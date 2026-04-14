import serial
import csv
import time
import re

# --- CONFIGURACIÓN ---
PUERTO = '/dev/ttyUSB0'  
BAUDIOS = 9600
ARCHIVO_SALIDA = "analisis_sensor.csv"

def extraer_valor(texto):
    # Usa una expresión regular para buscar números (incluyendo decimales)
    match = re.search(r"[-+]?\d*\.\d+|\d+", texto)
    return float(match.group()) if match else None

try:
    ser = serial.Serial(PUERTO, BAUDIOS, timeout=1)
    time.sleep(2)
    
    print(f"Registrando datos en {ARCHIVO_SALIDA}... Presiona Ctrl+C para detener.")
    
    with open(ARCHIVO_SALIDA, mode='w', newline='') as archivo:
        writer = csv.writer(archivo)
    
        writer.writerow(["Timestamp", "Temperatura_C", "Humedad_Porcentaje"])
        
        temp_actual = None
        
        while True:
            if ser.in_waiting > 0:
                linea = ser.readline().decode('utf-8', errors='replace').strip()
                
                if "Temp C =" in linea:
                    temp_actual = extraer_valor(linea)
                
                elif "Hum % =" in linea:
                    hum_actual = extraer_valor(linea)
                    
                    # Cuando recibimos la humedad, asumimos que el par está completo
                    if temp_actual is not None:
                        timestamp = time.strftime("%Y-%m-%d %H:%M:%S")
                        writer.writerow([timestamp, temp_actual, hum_actual])
                        archivo.flush() # Fuerza el guardado en el disco
                        print(f"[{timestamp}] Guardado: T={temp_actual}°C, H={hum_actual}%")
                        
except KeyboardInterrupt:
    print("\nDetenido por el usuario.")
finally:
    if 'ser' in locals():
        ser.close()