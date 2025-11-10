from flask import Flask, jsonify, request
import mysql.connector
from datetime import datetime

app = Flask(__name__)

DB_CONFIG = {
    'host': 'localhost',
    'user': 'br_ad',
    'password': 'ranita',
    'database': 'sensores_db'
}

def get_db_connection():
    return mysql.connector.connect(**DB_CONFIG)

# === Endpoint para mostrar datos ===
@app.route('/api/sensores', methods=['GET'])
def get_sensores():
    try:
        conn = get_db_connection()
        cursor = conn.cursor(dictionary=True)
        cursor.execute("SELECT * FROM lecturas ORDER BY fecha_lectura DESC LIMIT 50")
        data = cursor.fetchall()
        cursor.close()
        conn.close()
        return jsonify(data)
    except Exception as e:
        return jsonify({"error": str(e)}), 500

# === Endpoint para recibir datos de sensores ===
@app.route('/api/sensores', methods=['POST'])
def add_lectura():
    try:
        data = request.get_json()
        nombre = data.get('nombre')
        valor = data.get('valor')

        if not nombre or valor is None:
            return jsonify({"error": "Faltan 'nombre' o 'valor'"}), 400

        conn = get_db_connection()
        cursor = conn.cursor()
        query = "INSERT INTO lecturas (nombre, valor) VALUES (%s, %s)"
        cursor.execute(query, (nombre, float(valor)))
        conn.commit()
        cursor.close()
        conn.close()

        return jsonify({"status": "ok", "mensaje": "Dato guardado"}), 201
    except Exception as e:
        return jsonify({"error": str(e)}), 500

# === Página web ===
@app.route('/')
def index():
    return '''
    <!DOCTYPE html>
    <html>
    <head>
        <title>Sensores Reales</title>
        <meta charset="utf-8">
        <style>
            body { font-family: Arial; margin: 30px; background: #f9f9f9; }
            h1 { color: #2c3e50; }
            table { width: 100%; border-collapse: collapse; margin-top: 20px; }
            th, td { padding: 12px; text-align: left; border-bottom: 1px solid #ddd; }
            th { background: #3498db; color: white; }
            tr:hover { background: #f1f1f1; }
        </style>
    </head>
    <body>
        <h1> Datos de Sensores Reales</h1>
        <div id="mensaje"></div>
        <table>
            <thead>
                <tr><th>ID</th><th>Nombre</th><th>Valor</th><th>Fecha</th></tr>
            </thead>
            <tbody id="tabla-body"></tbody>
        </table>

        <script>
            function cargarDatos() {
                fetch('/api/sensores')
                    .then(res => res.json())
                    .then(data => {
                        const tbody = document.getElementById('tabla-body');
                        tbody.innerHTML = '';
                        data.forEach(item => {
                            const tr = `<tr>
                                <td>${item.id}</td>
                                <td>${item.nombre}</td>
                                <td>${item.valor}</td>
                                <td>${new Date(item.fecha_lectura).toLocaleString()}</td>
                            </tr>`;
                            tbody.innerHTML += tr;
                        });
                    })
                    .catch(err => {
                        document.getElementById('mensaje').innerText = 'Error al cargar datos';
                    });
            }

            // Cargar al inicio y cada 5 segundos
            cargarDatos();
            setInterval(cargarDatos, 5000);
        </script>
    </body>
    </html>
    '''

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)