#include "esp_camera.h"
#include <HardwareSerial.h>
#include <base64.h>

// Configuración pines cámara AI-Thinker
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27
#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

HardwareSerial SerialPort(2); // UART2

void setup() {
  Serial.begin(115200);
  SerialPort.begin(115200, SERIAL_8N1, 3, 1); // RX=GPIO3, TX=GPIO1
  
  // Inicializar cámara
  if (!setupCamera()) {
    Serial.println("❌ Error: No se pudo inicializar la cámara");
    SerialPort.println("ERROR_CAMERA_INIT");
    while(1) { 
      delay(1000); 
      Serial.println("Reinicia el ESP32-CAM...");
    }
  }
  
  Serial.println("🚀 ESP32-CAM Listo - Esperando comandos por Serial");
  SerialPort.println("CAM_READY");
}

bool setupCamera() {
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  
  // CONFIGURACIÓN OPTIMIZADA para envío Serial con Base64
  if(psramFound()){
    config.frame_size = FRAMESIZE_VGA;   // 640x480 - Balance perfecto
    config.jpeg_quality = 15;            // Compresión media-alta
    config.fb_count = 2;
    Serial.println("✅ PSRAM detectado - Calidad VGA");
  } else {
    config.frame_size = FRAMESIZE_QVGA;  // 320x240 - Más pequeño
    config.jpeg_quality = 12;            // Más compresión
    config.fb_count = 1;
    Serial.println("⚠️  Sin PSRAM - Calidad QVGA");
  }
  
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("❌ Error cámara: 0x%x\n", err);
    return false;
  }
  
  // Ajustes adicionales de la cámara
  sensor_t *s = esp_camera_sensor_get();
  if (s != NULL) {
    s->set_brightness(s, 0);     // -2 to 2
    s->set_contrast(s, 0);       // -2 to 2
    s->set_saturation(s, 0);     // -2 to 2
    s->set_special_effect(s, 0); // 0 to 6 (0 - No Effect)
    s->set_whitebal(s, 1);       // 0 = disable , 1 = enable
    s->set_awb_gain(s, 1);       // 0 = disable , 1 = enable
    s->set_wb_mode(s, 0);        // 0 to 4 - if awb_gain enabled (0 - Auto)
    s->set_exposure_ctrl(s, 1);  // 0 = disable , 1 = enable
    s->set_aec2(s, 0);           // 0 = disable , 1 = enable
    s->set_ae_level(s, 0);       // -2 to 2
    s->set_aec_value(s, 300);    // 0 to 1200
    s->set_gain_ctrl(s, 1);      // 0 = disable , 1 = enable
    s->set_agc_gain(s, 0);       // 0 to 30
    s->set_gainceiling(s, (gainceiling_t)0);  // 0 to 6
    s->set_bpc(s, 0);            // 0 = disable , 1 = enable
    s->set_wpc(s, 1);            // 0 = disable , 1 = enable
    s->set_raw_gma(s, 1);        // 0 = disable , 1 = enable
    s->set_lenc(s, 1);           // 0 = disable , 1 = enable
    s->set_hmirror(s, 0);        // 0 = disable , 1 = enable
    s->set_vflip(s, 0);          // 0 = disable , 1 = enable
    s->set_dcw(s, 1);            // 0 = disable , 1 = enable
  }
  
  Serial.println("✅ Cámara inicializada y configurada correctamente");
  return true;
}

void loop() {
  if (SerialPort.available()) {
    String command = SerialPort.readStringUntil('\n');
    command.trim();
    
    Serial.println("Comando recibido: " + command);
    
    if (command == "TAKE_PHOTO") {
      sendPhotoSerial();
    } else if (command == "STATUS") {
      SerialPort.println("CAM_READY");
      Serial.println("✅ Estado: Listo");
    } else if (command == "RESET") {
      Serial.println("🔄 Reiniciando cámara...");
      ESP.restart();
    } else if (command == "TEST") {
      testCamera();
    } else {
      SerialPort.println("ERROR_UNKNOWN_COMMAND");
      Serial.println("❌ Comando desconocido: " + command);
    }
  }
  delay(100);
}

