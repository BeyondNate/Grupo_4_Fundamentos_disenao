#include <WiFi.h>
#include <HTTPClient.h>


const char* ssid = "Nx";
const char* password = "12345678";


const char* servidor = "http://10.13.225.89:5000/api/sensores"; 

// === Pin del sensor MQ-135 (salida analógica AO) ===
const int MQ135_PIN = 34;  // Pines ADC1 válidos: 32, 33, 34, 35, 36, 39

void setup() {
  Serial.begin(115200);
  Serial.println("Iniciando...");

  // Conectar al Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando al WiFi...");
  }
  Serial.println("¡Conectado al WiFi!");
  Serial.print("IP del ESP32: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Leer el valor analógico del MQ-135 (rango: 0 - 4095)
  int lectura = analogRead(MQ135_PIN);
  Serial.print("Lectura MQ-135: ");
  Serial.println(lectura);

  // Enviar datos al servidor Flask
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(servidor);
    http.addHeader("Content-Type", "application/json");

    // Crear JSON: {"nombre":"MQ135","valor":1234}
    String cuerpo = "{\"nombre\":\"MQ135\",\"valor\":" + String(lectura) + "}";

    int codigoRespuesta = http.POST(cuerpo);
    String respuesta = http.getString();

    Serial.print("Código HTTP: ");
    Serial.println(codigoRespuesta);
    Serial.print("Respuesta del servidor: ");
    Serial.println(respuesta);

    http.end();
  } else {
    Serial.println("Error: No hay conexión WiFi");
  }

  // Esperar 10 segundos antes de la próxima lectura
  delay(10000);
}