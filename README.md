
# Equipo 04 - Fundamentos de Diseño 2025-2  
### Carrera de Ingeniería Informática e Industrial  
**Universidad Peruana Cayetano Heredia**

---

## 🌍 Descripción del Equipo  
Somos el **Equipo 04** del curso **Fundamentos de Diseño 2025-2**, conformado por estudiantes de la carrera de Ingeniería Informática e Industrial.  

Nuestro objetivo es aplicar metodologías de diseño centradas en generar soluciones innovadoras que impacten de manera positiva en la sociedad, el ambiente y la tecnología.  

Como equipo, nos interesa trabajar en los siguientes **Objetivos de Desarrollo Sostenible (ODS):**
 
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
| <img src="https://github.com/BeyondNate/Grupo_4_Fundamentos_disenao/blob/main/Recursos/imagenes/melisa.jpg" width="90"/> | **Melissa Bustos Montañez** | Diseñadora | Diseño de prototipos, creatividad aplicada |
| <img src="https://github.com/BeyondNate/Grupo_4_Fundamentos_disenao/blob/main/Recursos/imagenes/gabriela.jpg" width="90"/> | **Gabriela Santamaría Huaytan** | Encargada de documentación | Comunicación científica, redacción técnica |
| <img src="https://github.com/BeyondNate/Grupo_4_Fundamentos_disenao/blob/main/Recursos/imagenes/asmat.jpg" width="90"/> | **Rodrigo Asmat Mendoza** | Programador - Modelador | Programación, análisis de datos, simulación |

---


# PROYECTO: SmartFresh - Módulo Inteligente Antidesperdicio para Refrigeradores

### Descripción General
**SmartFresh** es un módulo inteligente y portátil que se instala en el interior de refrigeradores convencionales para transformarlos en sistemas inteligentes. Diseñado para prolongar la vida útil de los alimentos y reducir el desperdicio, integra tecnología IoT, sensores avanzados, visión artificial y está fabricado con materiales sostenibles.

### Objetivo General
Diseñar y desarrollar un prototipo de dispositivo modular adaptable que reduzca en un 50% el desperdicio de alimentos en hogares peruanos mediante tecnología de monitoreo inteligente y gestión proactiva.

### 🔍 ¿Cómo Funciona?

#### **Sistema Integrado de Monitoreo:**
1.  **Visión por Computadora:** Una cámara compacta en el módulo escanea periódicamente los productos, identificándolos y registrándolos en el inventario digital.
2.  **Sensores Inteligentes:**
    *   **Básculas inteligentes desmontables:** Se colocan en los estantes existentes para monitorear el consumo real.
    *   **Sensores de clima modular:** Miden temperatura y humedad en diferentes zonas del refrigerador.
    *   **Escáner de códigos:** Opcional para identificar productos envasados al guardarlos.

#### **Sensores y su Función Específica:**

| Sensor | Tipo | Para qué Sirve | Beneficio |
|:---|:---|:---|:---|
| **Cámara OV5647** | Visión artificial | Identifica alimentos mediante reconocimiento de imagen y detecta cambios de color/textura | Reconocimiento automático de la fruta deteriorada |
| **Sensor MQ135** | Sensar | Detectar la concentración de gases de CO2| Reconocer la calidad de la fruta |

#### **Procesamiento y Algoritmos:**
*   Un módulo de **Machine Learning** (Raspberry Pi/Jetson Nano) clasifica alimentos, estima su estado de frescura basado en apariencia y tiempo, y predice fechas de vencimiento.
*   **Algoritmos de recomendación** sugieren recetas basadas en los alimentos que están por vencer.

#### **Interfaz de Usuario y Alertas:**
*   **Aplicación móvil "SmartFresh App" conectada vía WiFi/Bluetooth:** Interfaz principal que muestra inventario en tiempo real y envía notificaciones push inteligentes:
    > *"⚠️ ALERTA: Tus plátanos están en su punto perfecto para comer hoy. ¡Ideal para un smoothie!"*
    > *"🔔 AVISO: La leche caduca en 2 días. ¿Te gustaría ver recetas para usarla?"*
    > *"📊 RESUMEN SEMANAL: Has ahorrado S/ 15.00 al reducir tu desperdicio de alimentos."*
    > *"🌡️ NOTIFICACIÓN: La temperatura del refrigerador subió a 8°C. Verifica que la puerta esté bien cerrada."*

#### **Características de la Aplicación Móvil:**
- **Inventario en Tiempo Real:** Visualización de todos los alimentos con su estado de frescura
- **Alertas Personalizables:** Configuración de preferencias de notificaciones
- **Recetas Inteligentes:** Sugerencias basadas en alimentos próximos a vencer
- **Estadísticas de Ahorro:** Seguimiento de dinero y alimentos salvados del desperdicio
- **Control Remoto:** Monitoreo de temperatura y humedad desde cualquier lugar
- **Listas de Compra Automáticas:** Sugiere qué comprar basado en consumos habituales

#### **Diseño Sostenible y Portátil:**
*   **Batería recargable:** Autonomía de 2-3 semanas con carga completa.
*   **Materiales ecológicos:** Carcasa fabricada con plásticos reciclados o biodegradables.
*   **Fácil instalación:** Se adhiere con soportes magnéticos o de succión, sin modificaciones permanentes.
*   **Compatibilidad universal:** Funciona con cualquier modelo de refrigerador.

---
## 📊 IMPACTO EN EL ODS 12: PRODUCCIÓN Y CONSUMO RESPONSABLES

### 🎯 Meta 12.3: Reducción del Desperdicio de Alimentos
**"De aquí a 2030, reducir a la mitad el desperdicio de alimentos per cápita mundial"**

