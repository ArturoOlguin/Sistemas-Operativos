import os
import time

# Lista de archivos PDF a abrir, especifica las rutas de tus archivos
archivos_pdf = ["Ejemplo.pdf", "Ejemplo2.pdf"]


def archivo_esta_abierto(archivo):
    try:
        with open(archivo, "r+"):
            return False  # El archivo está cerrado
    except IOError:
        return True  # El archivo está en uso

for archivo in archivos_pdf:
    print(f"Abriendo {archivo}...")

    # Abre el archivo PDF con el visor predeterminado del sistema
    os.startfile(archivo)  # En Windows. En Linux/Mac puedes usar 'open' o 'xdg-open'
    
    # Espera hasta que el archivo PDF sea cerrado por el usuario
while True:
        # Verifica si el archivo está abierto en el sistema
        # Esto se logra al intentar abrir el archivo en modo exclusivo.
        try:
            with open(archivo, "r+"):
                pass
        except IOError:
            # Si el archivo no puede abrirse en modo exclusivo, espera
            print(f"Esperando que se cierre {archivo}...")
            time.sleep(5)
        else:
            # Sale del bucle si el archivo puede abrirse en modo exclusivo
            print(f"{archivo} ha sido cerrado.")
            break
