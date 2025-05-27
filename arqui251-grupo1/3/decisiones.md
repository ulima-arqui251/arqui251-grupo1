## Decisión 1 (Elección de Tecnología)

### Título:
Elección entre Lenguaje de Tipado Estático vs Tipado Dinámico para todo el proyecto


### Contexto:

El grupó de desarrollo es mediano los cuales tienen experiencia con Java, Javascript y Python. La velocidad de desarrollo es vital dado que la empresa está constantemente agregando nuevas actualizaciones al software de facturación. Dicho esto, la aplicación necesita un nivel adecuado de seguridad para proteger los datos financieros de los clientes de la empresa.


### Alternativas:

1.	Lenguaje de Tipado Estático (Java, Kotlin)
   
•	El código es más fácil de refactorizar y mantener gracias al tipado fuerte

•	Los compiladores pueden optimizar el código de manera más eficiente.

2.	Lenguaje de Tipado Dinámico (JavaScript, Python)

•	En el caso de JavaScript, el uso de un único lenguaje para frontend y backend simplifica el stack tecnológico.

•	Con Node.js, ofrece capacidades de concurrencia eficientes para manejar solicitudes múltiples.


### Criterios de Elección:

•	Velocidad de desarrollo.

•	Minimizar la cantidad de lenguajes diferentes que utilizará el equipo de desarrollo

•	Flexibilidad para cambios rápidos en los módulos de la plataforma.

•	Necesidades de seguridad y robustez en los módulos financieros.


### Decisión:

Se elige el uso de lenguajes de tipado dinámico.


### Sustento:

Debido al rápido crecimiento de la empresa y la necesidad de iterar con agilidad, un lenguaje de tipado dinámico como JavaScript ofrece la flexibilidad ideal para adaptarse a cambios constantes. Además, unificar el lenguaje en frontend y backend simplifica el stack tecnológico y facilita la adopción de nuevos desarrollos por parte del equipo actual. Aunque los lenguajes tipados estáticamente puedan reducir ciertos errores, en este contexto, la capacidad de adaptación y la simplicidad del ecosistema resultan prioridades más relevantes.


### Decisión 2 (Modelo de Datos)


### Título:

Elección entre un modelo de datos relacional vs documental para el manejo de los datos del módulo de CRM


### Contexto:

La información de los clientes, almacenada por el módulo de CRM, es menos estructurada que la del resto de la plataforma. Suelen almacenarse también interacciones con el soporte y comunicaciones por diversos canales. Se está revisando si se utilizará el modelo relacional o se opta por un esquema documental.


### Alternativas:

1.	Modelo Relacional (Oracle)

•	Garantiza consistencia entre los datos.

•	Cuenta con herramientas empresariales maduras para seguridad, respaldo y monitoreo

•	Permite almacenar documentos en formato JSON

2.	Modelo Documental (Couchbase)

•	Permite la sincronización entre dispositivos y el almacenamiento distribuido eficiente

•	Ideal para aplicaciones en tiempo real que requieren baja latencia y alta disponibilidad


### Criterios de Elección:

•	Integridad de datos y soporte para consultas estructuradas

•	Flexibilidad en la definición del esquema de los datos de clientes.

•	Requisitos de escalabilidad para el CRM.


### Decisión:

Se elige un modelo relacional (como Oracle Database)


### Sustento:

Aunque el módulo de CRM maneja datos parcialmente no estructurados, se considera fundamental mantener una visión integrada del sistema, incluyendo la posibilidad de cruzar información con otros módulos (como ventas, soporte o facturación). Oracle permite lograr esto sin comprometer la integridad de los datos, ofreciendo además soporte para documentos JSON cuando se requiere flexibilidad. Esta capacidad híbrida permite conservar la estructura del modelo relacional y al mismo tiempo adaptarse a casos puntuales de datos más dinámicos. Adicionalmente, su madurez, rendimiento y herramientas de gestión lo hacen una opción más alineada con los estándares de calidad y confiabilidad requeridos para una solución empresarial integrada.


### Decisión 3 (Coordinación)


### Título:

Un script de JavaScript se encarga de ejecutar consultas SQL


### Contexto:

Se necesita una base de datos robusta y escalable que permita ejecutar consultas desde un script en JavaScript, optimizando el rendimiento y garantizando integridad en los datos. 


### Alternativas:

1.	Oracle Database

•	Alta integridad referencial y consistencia de datos.

•	Herramientas robustas para seguridad, replicación y respaldo.

2.	MongoDB

•	Alta escalabilidad horizontal.

•	Flexible para cambios en la estructura de datos.


### Criterios de Elección:

•	Integridad de datos.

•	Escalabilidad

•	Facilidad de integración con JavaScript


### Decisión:

Se elige Oracle como el modelo de base de datos para la aplicación


### Sustento:
Oracle ofrece una infraestructura sólida para mantener la integridad y consistencia de los datos, aspectos fundamentales en sistemas de facturación. Su fiabilidad comprobada en entornos empresariales complejos lo posiciona como una solución robusta para aplicaciones que requieren precisión y control.

