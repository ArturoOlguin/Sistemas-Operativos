/*Simula una memoria ram y elimina el archivo que lleva mas tiempo sin usarse*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CACHE_SIZE 5

typedef struct {
    int id;
    char data[20];
} CacheItem;

CacheItem cache[CACHE_SIZE];
int usage[CACHE_SIZE]; // Array para controlar el uso reciente de los elementos

void initializeCache() {
    for (int i = 0; i < CACHE_SIZE; i++) {
        cache[i].id = -1; // -1 indica que el espacio está vacío
        usage[i] = 0; // Inicializamos el uso en 0
    }
}

void printCache() {
    printf("Contenido de la cache:\n");
    for (int i = 0; i < CACHE_SIZE; i++) {
        if (cache[i].id != -1) {
            printf("ID: %d, Data: %s, Usage: %d\n", cache[i].id, cache[i].data, usage[i]);
        }
    }
}

int findLRU() {
    int minUsage = usage[0], lruIndex = 0;
    for (int i = 1; i < CACHE_SIZE; i++) {
        if (usage[i] < minUsage) {
            minUsage = usage[i];
            lruIndex = i;
        }
    }
    return lruIndex; // Devolvemos el índice del elemento menos usado
}

void accessCache(CacheItem item) {
    int found = 0;
    for (int i = 0; i < CACHE_SIZE; i++) {
        if (cache[i].id == item.id) {
            found = 1;
            usage[i]++; // Incrementamos el uso si encontramos el elemento
            break;
        }
    }

    if (!found) {
        int lruIndex = findLRU(); // Buscamos el menos usado
        printf("Reemplazando elemento ID: %d con ID: %d\n", cache[lruIndex].id, item.id);
        cache[lruIndex] = item; // Reemplazamos el LRU con el nuevo
        usage[lruIndex] = 1; // Reiniciamos el uso
    }
}

int main() {
    initializeCache();
    
    // Simulamos accesos a la cache
    accessCache((CacheItem){1, "Cache data 1"});
    accessCache((CacheItem){2, "Cache data 2"});
    accessCache((CacheItem){3, "Cache data 3"});
    accessCache((CacheItem){4, "Cache data 4"});
    accessCache((CacheItem){5, "Cache data 5"});
    printCache();
    
    // Simulamos más accesos que reemplazarán los menos usados
    accessCache((CacheItem){6, "Cache data 6"}); // Reemplazará al LRU
    accessCache((CacheItem){3, "Cache data 3"}); // Acceso existente, no reemplaza

    printCache();
    return 0;
}