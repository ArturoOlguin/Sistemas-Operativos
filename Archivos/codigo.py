import os
import subprocess

def abrir_pdf_secuencialmente():
    # Ruta base donde están las carpetas
    ruta_base = r"D:\ESCOM\Semestres\4to Semestre\SO\Ejercicio"

    # Lista de archivos PDF en el orden en que se deben abrir
    archivos_pdf = [
        os.path.join(ruta_base, "Uno", "Ejemplo1.pdf"),
        os.path.join(ruta_base, "Dos", "Ejemplo2.pdf"),
        os.path.join(ruta_base, "Tres", "Ejemplo3.pdf"),
        os.path.join(ruta_base, "Cuatro", "Ejemplo4.pdf"),
    ]
    
    # Abrimos cada archivo secuencialmente
    for archivo in archivos_pdf:
        # Verificamos si el archivo existe antes de intentar abrirlo
        if os.path.exists(archivo):
            print(f"Abriendo {archivo}")
            # Abre el archivo y espera a que se cierre
            with subprocess.Popen([archivo], shell=True) as proceso:
                proceso.wait()  # Espera hasta que el archivo se cierre
            print(f"Cerraste {archivo}")
        else:
            print(f"No se encontró el archivo: {archivo}")

    print("Todos los archivos han sido cerrados. Fin del programa.")

# Ejecutar la función
abrir_pdf_secuencialmente()
