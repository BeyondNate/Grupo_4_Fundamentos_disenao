#define MQ135_PIN 34
void setup() {
Serial.begin(115200);
delay(1000);
Serial.println("Iniciando lectura del sensor MQ-135...");
}
void loop() {
int valorAnalogico = analogRead(MQ135_PIN);
float voltaje (valorAnalogico / 4095.0) * 3.3;
Serial.print("Lectura MQ-135: ");
Serial.print(valorAnalogico);
Serial.print(" | Voltaje: ");
Serial.print(voltaje);
Serial.println(" V");
delay(1000);
}
