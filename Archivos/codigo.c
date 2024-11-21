#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

// Función para abrir un archivo PDF y esperar a que se cierre
void abrir_pdf(const char *ruta_pdf) {
    // Usamos ShellExecute para abrir el PDF con el programa predeterminado
    HINSTANCE resultado = ShellExecute(NULL, "open", ruta_pdf, NULL, NULL, SW_SHOWNORMAL);

    // Verificamos si el archivo se abrió correctamente
    if (resultado <= (HINSTANCE)32) {
        fprintf(stderr, "Error al intentar abrir el archivo: %s\n", ruta_pdf);
    } else {
        printf("Se abrió el archivo: %s\n", ruta_pdf);
    }

    // Esperar a que el usuario cierre el visor
    printf("Cierra el archivo para continuar...\n");
    getchar();
}

int main() {
    const char *ruta_base = "D:\\ESCOM\\Semestres\\4to Semestre\\SO\\Ejercicio";
    const char *archivos_pdf[] = {
        "\\Uno\\Ejemplo1.pdf",
        "\\Dos\\Ejemplo2.pdf",
        "\\Tres\\Ejemplo3.pdf",
        "\\Cuatro\\Ejemplo4.pdf"
    };

    for (int i = 0; i < 4; i++) {
        char ruta_completa[512];
        snprintf(ruta_completa, sizeof(ruta_completa), "%s%s", ruta_base, archivos_pdf[i]);
        printf("Abriendo archivo: %s\n", ruta_completa);
        abrir_pdf(ruta_completa);
    }

    printf("Todos los archivos han sido cerrados. Fin del programa.\n");
    return 0;
}
