/*En una fábrica de producción, se necesita gestionar de manera eficiente los bloques de memoria utilizados para almacenar información sobre los productos fabricados. Cada bloque de memoria debe contener un identificador (ID) único y un tamaño que represente la cantidad de información que puede almacenar, siendo este tamaño un múltiplo de 10.*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Definición de una estructura para un bloque de memoria
typedef struct MemoryBlock {
    int id;                     // Identificador del bloque de memoria
    size_t size;                // Tamaño del bloque de memoria
    struct MemoryBlock *next;   // Puntero al siguiente bloque en la lista
} MemoryBlock;

// Función para inicializar un bloque de memoria
MemoryBlock* createMemoryBlock(int id, size_t size) {
    MemoryBlock *block = (MemoryBlock *)malloc(sizeof(MemoryBlock));
    if (block != NULL) {
        block->id = id;
        block->size = size;
        block->next = NULL;
    }
    return block;
}

// Función para liberar un bloque de memoria
void freeMemoryBlock(MemoryBlock *block) {
    free(block);
}

// Función para imprimir la lista de bloques de memoria
void printMemoryList(MemoryBlock *head) {
    MemoryBlock *current = head;
    printf("Lista de bloques de memoria:\n");
    while (current != NULL) {
        printf("ID: %d, Tamaño: %zu\n", current->id, current->size);
        current = current->next;
    }
}

int main() {
    MemoryBlock *memoryList = NULL;  // Lista enlazada de bloques de memoria
    MemoryBlock *lastBlock = NULL;    // Puntero para enlazar los bloques

    // Inicializar la semilla para la generación de números aleatorios
    srand(time(NULL));

    // Creación de 10 bloques de memoria simulados
    for (int i = 1; i <= 10; i++) {
        // Generar un tamaño aleatorio que sea múltiplo de 10 entre 10 y 500
        size_t size = (rand() % 50 + 1) * 10;  // Tamaño entre 10 y 500
        MemoryBlock *newBlock = createMemoryBlock(i, size);
        if (newBlock != NULL) {
            if (memoryList == NULL) {
                memoryList = newBlock;  // Primer bloque
            } else {
                lastBlock->next = newBlock;  // Enlazamos el bloque anterior con el nuevo
            }
            lastBlock = newBlock;  // Actualizamos el puntero al último bloque
        }
    }

    // Imprimir la lista de bloques de memoria
    printMemoryList(memoryList);

    // Liberar los bloques de memoria
    MemoryBlock *current = memoryList;
    while (current != NULL) {
        MemoryBlock *next = current->next;  // Guardamos el siguiente bloque
        freeMemoryBlock(current);  // Liberamos el bloque actual
        current = next;  // Avanzamos al siguiente bloque
    }

    return 0;
}