import pandas as pd
import os

def analizar_datos(archivo_csv):
    # Verificar si el archivo existe
    if not os.path.exists(archivo_csv):
        print(f"Error: No se encontró el archivo '{archivo_csv}'")
        return

    # Cargar los datos
    df = pd.read_csv(archivo_csv)

    df['Timestamp'] = pd.to_datetime(df['Timestamp'])

    print("-" * 40)
    print("      RESUMEN DE LECTURAS SHT31")
    print("-" * 40)

    # Cálculo de estadísticas para Temperatura
    stats_temp = {
        "Promedio": df["Temperatura_C"].mean(),
        "Mínima": df["Temperatura_C"].min(),
        "Máxima": df["Temperatura_C"].max(),
        "Desviación Est.": df["Temperatura_C"].std()
    }

    # Cálculo de estadísticas para Humedad
    stats_hum = {
        "Promedio": df["Humedad_Porcentaje"].mean(),
        "Mínima": df["Humedad_Porcentaje"].min(),
        "Máxima": df["Humedad_Porcentaje"].max(),
        "Desviación Est.": df["Humedad_Porcentaje"].std()
    }

    print(f"Total de muestras recolectadas: {len(df)}")
    print("\n--- TEMPERATURA (°C) ---")
    for key, val in stats_temp.items():
        print(f"{key}: {val:.2f}")

    print("\n--- HUMEDAD (%) ---")
    for key, val in stats_hum.items():
        print(f"{key}: {val:.2f}")
    
    print("-" * 40)

if __name__ == "__main__":
    analizar_datos("analisis_sensor.csv")