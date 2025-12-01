#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>


// ======================
// OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);


// ======================
// Encoder
#define ENCODER_A 32
#define ENCODER_B 33
#define ENCODER_SW 25
volatile int encoderValue = 0;
volatile bool moved = false;
int lastA = LOW;


// ======================
// MQ135
#define MQ135_PIN 34
const int numSamples = 20;
float readings[numSamples];
int readIndex = 0;
float total = 0;


// ======================
// LED y buzzer
#define LED_ALERT 26
#define BUZZER 27


// ======================
// Datos usuario
String telefono = "";
int kilos = 0;
int etapa = 0; // 0=telefono,1=kilos,2=listo


// Botón encoder
bool lastButtonState = HIGH;
unsigned long buttonPressedTime = 0;


// ======================
// Telegram
const char* ssid = "UPCH_CENTRAL";
const char* password = "CAYETANO2022";
const char* botToken = "7968709983:AAGi8IuLLbM6lsTQb-Aqq3LlOryRLnxbR9Q";
WiFiClientSecure securedClient;
UniversalTelegramBot bot(botToken, securedClient);
String botName = "AliG002";
String botLink = "https://t.me/AliG002";


// ======================
// MySQL API
const char* mysqlServer = "http://172.20.25.105:5000"; // Tu IP
#define ALERT_INTERVAL 60000
unsigned long lastAlertTime = 0;
unsigned long lastDBUpdate = 0;
#define DB_UPDATE_INTERVAL 30000 // Guardar en DB cada 30 segundos
#define MAX_USERS 10
String chatIds[MAX_USERS];
int userCount = 0;


// ======================
// Funciones
void IRAM_ATTR leerEncoder(){
  int a = digitalRead(ENCODER_A);
  int b = digitalRead(ENCODER_B);
  if(a != lastA){
    if(b != a) encoderValue++;
    else encoderValue--;
    moved = true;
  }
  lastA = a;
}


void leerBotonEncoder(){
  bool buttonState = digitalRead(ENCODER_SW);
  if(buttonState==LOW && lastButtonState==HIGH) buttonPressedTime=millis();
 
  if(buttonState==LOW && (millis()-buttonPressedTime)>10000){
    telefono=""; kilos=0; etapa=0; encoderValue=0;
    mostrarPantalla();
    Serial.println("🔄 Sistema reiniciado");
  }


  if(buttonState==HIGH && lastButtonState==LOW){
    if(etapa==0){
      telefono += String(abs(encoderValue)%10);
      Serial.print("📞 Dígito ingresado: "); Serial.println(abs(encoderValue)%10);
      if(telefono.length()>=9) etapa=1;
    } else if(etapa==1){
      kilos = abs(encoderValue)%51; // max 50 kg
      etapa=2;
      Serial.print("⚖️ Kilos ingresados: "); Serial.println(kilos);
      // Registrar usuario en BD cuando completa datos
      registrarUsuarioBD();
    }
    encoderValue=0;
    mostrarPantalla();
  }
  lastButtonState=buttonState;
}


void mostrarPantalla(){
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0,0);


  if(etapa==0){
    display.println("Ingrese telefono:");
    display.setCursor(0,20);
    display.print(telefono); display.print("_");
    display.setCursor(0,45);
    display.print("Valor: "); display.println(abs(encoderValue)%10);
  } else if(etapa==1){
    display.println("Ingrese kilos:");
    display.setCursor(0,20);
    display.print(kilos); display.println(" kg");
    display.setCursor(0,45);
    display.print("Valor: "); display.println(abs(encoderValue)%51);
  } else{
    display.println("Datos completos!");
    display.setCursor(0,20);
    display.print("Telefono: "); display.println(telefono);
    display.setCursor(0,35);
    display.print("Kilos: "); display.println(kilos);
    display.println("--------------------");
    display.println("Presione 10s para reset");
    display.println("--------------------");
    display.println("Bot Telegram:");
    display.println(botName);
    display.println(botLink);
    display.println("Inicie /start en bot");
  }
  display.display();
}


// ======================
// Funciones para MySQL MEJORADAS
void registrarUsuarioBD() {
  if(WiFi.status() == WL_CONNECTED){
    HTTPClient http;
    http.setTimeout(10000); // 10 segundos timeout
    String url = String(mysqlServer) + "/registrar_usuario";
   
    Serial.print("🌐 Conectando a: "); Serial.println(url);
   
    if(!http.begin(url)) {
      Serial.println("❌ Error iniciando conexión HTTP");
      return;
    }
   
    http.addHeader("Content-Type", "application/json");


    StaticJsonDocument<200> doc;
    doc["telefono"] = telefono;
    doc["kilos"] = kilos;


    String jsonStr;
    serializeJson(doc, jsonStr);
   
    Serial.print("📤 Enviando datos: "); Serial.println(jsonStr);
   
    int httpResponse = http.POST(jsonStr);
   
    if(httpResponse == 200){
      Serial.println("✅ Usuario registrado en BD correctamente");
    } else {
      Serial.print("❌ Error al registrar usuario - Código: ");
      Serial.print(httpResponse);
      Serial.print(" - Respuesta: ");
      Serial.println(http.getString());
    }
    http.end();
  } else {
    Serial.println("❌ WiFi no conectado para registrar usuario");
  }
}


