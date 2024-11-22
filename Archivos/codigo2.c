#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

// Función para abrir un archivo PDF y esperar a que se cierre
void abrir_pdf(const char *ruta_pdf) {
    SHELLEXECUTEINFO shExInfo = {0};
    shExInfo.cbSize = sizeof(SHELLEXECUTEINFO);
    shExInfo.fMask = SEE_MASK_NOCLOSEPROCESS; // Permite capturar el proceso
    shExInfo.hwnd = NULL;
    shExInfo.lpVerb = "open";                 // Acción: abrir
    shExInfo.lpFile = ruta_pdf;               // Archivo a abrir
    shExInfo.lpParameters = NULL;             // Sin parámetros adicionales
    shExInfo.lpDirectory = NULL;              // Directorio de trabajo
    shExInfo.nShow = SW_SHOWNORMAL;           // Mostrar ventana de forma normal

    if (ShellExecuteEx(&shExInfo)) {
        printf("Archivo abierto: %s\n", ruta_pdf);

        // Esperar a que el proceso asociado termine
        if (shExInfo.hProcess != NULL) {
            WaitForSingleObject(shExInfo.hProcess, INFINITE); // Espera indefinida
            CloseHandle(shExInfo.hProcess);                  // Liberar el handle
        }
    } else {
        fprintf(stderr, "Error al abrir el archivo: %s\n", ruta_pdf);
    }
}

int main() {
    const char *archivos_pdf[] = {
        "Uno\\Manejador_de_Interrupciones.pdf",
        "Dos\\Controladores_de_los_dispositivos.pdf",
        "Tres\\Software_Modo_Usuario.pdf",
    };

    for (int i = 0; i < 4; i++) {
        printf("Abriendo archivo: %s\n", archivos_pdf[i]);
        abrir_pdf(archivos_pdf[i]);
    }

    printf("Todos los archivos han sido cerrados. Fin del programa.\n");
    return 0;
}
