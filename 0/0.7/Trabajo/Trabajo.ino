//import de WiFi
#include <WiFi.h>

//import de arduino para usar mqtt
#include <mqtt_client.h>

//import para usar el sensor DHT
#include "DHT.h"

//imports de azure
#include <az_core.h>
#include <az_iot.h>
#include "AzIoTSasToken.h"
#include "SerialLogger.h"
#include "iot_configs.h"
#include "azure_ca.h"

//Definir el pin del sensor y su tipo
#define SENSOR_PIN 4
#define SENSOR_TYPE DHT11

//crear sensor
DHT sensor(SENSOR_PIN, SENSOR_TYPE);

//obtener datos de azure y de mi WiFi
const char* wifiSSID = SSID;
const char* wifiPassword = PASSWORD;
const char* iotHubHost = HOSTNAME;
const char* mqttUri = "mqtts://" HOSTNAME;
const char* deviceName = DEVICE_ID;
const int mqttPort = AZ_IOT_DEFAULT_MQTT_CONNECT_PORT;

//variables para comunicación con azure
static esp_mqtt_client_handle_t mqttClient;
static az_iot_hub_client iotClient;

//variables para almacenar datos de la comunicación con azure. Son asignados arbitrariamente
static char clientId[128];
static char username[128];
static char password[200];
static uint8_t sasTokenBuffer[256];
static char telemetryTopic[128];

//Variables para calculos de envío
static unsigned long lastSendTime = 0;
constexpr unsigned long SEND_INTERVAL_MS = 1000;

//variables de la humedad
float currentHumidity = 0.0f;
float currentTemperature = 0.0f;

//creación del Token
static AzIoTSasToken sasToken(
    &iotClient,
    AZ_SPAN_FROM_STR(DEVICE_KEY),
    AZ_SPAN_FROM_BUFFER(sasTokenBuffer),
    AZ_SPAN_FROM_BUFFER(password));


//asegurar un solo envío por MQTT
#define MQTT_QOS1 1

//conectarse a WiFi
void connectWiFi() {
  Logger.Info("Intentando conexión a " + String(wifiSSID));
  WiFi.mode(WIFI_STA); //conectarse a un Wifi existente
  WiFi.disconnect();
  delay(100);
  WiFi.begin(wifiSSID, wifiPassword);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Logger.Info("Conectado");
}

//Crear tiempo, esto sirve para que el tiempo del modelo se relacione al de Axure
void setupTime() {
  Logger.Info("Sincronizando tiempo");
  //sincronizar a la hora de peru
  constexpr int timezoneOffset = -8 * 3600; 
  constexpr int dstOffset = 1 * 3600;
  //
  //configurar tiempo
  configTime(timezoneOffset, dstOffset, "pool.ntp.org", "time.nist.gov");

  //tiempo actual
  time_t now = time(nullptr); // obtiene el tiempo de UNIX (tiempo pasado desde uno de Enero de 1970)
  constexpr time_t minValidTime = 1510592825; //sincroniza a 2017, un tiempo seguro para UNIX
  //sincronización del tiempo
  while (now < minValidTime) {
    Serial.print(".");
    delay(500);
    now = time(nullptr);
  }
  Serial.println();
  Logger.Info("Tiempo sincronizado");
}



void initializeIoTHub() {
  // crea una opción default de azure y obtiene la opción de cliente customizable
  az_iot_hub_client_options options = az_iot_hub_client_options_default();
  options.user_agent = AZ_SPAN_FROM_STR("customClient/1.0");

  //validar que el cliente existe
  if (az_result_failed(az_iot_hub_client_init(
          &iotClient,
          az_span_create((uint8_t*)iotHubHost, strlen(iotHubHost)),
          az_span_create((uint8_t*)deviceName, strlen(deviceName)),
          &options))) {
    Logger.Error("Fallo la inicializacion del cliente");
    return;
  }

  size_t idLen = 0;

  //validar que la id del cliente es la correcta
  if (az_result_failed(az_iot_hub_client_get_client_id(
          &iotClient, clientId, sizeof(clientId) - 1, &idLen))) {
    Logger.Error("No se consiguió el ID del cliente");
    return;
  }

  //validar que el nombre del cliente es el correcto
  if (az_result_failed(az_iot_hub_client_get_user_name(
          &iotClient, username, sizeof(username), NULL))) {
    Logger.Error("Failed to get MQTT username");
    return;
  }

  Logger.Info("Id del cliente: " + String(clientId));
  Logger.Info("MQTT nombre de usuario: " + String(username));
}