void guardarLecturaBD(float voltage, float ppm, String estado) {
  if(WiFi.status() == WL_CONNECTED){
    HTTPClient http;
    http.setTimeout(10000); // 10 segundos timeout
    String url = String(mysqlServer) + "/guardar_lectura";
   
    Serial.print("🌐 Conectando a: "); Serial.println(url);
   
    if(!http.begin(url)) {
      Serial.println("❌ Error iniciando conexión HTTP");
      return;
    }
   
    http.addHeader("Content-Type", "application/json");


    StaticJsonDocument<300> doc;
    doc["telefono"] = telefono;
    doc["voltage"] = voltage;
    doc["ppm"] = ppm;
    doc["estado"] = estado;
    doc["timestamp"] = millis();


    String jsonStr;
    serializeJson(doc, jsonStr);
   
    Serial.print("📤 Enviando lectura: "); Serial.println(jsonStr);
   
    int httpResponse = http.POST(jsonStr);
   
    if(httpResponse == 200){
      Serial.println("✅ Lectura guardada en BD");
    } else {
      Serial.print("❌ Error guardando lectura - Código: ");
      Serial.print(httpResponse);
      Serial.print(" - Respuesta: ");
      Serial.println(http.getString());
    }
    http.end();
  } else {
    Serial.println("❌ WiFi no conectado para guardar lectura");
  }
}


// ======================
void setup() {
  Serial.begin(115200);
  Serial.println("\n🚀 Iniciando Sistema de Monitoreo...");


  // Pines
  pinMode(ENCODER_A, INPUT_PULLUP);
  pinMode(ENCODER_B, INPUT_PULLUP);
  pinMode(ENCODER_SW, INPUT_PULLUP);
  pinMode(LED_ALERT, OUTPUT);
  pinMode(BUZZER, OUTPUT);


  attachInterrupt(digitalPinToInterrupt(ENCODER_A), leerEncoder, CHANGE);


  // OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
    Serial.println("❌ OLED fallo");
    while(1);
  }
  display.clearDisplay();
  display.setTextColor(WHITE);
  Serial.println("✅ OLED inicializado");


  // WiFi
  Serial.print("📡 Conectando a WiFi: ");
  Serial.println(ssid);
 
  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ WiFi conectado");
  Serial.print("📶 IP local: "); Serial.println(WiFi.localIP());


  // Test conexión servidor
  Serial.println("🔍 Probando conexión con servidor...");
  HTTPClient http;
  http.begin(String(mysqlServer) + "/status");
  int response = http.GET();
  Serial.print("🤖 Respuesta del servidor: ");
  Serial.println(response);
  if(response == 200) {
    Serial.println("✅ Servidor Flask conectado correctamente");
  } else {
    Serial.println("❌ No se pudo conectar al servidor Flask");
  }
  http.end();


  // Inicializar MQ135
  for(int i=0;i<numSamples;i++) readings[i]=0;
  Serial.println("✅ Sensor MQ135 inicializado");


  mostrarPantalla();
  Serial.println("🎉 Sistema listo! Ingresa teléfono y kilos...");
}


// ======================
void loop() {
  leerBotonEncoder();
  if(moved){
    mostrarPantalla();
    moved=false;
  }


  if(etapa==2){
    int raw = analogRead(MQ135_PIN);
    float voltage = (raw / 4095.0) * 3.3;


    total -= readings[readIndex];
    readings[readIndex] = voltage;
    total += readings[readIndex];
    readIndex = (readIndex+1)%numSamples;
    float voltageAvg = total/numSamples;
    float ppm = voltageAvg*2000;


    Serial.print("📊 Voltaje promedio: "); Serial.print(voltageAvg,3);
    Serial.print(" V | PPM aprox: "); Serial.println(ppm);


    // Umbrales y alertas
    String mensaje = "";
    String estado = "";
    if(voltageAvg < 0.1){
      digitalWrite(LED_ALERT, LOW);
      digitalWrite(BUZZER, LOW);
      estado = "sin gas";
      Serial.println("✅ Estado: Sin gas - Remolacha fresca");
    }
    else if(voltageAvg < 0.19){
      digitalWrite(LED_ALERT, HIGH);
      digitalWrite(BUZZER, LOW);
      mensaje = "⚠ Olor leve detectado. Escribe /foto para verificar.";
      estado = "leve";
      Serial.println("⚠️ Estado: Leve - Inicio de descomposición");
    }
    else if(voltageAvg < 0.30){
      digitalWrite(LED_ALERT, HIGH);
      digitalWrite(BUZZER, HIGH);
      mensaje = "⚠ Olor moderado detectado. Escribe /foto para verificar.";
      estado = "moderado";
      Serial.println("🚨 Estado: Moderado - Descomposición avanzada");
    }
    else{
      digitalWrite(LED_ALERT, HIGH);
      digitalWrite(BUZZER, HIGH);
      mensaje = "⚠ Mucho gas detectado. Escribe /foto para verificar inmediatamente.";
      estado = "mucho gas";
      Serial.println("🔴 Estado: Mucho gas - Remolacha podrida");
    }


    // Enviar Telegram cada minuto
    if(mensaje != "" && millis() - lastAlertTime > ALERT_INTERVAL && userCount > 0){
      Serial.println("📨 Enviando alerta por Telegram...");
      for(int i=0; i<userCount; i++) bot.sendMessage(chatIds[i], mensaje, "");
      lastAlertTime = millis();
    }


    // Guardar en MySQL cada 30 segundos
    if(millis() - lastDBUpdate > DB_UPDATE_INTERVAL) {
      Serial.println("💾 Guardando lectura en base de datos...");
      guardarLecturaBD(voltageAvg, ppm, estado);
      lastDBUpdate = millis();
    }


  } else{
    digitalWrite(LED_ALERT, LOW);
    digitalWrite(BUZZER, LOW);
  }


  delay(200);
}
