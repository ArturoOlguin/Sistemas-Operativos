import os
import time

# Lista de archivos PDF en la carpeta "inves"
archivos_pdf = ["Ejemplo.pdf", "C:\Ejercicio\inves2\Ejemplo 2.pdf"]

def archivo_esta_abierto(archivo):
    try:
        with open(archivo, "r+"):
            return False  # El archivo está cerrado
    except IOError:
        return True  # El archivo está en uso

for archivo in archivos_pdf:
    print(f"Abriendo {archivo}...")
    os.startfile(archivo)  # Abre el archivo en Windows con el visor predeterminado
    
    # Espera hasta que el archivo se cierre
    while archivo_esta_abierto(archivo):
        print(f"Esperando que se cierre {archivo}...")
        time.sleep(2)  # Espera 2 segundos antes de verificar nuevamente

    print(f"{archivo} ha sido cerrado. Abriendo el siguiente PDF...\n")