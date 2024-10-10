#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_MEMORIA 1024  // Tamaño de la memoria principal en MB
#define TAM_DISCO 2048    // Tamaño de la memoria de intercambio (disco) en MB
#define TAM_BLOQUE 1      // Tamaño de un bloque de memoria en MB

// Estructura de un proceso
typedef struct {
    int id;         // ID del proceso
    int tamano;     // Tamaño en MB
    int llegada;    // Tiempo de llegada
    int finalizacion; // Tiempo de finalización
} Proceso;

// Estructura para la lista enlazada de memoria
typedef struct BloqueMemoria {
    int tamano;                  // Tamaño del bloque
    int esta_libre;              // 1 si está libre, 0 si está ocupado
    struct BloqueMemoria *siguiente; // Siguiente bloque en la lista
    Proceso *proceso;            // Proceso asignado al bloque
} BloqueMemoria;

// Variables globales para la memoria y disco
BloqueMemoria *memoria = NULL;  // Lista enlazada para la memoria principal
BloqueMemoria *disco = NULL;    // Lista enlazada para el área de intercambio
int mapa_memoria[TAM_MEMORIA / TAM_BLOQUE];  // Mapa de bits de la memoria
int mapa_disco[TAM_DISCO / TAM_BLOQUE];      // Mapa de bits de la memoria de intercambio

// Función para inicializar la memoria y el disco
void inicializar_memoria() {
    // Inicializa la lista de bloques de memoria como un bloque completo libre
    memoria = (BloqueMemoria*) malloc(sizeof(BloqueMemoria));
    memoria->tamano = TAM_MEMORIA;
    memoria->esta_libre = 1;
    memoria->siguiente = NULL;
    memoria->proceso = NULL;

    // Inicializa la lista de bloques de disco como un bloque completo libre
    disco = (BloqueMemoria*) malloc(sizeof(BloqueMemoria));
    disco->tamano = TAM_DISCO;
    disco->esta_libre = 1;
    disco->siguiente = NULL;
    disco->proceso = NULL;

    // Inicializa el mapa de bits de la memoria
    memset(mapa_memoria, 0, sizeof(mapa_memoria));
    memset(mapa_disco, 0, sizeof(mapa_disco));
}

// Función para asignar memoria usando First Fit
BloqueMemoria* asignar_memoria(Proceso *proc, int tamano) {
    BloqueMemoria *actual = memoria;
    while (actual != NULL) {
        if (actual->esta_libre && actual->tamano >= tamano) {
            // Si el bloque es suficiente, dividirlo si es necesario
            if (actual->tamano > tamano) {
                BloqueMemoria *nuevo_bloque = (BloqueMemoria*) malloc(sizeof(BloqueMemoria));
                nuevo_bloque->tamano = actual->tamano - tamano;
                nuevo_bloque->esta_libre = 1;
                nuevo_bloque->siguiente = actual->siguiente;
                actual->siguiente = nuevo_bloque;
            }
            // Asignar el bloque
            actual->tamano = tamano;
            actual->esta_libre = 0;
            actual->proceso = proc;
            return actual;
        }
        actual = actual->siguiente;
    }
    return NULL;  // No hay memoria disponible
}

// Función para liberar memoria
void liberar_memoria(BloqueMemoria *bloque) {
    bloque->esta_libre = 1;
    bloque->proceso = NULL;
    // Combinar bloques libres adyacentes
    BloqueMemoria *actual = memoria;
    while (actual != NULL && actual->siguiente != NULL) {
        if (actual->esta_libre && actual->siguiente->esta_libre) {
            actual->tamano += actual->siguiente->tamano;
            BloqueMemoria *temp = actual->siguiente;
            actual->siguiente = temp->siguiente;
            free(temp);
        }
        actual = actual->siguiente;
    }
}

// Función para mover un proceso al disco (FIFO)
void mover_a_disco(Proceso *proc) {
    BloqueMemoria *actual = disco;
    while (actual != NULL) {
        if (actual->esta_libre && actual->tamano >= proc->tamano) {
            actual->tamano = proc->tamano;
            actual->esta_libre = 0;
            actual->proceso = proc;
            break;
        }
        actual = actual->siguiente;
    }
}

// Función para imprimir el estado de la memoria
void imprimir_estado_memoria() {
    BloqueMemoria *actual = memoria;
    printf("Estado de la memoria principal:\n");
    while (actual != NULL) {
        printf("Bloque de %d MB - %s\n", actual->tamano, actual->esta_libre ? "Libre" : "Ocupado");
        actual = actual->siguiente;
    }
}

// Función para imprimir el estado del disco
void imprimir_estado_disco() {
    BloqueMemoria *actual = disco;
    printf("Estado del disco:\n");
    while (actual != NULL) {
        printf("Bloque de %d MB - %s\n", actual->tamano, actual->esta_libre ? "Libre" : "Ocupado");
        actual = actual->siguiente;
    }
}

// Simulación básica de asignación y liberación
int main() {
    inicializar_memoria();

    Proceso p1 = {1, 200, 0, 10};  // Proceso 1 (200 MB)
    Proceso p2 = {2, 300, 2, 15};  // Proceso 2 (300 MB)
    Proceso p3 = {3, 600, 5, 20};  // Proceso 3 (600 MB)

    // Asignar memoria para los procesos
    asignar_memoria(&p1, p1.tamano);
    asignar_memoria(&p2, p2.tamano);
    
    // Mostrar el estado de la memoria
    imprimir_estado_memoria();

    // Intentar asignar el proceso 3, pero no cabe en la memoria
    if (asignar_memoria(&p3, p3.tamano) == NULL) {
        printf("No hay suficiente memoria. Moviendo proceso al disco.\n");
        mover_a_disco(&p3);
    }

    // Mostrar el estado del disco
    imprimir_estado_disco();

    // Liberar el proceso 1 y mostrar la memoria
    liberar_memoria(memoria);
    imprimir_estado_memoria();

    return 0;
}
