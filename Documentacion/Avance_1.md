# Proyecto: FVH-001 - Filtrador de Vapores Húmedos
## Descripción General:
El FVH-001 es un robot autónomo diseñado para operar en entornos mineros, capaz de detectar gases contaminantes y purificarlos para generar agua potable, utilizando energía solar como fuente principal.
Incorpora sensores de gas, un sistema de movimiento adaptativo (7 ruedas multiterreno) y una garra de adherencia para superficies irregulares.

---
##  Objetivos
-  Detectar y geolocalizar gases contaminantes en minas.
-  Alimentarse mediante energía solar renovable.
-  Moverse de forma autónoma en terrenos complejos (4x4 + garra de adherencia).
- (Futuro) Purificar gases y generar agua potable.

---
## Componentes Principales

| Componente                  | Función                                                                 |
|-----------------------------|-------------------------------------------------------------------------|
| Arduino Mega                | Control central de sensores, motores y lógica del sistema.             |
| Sensores de gas (MQ-Serie)  | Detección de CO, H₂S, metano y otros contaminantes en minas.           |
| Paneles solares             | Generación de energía renovable para autonomía operativa.              |
| Batería LiPo + regulador    | Almacenamiento y gestión de energía solar.                             |
| Motores DC + drivers        | Movimiento 4x4 en terrenos abruptos.                                   |
| Servomotor/Electroimán      | Garra de adherencia para estabilidad en pendientes o superficies lisas. |
| Módulo GPS                  | Georreferenciación de zonas contaminadas.                              |
| Tarjeta SD                  | Registro de datos de contaminación y operaciones.                      |

---

## Relación con ODS 7
Este proyecto contribuye al **Objetivo de Desarrollo Sostenible 7: Energía Asequible y No Contaminante** mediante:
- Uso de **energía solar** como fuente principal.
- Reducción de contaminación en minas mediante detección temprana.
- Tecnología accesible y de bajo costo con Arduino.
- Propuesta de purificación de aire (a futuro).

---

## Desafíos Técnicos
1. **Purificación de gases**: Requiere sistemas avanzados (condensación, filtros UV) fuera del alcance de Arduino.
2. **Energía en minas subterráneas**: La solar puede ser insuficiente → se requiere batería de respaldo.
3. **Complejidad mecánica**: 7 ruedas + garra requieren diseño estable y pruebas intensivas.

---

## 👥 Contribuciones
Ayudenos Profesor, es demasiado ambicioso
