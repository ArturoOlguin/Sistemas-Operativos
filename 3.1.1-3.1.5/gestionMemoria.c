#include <stdio.h>
#include <stdlib.h>

// Definición de una estructura para un bloque de memoria
typedef struct MemoryBlock
{
    int id;                   // Identificador del bloque de memoria
    size_t size;              // Tamaño del bloque de memoria
    struct MemoryBlock *next; // Puntero al siguiente bloque en la lista
} MemoryBlock;

// Función para inicializar un bloque de memoria
MemoryBlock *createMemoryBlock(int id, size_t size)
{
    MemoryBlock *block = (MemoryBlock *)malloc(sizeof(MemoryBlock));
    if (block != NULL)
    {
        block->id = id;
        block->size = size;
        block->next = NULL;
    }
    return block;
}

// Función para liberar un bloque de memoria
void freeMemoryBlock(MemoryBlock *block)
{
    free(block);
}

// Función para imprimir la lista de bloques de memoria
void printMemoryList(MemoryBlock *head)
{
    MemoryBlock *current = head;
    printf("Lista de bloques de memoria:\n");
    while (current != NULL)
    {
        printf("ID: %d, Tamaño: %zu\n", current->id, current->size);
        current = current->next;
    }
}

int main()
{
    MemoryBlock *memoryList = NULL; // Lista enlazada de bloques de memoria

    // Creación de bloques de memoria simulados
    MemoryBlock *block1 = createMemoryBlock(1, 100);
    MemoryBlock *block2 = createMemoryBlock(2, 200);
    MemoryBlock *block3 = createMemoryBlock(3, 150);

    // Insertar los bloques en la lista de memoria
    block1->next = block2;
    block2->next = block3;
    memoryList = block1;

    // Imprimir la lista de bloques de memoria
    printMemoryList(memoryList);

    // Liberar los bloques de memoria
    freeMemoryBlock(block1);
    freeMemoryBlock(block2);
    freeMemoryBlock(block3);

    return 0;
}