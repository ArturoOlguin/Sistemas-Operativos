/*EQUIPO TACOS LINUXEROS*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int count = 0;
pthread_mutex_t mutex;
pthread_cond_t cond_productor, cond_consumidor;

void* productor(void* args) {
    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&mutex);

        while (count == BUFFER_SIZE) {
            pthread_cond_wait(&cond_productor, &mutex);
        }

        buffer[count++] = rand() % 100;
        printf("Productor produjo: %d\n", buffer[count-1]);

        pthread_cond_signal(&cond_consumidor);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

void* consumidor(void* args) {
    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&mutex);

        while (count == 0) {
            pthread_cond_wait(&cond_consumidor, &mutex);
        }

        int item = buffer[--count];
        printf("Consumidor consumió: %d\n", item);

        pthread_cond_signal(&cond_productor);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t prod, cons;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond_productor, NULL);
    pthread_cond_init(&cond_consumidor, NULL);

    pthread_create(&prod, NULL, productor, NULL);
    pthread_create(&cons, NULL, consumidor, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_productor);
    pthread_cond_destroy(&cond_consumidor);

    return 0;
}
