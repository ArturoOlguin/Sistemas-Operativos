#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define ARRAY_SIZE 100
#define ITERATIONS 200
#define NUM_THREADS 2

int array[ARRAY_SIZE];           // Array original
int aux_array[ARRAY_SIZE];       // Array auxiliar
pthread_barrier_t barrier;       // Barrera para sincronizar threads

// Función que calcula la media para una sección del array
void* process_section(void* arg) {
    int thread_id = (int)arg;
    int start = (thread_id == 0) ? 0 : ARRAY_SIZE / 2;
    int end = (thread_id == 0) ? ARRAY_SIZE / 2 : ARRAY_SIZE;

    for (int iter = 0; iter < ITERATIONS; iter++) {
        // Calcular valores nuevos en la sección correspondiente
        for (int i = start; i < end; i++) {
            int left = (i == 0) ? array[ARRAY_SIZE - 1] : array[i - 1];
            int right = (i == ARRAY_SIZE - 1) ? array[0] : array[i + 1];
            aux_array[i] = (left + array[i] + right) / 3;
        }

        // Sincronizar threads antes de volcar los datos al array real
        pthread_barrier_wait(&barrier);

        // Volcar los datos del array auxiliar al array real
        for (int i = start; i < end; i++) {
            array[i] = aux_array[i];
        }

        // Sincronizar threads antes de pasar a la siguiente iteración
        pthread_barrier_wait(&barrier);
    }

    pthread_exit(NULL);
}

int main() {
    // Inicializar el array con valores aleatorios (ejemplo)
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = rand() % 100;
    }

    // Inicializar barrera
    pthread_barrier_init(&barrier, NULL, NUM_THREADS);

    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Crear threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, process_section, &thread_ids[i]);
    }

    // Esperar a que los threads terminen
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destruir la barrera
    pthread_barrier_destroy(&barrier);

    // Imprimir el array final
    printf("Array final:\n");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}