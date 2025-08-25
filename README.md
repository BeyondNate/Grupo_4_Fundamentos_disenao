
# Equipo 04 - Fundamentos de Diseño 2025-2  
### Carrera de Ingeniería Informática e Industrial  
**Universidad Peruana Cayetano Heredia**

---

## 🌍 Descripción del Equipo  
Somos el **Equipo 04** del curso **Fundamentos de Diseño 2025-2**, conformado por estudiantes de la carrera de Ingeniería Informática e Industrial.  
Nuestro objetivo es aplicar la metodología de diseño para generar soluciones innovadoras con impacto social, tecnológico y ambiental.  

Nos interesa trabajar en los siguientes **Objetivos de Desarrollo Sostenible (ODS):** 
 
- ODS 7: Energía Asequible y No Contaminante 
- ODS 9: Industria, Innovación e Infraestructura  
- ODS 11: Ciudades y Comunidades Sostenibles
- ODS 12: Producción y Consumo Responsables 
- ODS 13: Acción por el Clima  

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
| <img src="https://github.com/BeyondNate/Grupo_4_Fundamentos_disenao/blob/main/Recursos/imagenes/melisa.jpg" width="90"/> | **Melissa Bustos Montañez** | Diseñador/a | Diseño de prototipos, creatividad aplicada |
| <img src="https://github.com/BeyondNate/Grupo_4_Fundamentos_disenao/blob/main/Recursos/imagenes/gabriela.jpg" width="90"/> | **Gabriela Santamaría Huaytan** | Encargado/a de documentación | Comunicación científica, redacción técnica |
| <img src="https://github.com/BeyondNate/Grupo_4_Fundamentos_disenao/blob/main/Recursos/imagenes/asmat.jpg" width="90"/> | **Rodrigo Asmat Mendoza** | Programador/a - Modelador/a | Programación, análisis de datos, simulación |

---

## 📌 Resumen Final  
### ODS 11 Ciudades inteligentes
### **Objetivo General**
Garantizar el acceso a una energía **asequible, segura, sostenible y moderna** para todas las personas.

### **¿Por qué es importante?**
La energía es fundamental para el desarrollo humano y económico: para la salud, la educación, el empleo y la seguridad. Sin embargo, millones de personas aún carecen de acceso a electricidad y dependen de fuentes de energía contaminantes (como leña o queroseno) para cocinar, lo que genera problemas de salud y ambientaless.

---

### **Metas Clave (Resumidas)**

El ODS 7 busca:

1.  **Acceso Universal:** Garantizar el acceso universal a servicios energéticos asequibles, confiables y modernos para **2030**.
2.  **Energía Renovable:** Aumentar sustancialmente el porcentaje de **energía renovable** (solar, eólica, hidroeléctrica, etc.) en el mix energético global.
3.  **Eficiencia Energética:** Duplicar la tasa mundial de mejora de la **eficiencia energética** (usar menos energía para hacer lo mismo).
4.  **Cooperación Internacional:** Promover la investigación y la inversión en infraestructura y tecnología de energía limpia.
5.  **Tecnología y Servicios:** Ampliar la infraestructura y mejorar la tecnología para prestar servicios energéticos modernos y sostenibles para todos en los países en desarrollo.

---

BAIE 001 - Bomba de Agua Impulsada Eólicamente para Minería en Altura**  

**Objetivo General:**  
Diseñar y validar un prototipo de bomba de agua accionada por energía eólica para reducir el uso de combustibles fósiles en operaciones mineras de grandes alturas.  

**Metas Clave:**  
1. Aprovechar vientos de altitud para bombeo sostenible.  
2. Reducir costos energéticos y emisiones en minería.  
3. Validar technicalmente el prototipo en condiciones simuladas.  


**Aliados Clave:**  
- Empresas mineras (datos, financiamiento, pruebas).  
- Departamentos de ingeniería universitaria (recursos técnicos).  

**Impacto:**  
- **Ambiental:** Energía limpia y reducción de huella de carbono.  
- **Económico:** Ahorro operativo para la minería.  
- **Social:** Potencial adaptación para comunidades rurales.  

**Entregables:**  
- Prototipo funcional.  
- Reporte técnico y análisis de viabilidad económica.  
---

### **Proyecto: BAIE 001 - Sistema Integrado de Bombeo Eólico con Control Arduino**

**Objetivo:**  
Automatizar un sistema de bombeo de agua para minería en altura, usando energía eólica, con control inteligente y protecciones mediante Arduino.

---

### **Componentes Necesarios**

#### **1. Para la Generación Eólica:**
- Aerogenerador (puede ser DIY con motor DC como generador o kit comercial pequeño).
- Torre metálica o estructura firme.
- **Sensores:**
  - Anemómetro (medir velocidad del viento).
  - Veleta (detectar dirección del viento).
  - Sensor de RPM (encoder óptico en el eje del rotor).

#### **2. Para el Control y Protección:**
- Arduino Uno/Mega/Nano.
- Módulo de relés o driver MOSFET (para control de carga).
- Servomotor (para orientación automática del aerogenerador opcional).
- Freno mecánico (ej.: disco de freno con solenoide o servo).
- Batería de 12V/24V (para almacenar energía y estabilizar el sistema).

#### **3. Para el Bombeo:**
- Bomba de agua DC (12V/24V, según el caudal requerido).
- Sensor de nivel de agua (flotador o ultrasonido).
- Módulo PWM (para regular velocidad de la bomba).
- Tuberías y tanque de almacenamiento.

---

### **Funciones de Arduino (Código Integrado)**

El Arduino ejecutará este flujo de forma continua:

1.  **Monitoreo del Viento:**
    - Lee anemómetro y veleta.
    - Calcula si el viento es suficiente para generar energía o si es peligroso.

2.  **Protección del Aerogenerador:**
    - Si el viento > límite máximo (ej.: 60 km/h):
      - Activa el freno mecánico.
      - Desconecta la carga para evitar daños.
    - Si el viento cambia de dirección (y hay servomotor):
      - Ajusta la orientación del aerogenerador para maximizar eficiencia.

3.  **Control de la Bomba:**
    - Lee el sensor de nivel de agua (ej.: tanque vacío = bombear).
    - Si hay suficiente viento y el tanque no está lleno:
      - Regula la velocidad de la bomba con PWM según la intensidad del viento.
    - Si el tanque está lleno o no hay viento:
      - Apaga la bomba.

4.  **Regulación de Carga:**
    - Dirige la energía generada hacia:
      - La bomba de agua (prioridad).
      - La batería de respaldo (si sobra energía).
      - Resistor de descarga (dump load) si la batería está llena.

5.  **Monitorización en Tiempo Real:**
    - Muestra en pantalla LCD/PC:
      - Velocidad del viento.
      - Estado de la bomba (ON/OFF, velocidad).
      - Nivel de agua en tanque.
      - Alertas de seguridad.


---

### **Entregables del Proyecto**

1.  **Prototipo Físico:** Torre eólica + bomba + circuito con Arduino.
2.  **Código Arduino:** Programado y comentado.
3.  **Pruebas de Campo:** Datos de eficiencia (ej.: "Con viento a X km/h, se bombean Y litros/hora").
4.  **Análisis de Viabilidad:** Costos vs. ahorro energético para minería.

---
<img src="https://github.com/BeyondNate/Grupo_4_Fundamentos_disenao/blob/main/Recursos/imagenes/BAIE_001.jpeg" width="1000"/>
