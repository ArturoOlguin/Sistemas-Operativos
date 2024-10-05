/* En un cuartel hay un comedor para 1000 soldados. El soldado cuando quiere comer entra en el 
recinto y coge una bandeja con comida en uno de los 5 mostradores que existen para tal efecto; la 
bandeja tiene un vaso de agua o un botellín de refresco, si escoge esto último necesita uno de los 
60 abridores. Si quiere postre se dirige a uno de los 5 mostradores que lo despachan; Cuando 
finaliza la comida sale del recinto. Realizar un programa concurrente de forma que utilizando 
semáforos coordine las tareas de los soldados.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_SOLDADOS 1000
#define NUM_MOSTRADORES_COMIDA 5
#define NUM_ABRIDORES 60
#define NUM_MOSTRADORES_POSTRE 5

// Semáforos para gestionar los mostradores y abridores
sem_t mostradores_comida;
sem_t abridores;
sem_t mostradores_postre;

// Función que simula la acción de un soldado
void* soldado(void* arg) {
    int id = *((int*) arg);

    // El soldado va a uno de los mostradores de comida
    sem_wait(&mostradores_comida);
    printf("Soldado %d está tomando comida en un mostrador.\n", id);
    sleep(1); // Simula el tiempo para tomar comida
    sem_post(&mostradores_comida); // Libera el mostrador de comida

    // El soldado decide si toma refresco o agua (50% de probabilidad)
    if (rand() % 2 == 0) {
        sem_wait(&abridores);
        printf("Soldado %d está usando un abridor para el refresco.\n", id);
        sleep(1); // Simula el tiempo para abrir el refresco
        sem_post(&abridores); // Libera el abridor
    } else {
        printf("Soldado %d toma agua.\n", id);
    }

    // El soldado va a uno de los mostradores de postre
    sem_wait(&mostradores_postre);
    printf("Soldado %d está tomando postre en un mostrador.\n", id);
    sleep(1); // Simula el tiempo para tomar el postre
    sem_post(&mostradores_postre); // Libera el mostrador de postre

    printf("Soldado %d ha terminado su comida.\n", id);
    pthread_exit(NULL);
}

int main() {
    pthread_t soldados[NUM_SOLDADOS];
    int ids_soldados[NUM_SOLDADOS];

    // Inicializar los semáforos
    sem_init(&mostradores_comida, 0, NUM_MOSTRADORES_COMIDA);
    sem_init(&abridores, 0, NUM_ABRIDORES);
    sem_init(&mostradores_postre, 0, NUM_MOSTRADORES_POSTRE);

    // Crear los hilos de los soldados
    for (int i = 0; i < NUM_SOLDADOS; i++) {
        ids_soldados[i] = i + 1;
        pthread_create(&soldados[i], NULL, soldado, &ids_soldados[i]);
    }

    // Esperar a que todos los hilos terminen
    for (int i = 0; i < NUM_SOLDADOS; i++) {
        pthread_join(soldados[i], NULL);
    }

    // Destruir los semáforos
    sem_destroy(&mostradores_comida);
    sem_destroy(&abridores);
    sem_destroy(&mostradores_postre);

    return 0;
}
