
# Equipo 04 - Fundamentos de Diseño 2025-2  
### Carrera de Ingeniería Informática e Industrial  
**Universidad Peruana Cayetano Heredia**

---

## 🌍 Descripción del Equipo  
Somos el **Equipo 04** del curso **Fundamentos de Diseño 2025-2**, conformado por estudiantes de la carrera de Ingeniería Informática e Industrial.  

Nuestro objetivo es aplicar metodologías de diseño centradas en generar soluciones innovadoras que impacten de manera positiva en la sociedad, el ambiente y la tecnología.  

Como equipo, nos interesa trabajar en los siguientes **Objetivos de Desarrollo Sostenible (ODS):**
 
- ODS 12: Producción y Consumo Responsables 

---

## 📸 Fotografía del Equipo  
<p align="center">
  <img src="https://github.com/BeyondNate/Grupo_4_Fundamentos_disenao/blob/main/Recursos/imagenes/grupo%20.jpg" alt="Foto grupal del equipo" width="500"/><br>
  <em>Figura 1. Fotografía del equipo 04</em>
</p>

---

## 👥 Integrantes del Equipo  

| Foto | Nombre | Rol | Intereses |
|------|--------|-----|-----------|
| <img src="https://github.com/BeyondNate/Grupo_4_Fundamentos_disenao/blob/main/Recursos/imagenes/Brad.jpeg" width="90"/> | **Brad Cardenas Parian** | Líder del equipo | Innovación social, sostenibilidad |
| <img src="https://github.com/BeyondNate/Grupo_4_Fundamentos_disenao/blob/main/Recursos/imagenes/Mar%C3%ADa.jpg" width="90"/> | **María Antezana De la Cruz** | Responsable de investigación | Gestión ambiental, desarrollo comunitario |
| <img src="https://github.com/BeyondNate/Grupo_4_Fundamentos_disenao/blob/main/Recursos/imagenes/melisa.jpg" width="90"/> | **Melissa Bustos Montañez** | Diseñadora | Diseño de prototipos, creatividad aplicada |
| <img src="https://github.com/BeyondNate/Grupo_4_Fundamentos_disenao/blob/main/Recursos/imagenes/gabriela.jpg" width="90"/> | **Gabriela Santamaría Huaytan** | Encargada de documentación | Comunicación científica, redacción técnica |
| <img src="https://github.com/BeyondNate/Grupo_4_Fundamentos_disenao/blob/main/Recursos/imagenes/asmat.jpg" width="90"/> | **Rodrigo Asmat Mendoza** | Programador - Modelador | Programación, análisis de datos, simulación |

---


# PROYECTO: ALI-SmartFresh - Módulo Inteligente Antidesperdicio para Refrigeradores

## Descripción
Este proyecto consiste en un módulo inteligente que se implementa en refrigeradoras para detectar el deterioro de las beterragas, contribuyendo a la reducción del desperdicio de alimentos. El sistema combina sensores de gases y visión computacional para monitorear la frescura de las verduras de manera automática.

---

## Estructura del Sistema

### 1. Unidad Externa
- Ubicada en la puerta de la refrigeradora.
- Integra un **ESP32** para enviar los datos de manera remota.

### 2. Unidad Interna
- Ubicada en el compartimento de verduras.
- Incluye un **sensor MQ135** que mide la concentración de CO₂ para detectar signos de deterioro.
- Cuenta con un **ESP32-CAM** que captura una fotografía de la fruta cuando el sensor detecta que está malograda.

---

## Motivación
Estamos motivados por la innovación tecnológica y la sostenibilidad alimentaria, buscando soluciones que reduzcan el desperdicio de alimentos y promuevan el consumo responsable.

---

## Objetivo de Desarrollo Sostenible (ODS)
Este proyecto está alineado con el **ODS 12: Producción y consumo responsables**, fomentando hábitos responsables y optimizando el uso de alimentos mediante la detección temprana de deterioro.

---

## Tecnologías Utilizadas
- **ESP32**  
- **ESP32-CAM**  
- **Sensor MQ135 (CO₂)**  
- **Wi-Fi** para comunicación remota  

---

## Cómo Funciona
1. El sensor MQ135 mide la concentración de CO₂ en el compartimento de verduras.
2. Cuando detecta que la beterraga está deteriorada, el ESP32-CAM toma una fotografía a través del comando de Telegram.
3. Los datos del CO2 se envían a la la base de datos y posteriormente a la pagina web a través del ESP32.
4. Se puede monitorear el estado de las beterragas en tiempo real.
