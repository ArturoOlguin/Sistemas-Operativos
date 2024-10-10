/*Es un programa q copia archivos simultáneamente , sólo utiliza hilos y el join, además de abrir archivos con el file open y esas mmdas*/

#include <stdio.h>   // Librería para entrada/salida estándar
#include <stdlib.h>  // Librería para funciones estándar de C
#include <pthread.h> // Librería para trabajar con hilos

#define MAX_FILES 3  // Número máximo de archivos a copiar
#define BUFFER_SIZE 1024 // Tamaño del buffer para la copia

// Estructura para pasar los argumentos a los hilos
typedef struct {
    char *src;  // Archivo fuente
    char *dest; // Archivo destino
} FileCopyArgs;

// Función que cada hilo ejecutará para copiar un archivo
void *copy_file(void *args) {
    FileCopyArgs *file_args = (FileCopyArgs *)args;  // Se obtienen los argumentos de la estructura
    FILE *src_file = fopen(file_args->src, "rb");    // Abrimos el archivo fuente en modo lectura binaria
    FILE *dest_file = fopen(file_args->dest, "wb");  // Abrimos el archivo destino en modo escritura binaria

    // Si ocurre un error al abrir los archivos, se muestra un mensaje de error
    if (!src_file || !dest_file) {
        perror("Error opening files");
        return NULL;
    }

    char buffer[BUFFER_SIZE]; // Buffer para almacenar datos leídos del archivo
    size_t bytes;
    // Mientras haya datos en el archivo fuente, leemos y escribimos en el archivo destino
    while ((bytes = fread(buffer, 1, BUFFER_SIZE, src_file)) > 0) {
        fwrite(buffer, 1, bytes, dest_file);
    }

    // Cerramos los archivos
    fclose(src_file);
    fclose(dest_file);
    return NULL; // Terminamos el hilo
}

int main() {
    pthread_t threads[MAX_FILES]; // Arreglo para almacenar los identificadores de los hilos
    // Argumentos para los hilos, especificando los archivos fuente y destino
    FileCopyArgs file_args[MAX_FILES] = {
        {"file1.txt", "copy_file1.txt"},
        {"file2.txt", "copy_file2.txt"},
        {"file3.txt", "copy_file3.txt"}
    };

    // Crear los hilos, cada uno ejecuta la función copy_file con los argumentos correspondientes
    for (int i = 0; i < MAX_FILES; i++) {
        pthread_create(&threads[i], NULL, copy_file, &file_args[i]);
    }

    // Esperar a que todos los hilos terminen su ejecución
    for (int i = 0; i < MAX_FILES; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Archivos copiados exitosamente.\n"); // Mensaje de éxito
    return 0; // Terminar el programa
}