//maneja eventos mqtt
void mqttEventHandler(void* handler_args, esp_event_base_t base, int32_t event_id, void* event_data) {
  esp_mqtt_event_handle_t event = (esp_mqtt_event_handle_t)event_data;

  switch (event->event_id) {

    case MQTT_EVENT_CONNECTED: {
      Logger.Info("MQTT connected");
      int subRes = esp_mqtt_client_subscribe(mqttClient, AZ_IOT_HUB_CLIENT_C2D_SUBSCRIBE_TOPIC, 1);
      if (subRes == -1) {
        Logger.Error("Fallo el envío de datos");
      } else {
        Logger.Info("Ya puedes enviar datos a la nube");
      }
      break;
    }

    case MQTT_EVENT_DISCONNECTED:
      Logger.Info("MQTT desconectado");
      break;

    case MQTT_EVENT_DATA: {
      Logger.Info("Recibiendo MQTT");
      Serial.write(event->data, event->data_len);
      Serial.println();
      break;
    }

    default:
      break;
  }
}

int initMqttClient() {

//genera token SAS
if (sasToken.Generate(60) != 0) {
    Logger.Error("No se generó token SAS");
    return 1;
}

// configuración para entrar
esp_mqtt_client_config_t config = {};

// configuración para entrar
#if defined(ESP_ARDUINO_VERSION_MAJOR) && ESP_ARDUINO_VERSION_MAJOR >= 3
  config.broker.address.uri = mqttUri;
  config.broker.address.port = mqttPort;
  config.credentials.client_id = clientId;
  config.credentials.username = username;
  config.credentials.authentication.password = (const char*)az_span_ptr(sasToken.Get());
  config.session.keepalive = 30;
  config.session.disable_clean_session = 0;
  config.network.disable_auto_reconnect = false;
  config.broker.verification.certificate = (const char*)ca_pem;
  config.broker.verification.certificate_len = (size_t)ca_pem_len;
#else // fallback for older Arduino versions
  config.uri = mqttUri;
  config.port = mqttPort;
  config.client_id = clientId;
  config.username = username;
  config.password = (const char*)az_span_ptr(sasToken.Get());
  config.keepalive = 30;
  config.disable_clean_session = 0;
  config.disable_auto_reconnect = false;
  config.event_handle = mqttEventHandler;
#endif

  mqttClient = esp_mqtt_client_init(&config);
  if (!mqttClient) {
    Logger.Error("MQTT client init failed");
    return 1;
  }
  //verificación de versión de arduino
#if defined(ESP_ARDUINO_VERSION_MAJOR) && ESP_ARDUINO_VERSION_MAJOR >= 3
  esp_mqtt_client_register_event(mqttClient, MQTT_EVENT_ANY, mqttEventHandler, NULL);
#endif
  if (esp_mqtt_client_start(mqttClient) != ESP_OK) {
    Logger.Error("Failed to start MQTT client");
    return 1;
  }
  Logger.Info("MQTT client started");
  return 0;
}

//envío de datos por telemetry
void sendTelemetry() {
 
  if (az_result_failed(az_iot_hub_client_telemetry_get_publish_topic(
          &iotClient, NULL, telemetryTopic, sizeof(telemetryTopic), NULL))) {
    Logger.Error("No se pudo conseguir el telemetry");
    return;
  }

  String payload = "{\"Temperature\": " + String(currentTemperature, 1) + ", \"Humidity\": " + String(currentHumidity, 1) + "}";
  int res = esp_mqtt_client_publish(mqttClient, telemetryTopic, payload.c_str(), payload.length(), MQTT_QOS1, 0);

  if (res == 0) {
    Logger.Error("No se pudo publicar el telemetry");
  } else {
    Logger.Info("Telemetry enviada: " + payload);
  }

}

//Inicio de las funciones
void setup() {
  Serial.begin(115200);
  Logger.Info("Starting system...");
  connectWiFi();
  setupTime();
  initializeIoTHub();
  initMqttClient();
  sensor.begin();
  lastSendTime = millis();
}

//Envio de datos
void loop() {
  //verificacion de WiFi
  if (WiFi.status() != WL_CONNECTED) {
    connectWiFi();
  } 
  //Verificación para enviar datos
  else if (millis() - lastSendTime > SEND_INTERVAL_MS) {
    currentHumidity = sensor.readHumidity();
    currentTemperature = sensor.readTemperature();
    //verificación si son datos reales
    if (isnan(currentHumidity) || isnan(currentTemperature)) {
      Logger.Error("Error en el sensor");
    } else {
      sendTelemetry();
    }
    lastSendTime = millis() + 5000;
  }
  delay(1000);
}