| Indicador | Impacto de SmartFresh |
|:---|:---|
| **Reducción de desperdicio** | Monitoreo inteligente que previene el olvido y descomposición |
| **Optimización del consumo** | Alertas proactivas sobre fechas de vencimiento |
| **Gestión eficiente** | Inventario automático que evita compras duplicadas |

### ♻️ Meta 12.5: Reducción de Generación de Desechos
**"Reducir considerablemente la generación de desechos mediante actividades de prevención, reducción, reciclado y reutilización"**

| Indicador | Impacto de SmartFresh |
|:---|:---|
| **Prevención** | Elimina el desperdicio en origen al conservar mejor los alimentos |
| **Reducción** | Disminuye la cantidad de residuos orgánicos en hogares |
| **Economía circular** | Extiende la vida útil de refrigeradores existentes |

### 📚 Meta 12.8: Información para Estilos de Vida Sostenibles
**"Asegurar que las personas tengan información y conocimientos sobre desarrollo sostenible"**

| Indicador | Impacto de SmartFresh |
|:---|:---|
| **Educación alimentaria** | Proporciona datos sobre conservación de alimentos |
| **Concienciación** | Reportes semanales sobre ahorro económico y ambiental |
| **Toma de decisiones** | Información en tiempo real para consumo responsable |

---

## 🧩 Componentes Clave del Prototipo

| Categoría | Componentes | Función |
|:---:|:---|:---|
| **Hardware** | Raspberry Pi, Cámara OV5647, Sensores DHT22, Básculas HX711, Batería Li-ion 5000mAh | Cerebro, sensórica y potencia |
| **Software** | OpenCV, TensorFlow Lite, App móvil (Flutter), Sistema de alertas push | Procesamiento inteligente y comunicación |
| **Conectividad** | WiFi, Bluetooth 5.0, Servidor cloud para notificaciones | Conexión con aplicación móvil |
| **Diseño** | Carcasa impresa 3D (PLA reciclado), Soporte magnético, Básculas desmontables | Adaptabilidad y sostenibilidad |

---

## 🔬 Metodología de Desarrollo
1.  **Investigación:** Análisis de refrigeradores y hábitos de consumo peruanos
2.  **Diseño Conceptual:** Modelado 3D de carcasa y accesorios modulares
3.  **Desarrollo Técnico:** Implementación de sensores, visión artificial y app móvil
4.  **Pruebas y Validación:** Testeo en diferentes modelos de refrigeradores
5.  **Iteración:** Mejora continua basada en feedback de usuarios

---

## 📈 Métricas de Impacto ODS 12

| Métrica | Objetivo 2030 | Contribución de SmartFresh |
|:---|:---|:---|
| Reducción desperdicio alimentos | 50% | 50% en hogares usuarios |
| Generación de desechos orgánicos | Reducción considerable | Hasta 40% menos residuos |
| Personas con información sostenible | 100% | Educación continua a usuarios |

---

## 🔋 Especificaciones Técnicas

| Parámetro | Especificación |
|:---|:---|
| **Autonomía** | 2-3 semanas (uso normal) |
| **Tiempo de carga** | 3-4 horas (USB-C) |
| **Compatibilidad** | Todos los refrigeradores |
| **Sensores** | Temperatura, humedad, peso, cámara, RFID, QR |
| **Conectividad** | WiFi, Bluetooth 5.0, Cloud integration |
| **Notificaciones** | Push notifications, alertas personalizables |
| **Materiales** | PLA reciclado, componentes electrónicos reutilizables |
| **Peso** | 350g (módulo principal) |

## 📱 SmartFresh App - Características Principales

### **Notificaciones Inteligentes:**
- ✅ Alertas de vencimiento con 3 días de anticipación
- ✅ Notificaciones de estado óptimo de consumo
- ✅ Alertas técnicas (temperatura, humedad, puerta abierta)
- ✅ Resúmenes semanales de ahorro y impacto ambiental
- ✅ Recordatorios de productos que necesitan reposición

### **Disponibilidad:**
- 📲 **Android e iOS** disponibles en Google Play y App Store
- 🌐 **Interfaz en español** y adaptada para Perú
- 📊 **Panel de control** con métricas de sostenibilidad
- 🛒 **Integración con listas de compra** automáticas

**Nota:** El módulo está diseñado para operar en condiciones de frío (0°C a 10°C) y alta humedad (80-90% RH), típicas de refrigeradores domésticos. La aplicación móvil permite recibir alertas incluso cuando no estés en casa, gracias a la conexión cloud.

---

## 🎯 Beneficios de los Sensores SmartFresh

### **Detección Automática de Alimentos**
Los sensores de visión artificial identifican qué alimentos introduces y los registran automáticamente en tu inventario, sin necesidad de ingresar datos manualmente.

### **Monitoreo de Condiciones Óptimas**
Los sensores de temperatura y humedad aseguran que tu refrigerador mantenga las condiciones ideales para cada tipo de alimento, previniendo su descomposición prematura.

### **Control de Consumo Inteligente**
Las básculas integradas detectan cuándo consumes productos y en qué cantidad, permitiendo un seguimiento preciso de tus hábitos alimenticios.

### **Prevención de Desperdicio**
El sistema de alertas tempranas te avisa con suficiente anticipación cuándo los alimentos están próximos a vencer o alcanzan su punto óptimo de consumo.

### **Ahorro Energético**
El sensor de puerta detecta si el refrigerador queda abierto accidentalmente, enviándote una alerta para evitar pérdidas de frío y consumo excesivo de energía.
