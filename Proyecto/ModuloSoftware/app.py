from flask import Flask, request, jsonify, render_template
from flask_cors import CORS
import mysql.connector
from datetime import datetime, timedelta
import json
import time
import requests


app = Flask(__name__)
CORS(app)


# ========== CONFIGURACIÓN GALERÍA ESP32-CAM ==========
GALLERY_SCRIPT_URL = "https://script.google.com/macros/s/AKfycbxhqF2z-v4MzTtFpHqQwhGMBeUUuQXVrK80xyYA5wo2tXAbcXZWGCIs6Pp1jNfIOvg5eA/exec"


# ========== CONFIGURACIÓN MYSQL (SENSORES) ==========
db_config = {
   'host': 'localhost',
   'user': 'usuario_remolachas',
   'password': '12345678',
   'database': 'calidad_remolachas'
}




# ==================== FUNCIONES MySQL ====================


def verificar_conexion():
   """Verificar conexión a MySQL al inicio"""
   try:
       conn = mysql.connector.connect(**db_config)
       print("✅ Conexión MySQL exitosa")
       conn.close()
       return True
   except Exception as e:
       print(f"❌ Error conectando a MySQL: {e}")
       return False




def get_db_connection():
   """Obtener conexión a MySQL"""
   return mysql.connector.connect(**db_config)




def crear_tablas():
   """Crear tablas si no existen"""
   try:
       conn = get_db_connection()
       cursor = conn.cursor()


       cursor.execute("CREATE DATABASE IF NOT EXISTS calidad_remolachas")
       cursor.execute("USE calidad_remolachas")


       cursor.execute('''
           CREATE TABLE IF NOT EXISTS usuarios (
               id INT AUTO_INCREMENT PRIMARY KEY,
               telefono VARCHAR(15) UNIQUE,
               kilos INT,
               fecha_registro TIMESTAMP DEFAULT CURRENT_TIMESTAMP
           )
       ''')


       cursor.execute('''
           CREATE TABLE IF NOT EXISTS lecturas (
               id INT AUTO_INCREMENT PRIMARY KEY,
               telefono VARCHAR(15),
               voltage FLOAT,
               ppm FLOAT,
               estado VARCHAR(20),
               timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP
           )
       ''')


       conn.commit()
       print("✅ Tablas creadas/existen correctamente")


   except Exception as e:
       print(f"❌ Error creando tablas: {e}")
   finally:
       if 'cursor' in locals():
           cursor.close()
       if 'conn' in locals():
           conn.close()




# ==================== RUTAS ESP32 SENSORES ====================


@app.route('/registrar_usuario', methods=['POST'])
def registrar_usuario():
   """Recibir registro de usuario desde ESP32 normal"""
   try:
       data = request.get_json()
       telefono = data.get('telefono')
       kilos = data.get('kilos')


       print(f"📞 Registrando usuario: {telefono} con {kilos} kg")


       conn = get_db_connection()
       cursor = conn.cursor()
       cursor.execute("USE calidad_remolachas")


       cursor.execute('''
           INSERT INTO usuarios (telefono, kilos)
           VALUES (%s, %s)
           ON DUPLICATE KEY UPDATE kilos = VALUES(kilos)
       ''', (telefono, kilos))


       conn.commit()
       cursor.close()
       conn.close()


       print(f"✅ Usuario {telefono} registrado/actualizado")
       return jsonify({'message': 'Usuario registrado exitosamente'}), 200


   except Exception as e:
       print(f"❌ Error registrando usuario: {e}")
       return jsonify({'error': str(e)}), 500




@app.route('/guardar_lectura', methods=['POST'])
def guardar_lectura():
   """Recibir lecturas del sensor desde ESP32 normal"""
   try:
       data = request.get_json()
       telefono = data.get('telefono')
       voltage = data.get('voltage')
       ppm = data.get('ppm')
       estado = data.get('estado')


       print(f"📊 Guardando lectura: {telefono} - {voltage}V - {ppm}PPM - {estado}")


       conn = get_db_connection()
       cursor = conn.cursor()
       cursor.execute("USE calidad_remolachas")


       cursor.execute(
           'INSERT INTO lecturas (telefono, voltage, ppm, estado) VALUES (%s, %s, %s, %s)',
           (telefono, voltage, ppm, estado)
       )


       conn.commit()
       cursor.close()
       conn.close()


       print(f"✅ Lectura guardada para {telefono}")
       return jsonify({'message': 'Lectura guardada exitosamente'}), 200


   except Exception as e:
       print(f"❌ Error guardando lectura: {e}")
       return jsonify({'error': str(e)}), 500




@app.route('/datos', methods=['GET'])
def obtener_datos():
   """Obtener datos en tiempo real"""
   try:
       conn = get_db_connection()
       cursor = conn.cursor(dictionary=True)
       cursor.execute("USE calidad_remolachas")


       cursor.execute('''
           SELECT u.telefono, u.kilos, l.voltage, l.ppm, l.estado, l.timestamp
           FROM usuarios u
           INNER JOIN lecturas l ON u.telefono = l.telefono
           WHERE l.timestamp = (
               SELECT MAX(timestamp)
               FROM lecturas
               WHERE telefono = u.telefono
           )
       ''')


       datos = cursor.fetchall()
       cursor.close()
       conn.close()


       print(f"📨 Enviando {len(datos)} registros en tiempo real")
       return jsonify(datos), 200


   except Exception as e:
       print(f"❌ Error obteniendo datos: {e}")
       return jsonify({'error': str(e)}), 500




