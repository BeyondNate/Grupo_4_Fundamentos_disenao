// ESP32-CAM ► Telegram + Upload a Google Drive vía Google Apps Script
#include "esp_camera.h"
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "Base64.h"




// ---- CONFIGURACIÓN ----
const char* ssid = "UPCH_CENTRAL";
const char* password = "CAYETANO2022";




const char* botToken = "7968709983:AAGi8IuLLbM6lsTQb-Aqq3LlOryRLnxbR9Q";
const char* appsScriptUrl = "https://script.google.com/macros/s/AKfycbxWLc5EpS0BB2-9a97pt2gUcFaoFyltYkdvaGUzwQOjD9rEHVWyr5rVz_9jbyCYb50f/exec";
const char* secretToken = "BMMGR";
const char* driveFolderId = "1usCe7jZw3re85jDxBwQ-DNHohWFh26Ig";




WiFiClientSecure securedClient;
UniversalTelegramBot bot(botToken, securedClient);




// Config cámara
camera_config_t config = {
  .pin_pwdn = 32,
  .pin_reset = -1,
  .pin_xclk = 0,
  .pin_sscb_sda = 26,
  .pin_sscb_scl = 27,
  .pin_d7 = 35,
  .pin_d6 = 34,
  .pin_d5 = 39,
  .pin_d4 = 36,
  .pin_d3 = 21,
  .pin_d2 = 19,
  .pin_d1 = 18,
  .pin_d0 = 5,
  .pin_vsync = 25,
  .pin_href = 23,
  .pin_pclk = 22,
  .xclk_freq_hz = 20000000,
  .ledc_timer = LEDC_TIMER_0,
  .ledc_channel = LEDC_CHANNEL_0,
  .pixel_format = PIXFORMAT_JPEG,
  .frame_size = FRAMESIZE_VGA,
  .jpeg_quality = 12,
  .fb_count = 1
};




unsigned long lastTimeBotRan;
const unsigned long BOT_CHECK_INTERVAL = 2000;




// ------------------------------
void setup() {
  Serial.begin(115200);
  Serial.println("Iniciando WiFi...");




  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);




  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado, IP: ");
  Serial.println(WiFi.localIP());




  // Inicializar cámara
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Error init camera: %d\n", err);
    while (true) delay(1000);
  }




  // Telegram SSL
  securedClient.setInsecure();




  Serial.println("Listo.");
}




// ------------------------------
void loop() {
  if (millis() - lastTimeBotRan > BOT_CHECK_INTERVAL) {




    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);




    while (numNewMessages) {
      Serial.println("Nuevos mensajes:");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }




    lastTimeBotRan = millis();
  }
}




// ------------------------------
void handleNewMessages(int numNewMessages) {
  for (int i = 0; i < numNewMessages; i++) {




    String chat_id = String(bot.messages[i].chat_id);
    String text = bot.messages[i].text;




    Serial.printf("Msg de %s: %s\n", chat_id.c_str(), text.c_str());




    if (text == "/foto") {
      bot.sendMessage(chat_id, "Tomando foto... espera", "");
      delay(200);
      takeAndUploadPhoto(chat_id);
    } else {
      bot.sendMessage(chat_id, "Comando no reconocido.\nUsa /foto", "");
    }
  }
}




// ------------------------------
void takeAndUploadPhoto(String chat_id) {




  camera_fb_t * fb = esp_camera_fb_get();
  if (!fb) {
    Serial.println("Error al capturar foto");
    bot.sendMessage(chat_id, "Error al capturar foto", "");
    return;
  }




  Serial.printf("Foto capturada: %u bytes\n", fb->len);




  // Convertir a base64
  String imageBase64 = base64::encode(fb->buf, fb->len);
  esp_camera_fb_return(fb);




  // Construir JSON
  DynamicJsonDocument doc(1024);
  doc["token"] = secretToken;
  doc["folderId"] = driveFolderId;
  doc["filename"] = "foto_" + String(millis()) + ".jpg";
  doc["image"] = imageBase64;




  String json;
  serializeJson(doc, json);




  // ******* HTTPS FIX (soluciona error -11) *********
  WiFiClientSecure client;
  client.setInsecure();




  HTTPClient http;
  http.begin(client, appsScriptUrl);
  http.addHeader("Content-Type", "application/json");




  int httpCode = http.POST((uint8_t*)json.c_str(), json.length());




  if (httpCode > 0) {
    String payload = http.getString();
    Serial.printf("AppsScript respuesta: %d %s\n", httpCode, payload.c_str());




    if (httpCode > 0) {
    String payload = http.getString();
    Serial.printf("AppsScript respuesta: %d %s\n", httpCode, payload.c_str());




    // Buscar "status":"OK"
    if (payload.indexOf("\"status\":\"OK\"") >= 0) {
      bot.sendMessage(chat_id, "Foto Subida Correctamente", "");
    } else {
      bot.sendMessage(chat_id, "La foto no ha sido subida", "");
    }




} else {
    Serial.printf("Error HTTP: %d\n", httpCode);
    bot.sendMessage(chat_id, "Error conexión al servidor ❌", "");
}




  } else {
    Serial.printf("Error HTTP: %d\n", httpCode);
    bot.sendMessage(chat_id, "Error conexión al servidor ❌", "");
  }




  http.end();
}
