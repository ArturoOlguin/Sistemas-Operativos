#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> // Para usar tipos de datos específicos como uint8_t

#define MEMORY_SIZE 1024                      // Tamaño total de la memoria en bytes
#define BLOCK_SIZE 64                         // Tamaño de cada bloque de memoria en bytes
#define NUM_BLOCKS (MEMORY_SIZE / BLOCK_SIZE) // Número de bloques de memoria

// Estructura para un bloque de memoria con mapa de bits
typedef struct MemoryBlock
{
    uint8_t bitmap[BLOCK_SIZE / 8]; // Mapa de bits: 1 bit por byte (8 bits por byte)
    int id;                         // Identificador del bloque de memoria
} MemoryBlock;

// Función para inicializar un bloque de memoria con mapa de bits
MemoryBlock *createMemoryBlock(int id)
{
    MemoryBlock *block = (MemoryBlock *)malloc(sizeof(MemoryBlock));
    if (block != NULL)
    {
        block->id = id;
        // Inicializar el mapa de bits: todos los bits a 0 (libres)
        for (int i = 0; i < BLOCK_SIZE / 8; ++i)
        {
            block->bitmap[i] = 0;
        }
    }
    return block;
}

// Función para asignar memoria dentro de un bloque usando un mapa de bits
int allocateMemory(MemoryBlock *block, size_t size)
{
    int start = -1;                   // Inicialmente no se encuentra espacio suficiente
    int bits_needed = (size + 7) / 8; // Número de bytes necesarios para el tamaño solicitado

    // Buscar un espacio libre suficientemente grande en el mapa de bits
    for (int i = 0; i <= BLOCK_SIZE / 8 - bits_needed; ++i)
    {
        int j;
        for (j = 0; j < bits_needed; ++j)
        {
            if (block->bitmap[i + j] != 0)
            {
                break; // Bloque ocupado encontrado, continuar buscando
            }
        }
        if (j == bits_needed)
        {
            // Espacio suficiente encontrado, marcar como ocupado
            start = i * 8;
            for (int k = 0; k < bits_needed; ++k)
            {
                block->bitmap[i + k] = 0xFF; // Marcar todos los bytes como ocupados (0xFF)
            }
            break;
        }
    }

    return start;
}

// Función para liberar memoria dentro de un bloque usando un mapa de bits
void freeMemory(MemoryBlock *block, int start, size_t size)
{
    int bits_to_free = (size + 7) / 8; // Número de bytes a liberar

    // Liberar los bits correspondientes en el mapa de bits
    for (int i = start / 8; i < (start / 8) + bits_to_free; ++i)
    {
        block->bitmap[i] = 0; // Marcar como libre (todos los bits a 0)
    }
}

// Función para imprimir el mapa de bits de un bloque de memoria
void printMemoryBlock(MemoryBlock *block)
{
    printf("Bloque de memoria ID: %d\n", block->id);
    printf("Mapa de bits:\n");
    for (int i = 0; i < BLOCK_SIZE / 8; ++i)
    {
        printf("%02X ", block->bitmap[i]);
    }
    printf("\n");
}

int main()
{
    MemoryBlock *memoryBlock = createMemoryBlock(1);

    // Ejemplo de asignación y liberación de memoria
    int start1 = allocateMemory(memoryBlock, 128); // Asignar 128 bytes
    int start2 = allocateMemory(memoryBlock, 64);  // Asignar 64 bytes

    printf("Después de la asignación:\n");
    printMemoryBlock(memoryBlock);

    freeMemory(memoryBlock, start1, 128); // Liberar los 128 bytes asignados anteriormente

    printf("Después de la liberación:\n");
    printMemoryBlock(memoryBlock);

    free(memoryBlock); // Liberar la memoria del bloque de memoria

    return 0;
}

/*
Este código proporciona una implementación básica de un sistema de gestión de memoria utilizando mapas de bits en lenguaje C. es importante notar que este es un ejemplo simplificado.
*/