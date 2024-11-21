import os
import subprocess

def abrir_pdf(ruta_pdf):
    try:
        # Abrir el PDF con el programa predeterminado
        proceso = subprocess.Popen(ruta_pdf, shell=True)
        print(f"Archivo abierto: {ruta_pdf}")
        
        # Esperar a que el proceso termine
        proceso.wait()
        print(f"Archivo cerrado: {ruta_pdf}")
    except Exception as e:
        print(f"Error al abrir el archivo {ruta_pdf}: {e}")

def main():
    archivos_pdf = [
        "Uno/Ejemplo1.pdf",
        "Dos/Ejemplo2.pdf",
        "Tres/Ejemplo3.pdf",
        "Cuatro/Ejemplo4.pdf"
    ]
    
    for archivo in archivos_pdf:
        print(f"Abriendo archivo: {archivo}")
        abrir_pdf(archivo)

    print("Todos los archivos han sido cerrados. Fin del programa.")

if __name__ == "__main__":
    main()
