# BAIE-001 (BOMBA DE AGUA IMPULSADA EOLICAMENTE)
## Proyecto: Sistema de Bombeo Eólico Inteligente con Arduino
##  Descripción
Sistema autónomo que utiliza energía eólica para generar electricidad, almacenarla en una batería y activar una bomba de agua controlada por Arduino. Ideal para zonas rurales, altas o mineras con acceso limitado a la red eléctrica.
---

##  Objetivos
- Aprovechar el viento constante de zonas altas/mineras para generar energía.
- Bombear agua sin depender de combustibles fósiles o la red eléctrica.
- Implementar un control inteligente con Arduino para optimizar el uso de energía.

---

## ⚙️ Componentes Principales
| Componente               | Función                                                                 |
|--------------------------|-------------------------------------------------------------------------|
| Arduino Nano/Uno         | Control central del sistema (monitoreo y activación de la bomba).       |
| Motor DC (como generador)| Convierte la energía eólica en eléctrica (actúa como dinamo).           |
| Hélices de plástico      | Capturan el viento y giran el motor.                                    |
| Batería LiPo/Li-ion      | Almacena la energía generada (ej: 12V 2000mAh).                         |
| Módulo de carga solar    | Protege la batería durante la carga (ej: TP4056).                       |
| Bomba de agua DC         | Bombea agua cuando se activa (ej: bomba de 5-12V).                      |
| Sensor de nivel de agua  | Detecta el nivel del tanque (opcional).                                 |

---

##  Diagrama de Conexiones Simplificado
[Hélices] → [Motor DC como generador] → [Módulo de carga] → [Batería] → [Arduino]
│
└→ [Bomba de agua]

## Contribución al ODS 7
Este proyecto contribuye directamente al ODS 7 mediante:

1. Energía renovable no contaminante: Utiliza el viento, una fuente limpia e inagotable.
2. Acceso a energía asequible: Reduce costos de bombeo al eliminar dependencia de combustibles fósiles o electricidad de red.
3. Tecnología sostenible en zonas remotas: Ideal para comunidades mineras o rurales con acceso limitado a energía.
4. Innovación en eficiencia energética: Arduino optimiza el uso de energía solo bombeando agua cuando es necesario.

---

## Aplicaciones en la Vida Real
- Riego agrícola automático en zonas ventosas.
- Abastecimiento de agua potable en comunidades aisladas.
- Sistemas de emergencia para bombeo en caso de sequías.


---

## Desafíos y Soluciones

| Desafío | Solución propuesta |
|---------|-------------------|
| Bajo voltaje del generador | Usar multiplicador de voltaje o motor más eficiente. |
| Batería sobrecargada | Módulo de carga con protección (TP4056). |
| Bomba no activa sin viento | Almacenar energía en batería y usarla cuando haya suficiente carga. |

---
## Próximos Pasos (Para Escalar el Proyecto)
1. Agregar un sistema de monitoreo remoto con WiFi (ESP8266) para reportar estado vía web.
2. Implementar un mecanismo de orientación al viento con un servo motor.
3. Usar paneles solares complementarios para días sin viento (sistema híbrido).

---
## Conclusión
Este prototipo demuestra que es posible integrar tecnología low-cost (Arduino) con energías renovables para resolver problemas reales como el bombeo de agua. Es un ejemplo perfecto de cómo la innovación accesible puede impactar positivamente en comunidades y alinearse con los Objetivos de Desarrollo Sostenible de la ONU.

---
## Sketch
![Sketch FVH-001](https://github.com/BeyondNate/Grupo_4_Fundamentos_disenao/blob/main/Documentacion/assets/BAIE_001.jpeg?raw=true)


