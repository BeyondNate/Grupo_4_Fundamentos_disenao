# ALI - SMARTFRESH: Sistema de Monitoreo y Control del Estado de la Beterraga - Módulo de Software

## ESP32 – Sensor MQ135

int pinMQ = 34;

void setup() {
  Serial.begin(115200);
}

void loop() {
  int valor = analogRead(pinMQ);
  Serial.println(valor);
  delay(500);
}

## ESP32-CAM – Captura y envío de fotografías

if (text == "/foto") {
  bot.sendMessage(chat_id, "Tomando foto...");
  takeAndUploadPhoto(chat_id);
}

## Backend Flask – Recepción de Fotos

@app.route('/upload', methods=['POST'])
def upload_photo():
    file = request.files['photo']
    file.save("uploads/" + file.filename)
    return "OK"

## Google Apps Script – Subida de Imágenes a Drive

function doPost(e) {
  var file = DriveApp.createFile(
    e.parameter.filename,
    e.parameter.data,
    "image/jpeg"
  );
  return ContentService.createTextOutput(file.getId());
}

## Google Apps Script – Listar Imágenes

function getImages() {
  var folder = DriveApp.getFolderById("TU_FOLDER_ID");
  var files = folder.getFiles();
  var data = [];

  while (files.hasNext()) {
    var img = files.next();
    data.push(img.getUrl());
  }

  return ContentService.createTextOutput(JSON.stringify(data));
}

## Web – Página Principal

<button onclick="takePicture()">Tomar Foto</button>
<div id="response"></div>

## Web – Galería de Imágenes

<div class="gallery"></div>
<script src="script.js"></script>

## Base de Datos MySQL

CREATE DATABASE prototipo;
USE prototipo;

CREATE TABLE lecturas (
    id INT AUTO_INCREMENT PRIMARY KEY,
    valor_sensor FLOAT,
    fecha DATETIME
);
