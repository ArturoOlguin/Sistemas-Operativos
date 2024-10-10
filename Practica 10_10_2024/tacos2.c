#include <stdio.h>

#define NUM_BLOQUES 5 // Número de bloques de memoria
#define NO_ASIGNADO -1 // Valor que representa un bloque no asignado

// Estructura para representar un proceso
typedef struct {
    int id;
    int size;
} Proceso;

// Función para mostrar el estado de la memoria
void mostrarEstadoMemoria(int bloques[], int tamBloques[], int numBloques) {
    printf("\nEstado de la memoria:\n");
    for (int i = 0; i < numBloques; i++) {
        if (bloques[i] == NO_ASIGNADO) {
            printf("Bloque %d (Tamaño %d): Libre\n", i, tamBloques[i]);
        } else {
            printf("Bloque %d (Tamaño %d): Proceso %d asignado\n", i, tamBloques[i], bloques[i]);
        }
    }
    printf("\n");
}

// Función para asignar un proceso a un bloque de memoria adecuado
void asignarProceso(int bloques[], int tamBloques[], int numBloques, Proceso p) {
    int asignado = 0;

    for (int i = 0; i < numBloques; i++) {
        // Verificar si el bloque está libre y es lo suficientemente grande para el proceso
        if (bloques[i] == NO_ASIGNADO && tamBloques[i] >= p.size) {
            bloques[i] = p.id; // Asignar proceso al bloque
            printf("Proceso %d asignado al bloque %d\n", p.id, i);
            asignado = 1;
            break;
        }
    }

    if (!asignado) {
        printf("No hay bloques disponibles para el proceso %d (Tamaño %d)\n", p.id, p.size);
    }
}

// Función para liberar un bloque de memoria
void liberarMemoria(int bloques[], int tamBloques[], int numBloques, int idProceso) {
    int liberado = 0;

    for (int i = 0; i < numBloques; i++) {
        if (bloques[i] == idProceso) {
            bloques[i] = NO_ASIGNADO; // Liberar el bloque
            printf("Proceso %d liberado del bloque %d\n", idProceso, i);
            liberado = 1;
            break;
        }
    }

    if (!liberado) {
        printf("El proceso %d no está asignado a ningún bloque\n", idProceso);
    }
}

int main() {
    // Tamaños de los bloques de memoria
    int tamBloques[NUM_BLOQUES] = {100, 200, 300, 400, 500};
    // Estado de los bloques: -1 indica que el bloque está libre
    int bloques[NUM_BLOQUES] = {NO_ASIGNADO, NO_ASIGNADO, NO_ASIGNADO, NO_ASIGNADO, NO_ASIGNADO};

    // Crear algunos procesos
    Proceso procesos[] = {
        {1, 150}, // Proceso 1, tamaño 150
        {2, 450}, // Proceso 2, tamaño 450
        {3, 120}, // Proceso 3, tamaño 120
        {4, 350}, // Proceso 4, tamaño 350
    };

    int numProcesos = sizeof(procesos) / sizeof(procesos[0]);

    // Asignar los procesos a la memoria
    for (int i = 0; i < numProcesos; i++) {
        asignarProceso(bloques, tamBloques, NUM_BLOQUES, procesos[i]);
        mostrarEstadoMemoria(bloques, tamBloques, NUM_BLOQUES);
    }

    // Liberar el proceso 2 y mostrar el estado de la memoria
    liberarMemoria(bloques, tamBloques, NUM_BLOQUES, 2);
    mostrarEstadoMemoria(bloques, tamBloques, NUM_BLOQUES);

    return 0;
}