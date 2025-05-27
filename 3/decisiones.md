# Decisión 1 (Elección de Tecnología)

## Título:
Elección entre Lenguaje de Tipado Estático vs Tipado Dinámico para todo el proyecto

## Contexto:
El grupo de desarrollo es mediano y tiene experiencia con Java y JavaScript. La velocidad de desarrollo es vital dado que la empresa está constantemente agregando nuevas actualizaciones al software de facturación. Además, la aplicación necesita un nivel adecuado de seguridad para proteger los datos financieros de los clientes de la empresa.

## Alternativas:

### Lenguaje de Tipado Estático (Java)
- El código es más fácil de refactorizar y mantener gracias al tipado fuerte.
- El compilador de Java es más eficiente.
- Proporciona mayor seguridad y detección temprana de errores en tiempo de compilación.
- Facilita la creación de sistemas robustos y menos propensos a fallos en producción.
- Funciona mejor para entornos físicos

### Lenguaje de Tipado Dinámico (JavaScript)
- En el caso de JavaScript, el uso de un único lenguaje para frontend y backend simplifica el stack tecnológico.
- Con Node.js, ofrece capacidades de concurrencia eficientes para manejar solicitudes múltiples.
- Permite mayor flexibilidad para cambios rápidos y prototipado.

## Criterios de Elección:
- Seguridad y robustez en los módulos financieros.
- Minimizar la cantidad de lenguajes diferentes que utilizará el equipo de desarrollo.
- Flexibilidad para cambios rápidos en los módulos de la plataforma.

## Decisión:
Se elige el uso de lenguajes de tipado estático, específicamente **Java**.

## Sustento:
Dado el enfoque en la seguridad, robustez y almacenamiento local de los datos financieros, Java representa la mejor opción para asegurar la calidad y mantenibilidad del software. El tipado estático permite detectar errores en tiempo de compilación, reduciendo fallos en producción y facilitando la refactorización conforme el sistema crece.

Aunque la velocidad de desarrollo y la simplicidad del stack son importantes, la prioridad en este proyecto es la integridad y estabilidad del sistema, lo que hace que Java sea la elección adecuada.
Esta decisión permitirá al equipo:
- Mantener un código más estructurado y seguro.
- Detectar errores tempranamente, minimizando riesgos.
- Facilitar la evolución y mantenimiento a largo plazo del sistema.
- Aprovechar la experiencia existente en el equipo para una adopción más rápida.


# Decisión 2 (Elección de arquitectura)

## Título:  
Elección entre Arquitectura Monolítica vs Arquitectura Cliente-Servidor para una aplicación Java con base de datos.

## Contexto:  
El proyecto necesita de una base de datos para almacenar toda la información de la empresa. Se tiene una mayor experiencia con Java. Finalmente, el negocio tiene planes de expansión.

## Alternativas:

### Arquitectura Monolítica  
- Todo el negocio está integrado en una sola aplicación.  
- Menor complejidad en la comunicación interna, sin latencias de red.  
- Difícil de escalar y mantener cuando el sistema crece o se vuelve complejo.  
- Cambios en una parte pueden impactar todo el sistema.  

### Arquitectura Cliente-Servidor  
- Separación clara entre cliente (interfaz) y servidor (lógica + base de datos) ubicados en la misma red local.  
- Permite distribuir la carga entre cliente y servidor para mejor rendimiento y mantenimiento.  
- Facilidad para actualizaciones independientes de cliente y servidor.  
- Posibilidad para comunicación a través de red local.
- Mejor preparación para crecimiento en usuarios y funcionalidad.  
- Permite futuros accesos remotos o integración con otros sistemas si fuera necesario..

## Criterios de Elección:  
- Escalabilidad y crecimiento futuro.  
- Complejidad y tiempo de desarrollo inicial.  
- Experiencia del equipo con tecnologías distribuidas.  

## Decisión:  
Se opta por la **Arquitectura Cliente-Servidor** para el proyecto Java con base de datos.

## Sustento:  
La arquitectura cliente-servidor permite una mejor escalabilidad y mantenimiento para el sistema. La separación de responsabilidades entre cliente y servidor facilita actualizaciones independientes, mejora la seguridad y evita conflictos.

Aunque el desarrollo inicial es más complejo que en un monolito, la experiencia del equipo en Java y la necesidad de una base robusta y escalable justifican esta elección. Además, el modelo ya tienen pruebas previas de exito para entornos pequeños en escala.

Esta decisión permitirá al equipo:  
- Escalar el servidor y el cliente según demanda.  
- Mantener y actualizar módulos sin afectar todo el sistema.  
- Gestionar mejor la seguridad y control de accesos.  
- Facilitar la integración futura con otros sistemas o servicios.


# Decisión 3 (Elección de Motor de Base de Datos)

## Título:  
Elección entre Oracle vs PostgreSQL para la base de datos del proyecto Java

## Contexto:  
El proyecto requiere una base de datos robusta, segura y con alta disponibilidad para soportar una aplicación Java empresarial. El sistema deberá manejar datos críticos, transacciones complejas y ofrecer soporte a un volumen medio-alto de usuarios concurrentes.

## Alternativas:

### Oracle  
- Motor de base de datos comercial con alta documentación
- Excelente soporte para transacciones complejas, alta concurrencia y rendimiento.  
- Amplias funcionalidades avanzadas como particionamiento, replicación, y seguridad.  
- Costos asociados de licenciamiento y mantenimiento.  
- Integración robusta con herramientas y frameworks Java empresariales.
- Experiencia previa.

### PostgreSQL  
- Motor de base de datos open source, altamente confiable y con gran comunidad.  
- Buen soporte para transacciones y concurrencia, con mejoras constantes.  
- Costos bajos o nulos en licenciamiento.  
- Menor soporte comercial formal, aunque existen opciones de soporte pago.  
- Puede requerir mayor configuración y tuning para cargas muy altas o funcionalidades avanzadas específicas.

## Criterios de Elección:  
- Robustez y fiabilidad en manejo de datos críticos.  
- Necesidades funcionales avanzadas (replicación, particionamiento, seguridad).  
- Escalabilidad y rendimiento bajo cargas esperadas.

## Decisión:  
Se elige **Oracle** como motor de base de datos para el proyecto.

## Sustento:  
Oracle ofrece un conjunto completo de funcionalidades avanzadas que garantizan la robustez, seguridad y escalabilidad necesarias para el proyecto empresarial. La experiencia previa del equipo con Oracle facilita el desarrollo y mantenimiento, reduciendo riesgos y tiempos de implementación.

Aunque PostgreSQL representa una alternativa económicamente atractiva y confiable, en este proyecto se debe asegurar la estabilidad que Oracle proporciona, especialmente con el lenguaje Java.

Con esta decisión, el equipo podrá:  
- Gestionar grandes volúmenes de datos con alta concurrencia y seguridad.  
- Aprovechar las capacidades avanzadas nativas de Oracle para optimizar rendimiento y disponibilidad.  
- Minimizar riesgos relacionados a la escalabilidad.





