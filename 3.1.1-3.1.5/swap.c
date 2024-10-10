#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_ITEMS 10
#define SWAP_THRESHOLD 8 // Simulamos swap cuando tenemos 8 elementos en RAM

// Estructura de datos para simular elementos almacenados en memoria RAM
typedef struct
{
    int id;
    char data[20];
} DataItem;

// Arreglo para simular la memoria RAM
DataItem ram[MAX_ITEMS];
// Función para imprimir los elementos en RAM
void printRAM()
{
    printf("Contenido en RAM:\n");
    for (int i = 0; i < MAX_ITEMS; ++i)
    {
        if (ram[i].id != -1)
        {
            printf("ID: %d, Data: %s\n", ram[i].id, ram[i].data);
        }
    }
}

// Función para simular el intercambio de memoria (swap)
void swapToDisk(DataItem item)
{
    printf("Intercambiando elemento ID: %d a disco duro.\n", item.id);
    // Aquí iría la lógica para escribir el elemento en disco duro
    // Simplemente lo imprimimos como ejemplo
    printf("Elemento ID: %d, Data: %s fue intercambiado a disco.\n", item.id, item.data);
}
// Función para simular la adición de un elemento a la RAM
void addToRAM(DataItem item)
{
    int added = 0;
    for (int i = 0; i < MAX_ITEMS; ++i)
    {
        if (ram[i].id == -1)
        {                  // Espacio libre encontrado en RAM
            ram[i] = item; // Agregamos el elemento a RAM
            added = 1;
            break;
        }
    }
    if (!added)
    {
        // Si no hay espacio en RAM, simulamos el swap de un elemento
        swapToDisk(ram[0]); // Intercambiamos el primer elemento por el nuevo
        ram[0] = item;      // Agregamos el nuevo elemento a RAM
    }
}
int main()
{
    // Inicializamos la RAM con elementos vacíos
    for (int i = 0; i < MAX_ITEMS; ++i)
    {
        ram[i].id = -1; // Marcamos como vacío
    }

    // Ejemplo de uso: Agregamos algunos elementos a la RAM
    addToRAM((DataItem){1, "Datos de prueba 1"});
    addToRAM((DataItem){2, "Datos de prueba 2"});
    addToRAM((DataItem){3, "Datos de prueba 3"});
    addToRAM((DataItem){4, "Datos de prueba 4"});
    addToRAM((DataItem){5, "Datos de prueba 5"});
    addToRAM((DataItem){6, "Datos de prueba 6"});
    addToRAM((DataItem){7, "Datos de prueba 7"});
    addToRAM((DataItem){8, "Datos de prueba 8"});
    addToRAM((DataItem){9, "Datos de prueba 9"});
    addToRAM((DataItem){10, "Datos de prueba 10"});

    // Mostramos el contenido final en RAM
    printRAM();

    return 0;
}
/*
Este código simula la gestión de una memoria RAM (Memoria de Acceso Aleatorio) limitada, permitiendo añadir elementos y simulando un intercambio de elementos al disco cuando la RAM (Memoria de Acceso Aleatorio) alcanza su capacidad máxima. Es útil para entender conceptos básicos de gestión de memoria y cómo se pueden aplicar en sistemas más complejos.

*/