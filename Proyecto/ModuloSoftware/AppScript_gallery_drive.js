https://script.google.com/macros/s/AKfycbz0wgHC1SEaUp7GL5pa1Y93qwFD2VZSPXreRaxbibtcENiMjHnn913tA6_f-PXEX9dnzw/exec

const FOLDER_ID = "1usCe7jZw3re85jDxBwQ-DNHohWFh26Ig";

function doGet(e) {
  try {
    return listPhotos();
  } catch (error) {
    return ContentService
      .createTextOutput(JSON.stringify({ 
        error: error.toString(),
        photos: [],
        count: 0
      }))
      .setMimeType(ContentService.MimeType.JSON);
  }
}

function listPhotos() {
  try {
    var folder = DriveApp.getFolderById(FOLDER_ID);
    var files = folder.getFilesByType(MimeType.JPEG);
    
    var photos = [];
    var count = 0;
    
    while (files.hasNext() && count < 500) {
      var file = files.next();
      
      // Crear enlaces públicos de descarga
      var downloadUrl = `https://drive.google.com/uc?export=download&id=${file.getId()}`;
      var thumbnailUrl = `https://drive.google.com/thumbnail?id=${file.getId()}&sz=w400`;
      var viewUrl = `https://drive.google.com/file/d/${file.getId()}/view`;
      
      photos.push({
        id: file.getId(),
        name: file.getName(),
        date: file.getDateCreated().toISOString(),
        size: file.getSize(),
        thumbnail: thumbnailUrl,
        download: downloadUrl,
        view: viewUrl,
        url: file.getUrl()
      });
      
      count++;
    }
    
    photos.sort(function(a, b) {
      return new Date(b.date) - new Date(a.date);
    });
    
    Logger.log("📸 Listadas " + photos.length + " fotos");
    
    return ContentService
      .createTextOutput(JSON.stringify({ 
        photos: photos, 
        count: photos.length,
        folder_id: FOLDER_ID
      }))
      .setMimeType(ContentService.MimeType.JSON);
      
  } catch (error) {
    Logger.log("❌ Error: " + error.toString());
    throw error;
  }
}