@app.route('/estadisticas', methods=['GET'])
def obtener_estadisticas():
   """Obtener estadísticas completas"""
   try:
       conn = get_db_connection()
       cursor = conn.cursor(dictionary=True)
       cursor.execute("USE calidad_remolachas")


       cursor.execute('''
           SELECT
               COUNT(*) as total_usuarios,
               SUM(CASE WHEN l.estado = 'sin gas' THEN 1 ELSE 0 END) as frescas,
               SUM(CASE WHEN l.estado = 'leve' THEN 1 ELSE 0 END) as inicio_descomposicion,
               SUM(CASE WHEN l.estado = 'moderado' THEN 1 ELSE 0 END) as descomposicion_avanzada,
               SUM(CASE WHEN l.estado = 'mucho gas' THEN 1 ELSE 0 END) as podridas,
               AVG(l.ppm) as ppm_promedio,
               MAX(l.ppm) as ppm_maximo,
               MIN(l.ppm) as ppm_minimo
           FROM usuarios u
           INNER JOIN lecturas l ON u.telefono = l.telefono
           WHERE l.timestamp = (
               SELECT MAX(timestamp)
               FROM lecturas
               WHERE telefono = u.telefono
           )
       ''')
       stats = cursor.fetchone()


       cursor.execute('''
           SELECT
               DATE_FORMAT(timestamp, '%Y-%m-%d %H:00:00') as hora,
               AVG(ppm) as ppm_promedio,
               COUNT(*) as lecturas
           FROM lecturas
           WHERE timestamp >= NOW() - INTERVAL 24 HOUR
           GROUP BY hora
           ORDER BY hora
       ''')
       evolucion = cursor.fetchall()


       cursor.execute('''
           SELECT
               CASE
                   WHEN kilos <= 10 THEN '0-10 kg'
                   WHEN kilos <= 20 THEN '11-20 kg'
                   WHEN kilos <= 30 THEN '21-30 kg'
                   WHEN kilos <= 40 THEN '31-40 kg'
                   ELSE '41-50 kg'
               END as rango_kilos,
               COUNT(*) as cantidad,
               AVG(l.ppm) as ppm_promedio
           FROM usuarios u
           INNER JOIN lecturas l ON u.telefono = l.telefono
           WHERE l.timestamp = (
               SELECT MAX(timestamp)
               FROM lecturas
               WHERE telefono = u.telefono
           )
           GROUP BY rango_kilos
       ''')
       distribucion_kilos = cursor.fetchall()


       cursor.execute('''
           SELECT telefono, estado, ppm, timestamp
           FROM lecturas
           WHERE timestamp >= NOW() - INTERVAL 1 HOUR
           AND estado != 'sin gas'
           ORDER BY timestamp DESC
           LIMIT 10
       ''')
       alertas_recientes = cursor.fetchall()


       cursor.close()
       conn.close()


       return jsonify({
           'resumen': stats,
           'evolucion': evolucion,
           'distribucion_kilos': distribucion_kilos,
           'alertas_recientes': alertas_recientes
       }), 200


   except Exception as e:
       print(f"❌ Error generando estadísticas: {e}")
       return jsonify({'error': str(e)}), 500




@app.route('/historial/<telefono>', methods=['GET'])
def obtener_historial(telefono):
   """Obtener historial de un usuario"""
   try:
       conn = get_db_connection()
       cursor = conn.cursor(dictionary=True)


       cursor.execute('''
           SELECT voltage, ppm, estado, timestamp
           FROM lecturas
           WHERE telefono = %s
           ORDER BY timestamp DESC
           LIMIT 50
       ''', (telefono,))


       historial = cursor.fetchall()
       cursor.close()
       conn.close()


       return jsonify(historial), 200


   except Exception as e:
       return jsonify({'error': str(e)}), 500




# ==================== RUTAS GALERÍA ESP32-CAM ====================


@app.route('/api/gallery/photos')
def get_photos():
   """Obtener lista de fotos desde Google Drive"""
   try:
       print("📸 Obteniendo fotos desde Drive...")


       response = requests.get(GALLERY_SCRIPT_URL, timeout=10)


       if response.status_code == 200:
           data = response.json()
           print(f"✅ {data.get('count', 0)} fotos obtenidas")
           return jsonify(data)
       else:
           return jsonify({'error': 'Error al obtener fotos'}), 500


   except Exception as e:
       print(f"❌ Error: {e}")
       return jsonify({'error': str(e)}), 500




# ==================== RUTAS WEB ====================


@app.route('/')
def index():
   """Dashboard de sensores"""
   return render_template('index.html')




@app.route('/galeria')
def galeria():
   """Galería ESP32-CAM"""
   return render_template('galeria.html')




@app.route('/status', methods=['GET'])
def status():
   """Estado del servidor"""
   try:
       conn = get_db_connection()
       cursor = conn.cursor()
       cursor.execute("SELECT 1")
       cursor.close()
       conn.close()
       return jsonify({
           'status': 'OK',
           'database': 'Connected',
           'timestamp': datetime.now().isoformat()
       })
   except Exception as e:
       return jsonify({'status': 'Error', 'database': str(e)}), 500




@app.route('/test', methods=['GET'])
def test():
   """Prueba simple"""
   return jsonify({
       'message': '¡Servidor Flask funcionando!',
       'timestamp': datetime.now().isoformat()
   })




# ==================== INICIO ====================


if __name__ == '__main__':
   print("=" * 60)
   print("🚀 Iniciando servidor Flask...")
   print("=" * 60)


   if verificar_conexion():
       crear_tablas()
       print("\n✅ Servidor listo\n")
       print("📍 URLs:")
       print("   🌐 Dashboard:  http://localhost:5000")
       print("   📸 Galería:    http://localhost:5000/galeria")
       print("   📊 Status:     http://localhost:5000/status")
       print("\n" + "=" * 60)


       app.run(host='0.0.0.0', port=5000, debug=True)
   else:
       print("\n❌ Error con MySQL")
       print("=" * 60)
