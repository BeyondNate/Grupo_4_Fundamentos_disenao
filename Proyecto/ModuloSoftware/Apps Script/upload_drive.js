function doPost(e) {
  try {
    var data = JSON.parse(e.postData.contents);


    // validar token
    if (data.token !== "BMMGR") {
      return ContentService
        .createTextOutput(JSON.stringify({ status: "TOKEN_INVALIDO" }))
        .setMimeType(ContentService.MimeType.JSON);
    }


    // carpeta destino
    var folder = DriveApp.getFolderById(data.folderId);


    // decodificar imagen base64
    var bytes = Utilities.base64Decode(data.image);
    var blob = Utilities.newBlob(bytes, "image/jpeg", data.filename);


    // guardar archivo en Drive
    folder.createFile(blob);


    // RESPUESTA JSON REAL
    return ContentService
      .createTextOutput(JSON.stringify({ status: "OK" }))
      .setMimeType(ContentService.MimeType.JSON);


  } catch (err) {
    return ContentService
      .createTextOutput(JSON.stringify({ status: "ERROR", msg: err }))
      .setMimeType(ContentService.MimeType.JSON);
  }
}


function doGet(e) {
  return ContentService
    .createTextOutput(JSON.stringify({ status: "GET_OK" }))
    .setMimeType(ContentService.MimeType.JSON);
}