void sendPhotoSerial() {
  Serial.println("📸 Capturando foto...");
  
  // Capturar foto
  camera_fb_t * fb = esp_camera_fb_get();
  if (!fb) {
    SerialPort.println("ERROR_CAMERA_FAIL");
    Serial.println("❌ Error: No se pudo capturar la foto");
    return;
  }
  
  Serial.printf("✅ Foto capturada: %d bytes - Resolución: %dx%d\n", 
                fb->len, fb->width, fb->height);
  
  // CONVERTIR A BASE64
  Serial.println("🔄 Convirtiendo a Base64...");
  unsigned long startConvert = millis();
  
  String base64Image = base64::encode(fb->buf, fb->len);
  
  unsigned long convertTime = millis() - startConvert;
  Serial.printf("✅ Base64 generado: %d caracteres en %lu ms\n", 
                base64Image.length(), convertTime);
  
  // ENVIAR METADATA
  SerialPort.print("PHOTO_START:");
  SerialPort.print(base64Image.length());
  SerialPort.print(":");
  SerialPort.print(fb->width);
  SerialPort.print("x");
  SerialPort.print(fb->height);
  SerialPort.println();
  
  delay(100); // Pausa para que el receptor se prepare
  
  // ENVIAR BASE64 EN CHUNKS (líneas de 1000 caracteres)
  int chunkSize = 1000; // Caracteres por línea
  int totalChars = base64Image.length();
  int sentChars = 0;
  int chunkCount = 0;
  unsigned long startTime = millis();
  
  Serial.println("📤 Enviando Base64 por Serial...");
  
  while (sentChars < totalChars) {
    int remaining = totalChars - sentChars;
    int currentChunk = (remaining < chunkSize) ? remaining : chunkSize;
    
    // Enviar chunk de base64
    String chunk = base64Image.substring(sentChars, sentChars + currentChunk);
    SerialPort.println(chunk);
    
    sentChars += currentChunk;
    chunkCount++;
    
    // Pequeña pausa cada 3 chunks
    if (chunkCount % 3 == 0) {
      delay(10);
      yield();
    }
    
    // Feedback de progreso cada 10 chunks
    if (chunkCount % 10 == 0) {
      int progress = (sentChars * 100) / totalChars;
      int elapsed = (millis() - startTime) / 1000;
      Serial.printf("📤 Progreso: %d/%d chars (%d%%) - Tiempo: %ds\n", 
                   sentChars, totalChars, progress, elapsed);
    }
  }
  
  // ENVIAR MARCADOR FINAL
  delay(100);
  SerialPort.println("PHOTO_END");
  
  unsigned long totalTime = millis() - startTime;
  Serial.printf("✅ Foto enviada completa: %d chunks, %d caracteres en %lu ms\n", 
                chunkCount, sentChars, totalTime);
  
  // Liberar memoria
  esp_camera_fb_return(fb);
  base64Image = ""; // Limpiar String
  
  Serial.printf("📊 Memoria libre: %d bytes\n", ESP.getFreeHeap());
}

void testCamera() {
  Serial.println("🧪 Iniciando prueba de cámara...");
  
  camera_fb_t * fb = esp_camera_fb_get();
  if (!fb) {
    SerialPort.println("TEST_FAILED");
    Serial.println("❌ Prueba fallida: No se pudo capturar foto");
    return;
  }
  
  Serial.printf("✅ Prueba exitosa: %d bytes, %dx%d\n", 
                fb->len, fb->width, fb->height);
  
  // Calcular tamaño estimado en base64
  int base64Size = ((fb->len * 4) / 3) + 4;
  
  SerialPort.print("TEST_PASSED:");
  SerialPort.print(fb->len);
  SerialPort.print(":");
  SerialPort.print(fb->width);
  SerialPort.print("x");
  SerialPort.print(fb->height);
  SerialPort.print(":");
  SerialPort.print(base64Size);
  SerialPort.println();
  
  Serial.printf("📊 Tamaño estimado Base64: %d caracteres\n", base64Size);
  
  esp_camera_fb_return(fb);
}

// Función para cambiar resolución en tiempo real (opcional)
void changeResolution(framesize_t resolution) {
  sensor_t *s = esp_camera_sensor_get();
  if (s != NULL) {
    s->set_framesize(s, resolution);
    Serial.printf("✅ Resolución cambiada a: %d\n", resolution);
    SerialPort.println("RESOLUTION_CHANGED");
  }
}
