/*EQUIPO TACOS LINUXEROS*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define TAM_BUFFER 5   // Tamaño del búfer
#define NUM_ELEMENTOS 10   // Número total de elementos a producir/consumir

int buffer[TAM_BUFFER];  // Búfer compartido
int in = 0;               // Entrada en el búfer
int out = 0;              // Extracción del búfer

pthread_mutex_t mutex;    // Mutex para asegurar acceso exclusivo al búfer
pthread_cond_t vacio;     // Condición de búfer vacío
pthread_cond_t lleno;     // Condición de búfer lleno

void *productor(void *arg) {
    int elemento;
    for (int i = 0; i < NUM_ELEMENTOS; i++) {
        elemento = rand() % 100;  // Genera un número aleatorio entre 0 y 99
        
        pthread_mutex_lock(&mutex);
        
        // Espera hasta que haya espacio en el búfer
        while (((in + 1) % TAM_BUFFER) == out) {
            pthread_cond_wait(&vacio, &mutex);
        }
        
        // Inserta el elemento en el búfer
        buffer[in] = elemento;
        printf("Producido: %d\n", elemento);
        in = (in + 1) % TAM_BUFFER;
        
        // Notifica a los consumidores que el búfer no está vacío
        pthread_cond_signal(&lleno);
        
        pthread_mutex_unlock(&mutex);
        
        usleep(rand() % 100000);  // Pequeño retraso aleatorio
    }
    pthread_exit(NULL);
}

void *consumidor(void *arg) {
    int elemento;
    for (int i = 0; i < NUM_ELEMENTOS; i++) {
        pthread_mutex_lock(&mutex);
        
        // Espera hasta que haya elementos en el búfer para consumir
        while (in == out) {
            pthread_cond_wait(&lleno, &mutex);
        }
        
        // Extrae un elemento del búfer
        elemento = buffer[out];
        printf("Consumido: %d\n", elemento);
        out = (out + 1) % TAM_BUFFER;
        
        // Notifica a los productores que el búfer no está lleno
        pthread_cond_signal(&vacio);
        
        pthread_mutex_unlock(&mutex);
        
        usleep(rand() % 100000);  // Pequeño retraso aleatorio
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t hilo_productor, hilo_consumidor;
    
    // Inicializa los mutex y las variables de condición
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&vacio, NULL);
    pthread_cond_init(&lleno, NULL);
    
    // Crea los hilos del productor y el consumidor
    pthread_create(&hilo_productor, NULL, productor, NULL);
    pthread_create(&hilo_consumidor, NULL, consumidor, NULL);
    
    // Espera a que ambos hilos terminen
    pthread_join(hilo_productor, NULL);
    pthread_join(hilo_consumidor, NULL);
    
    // Destruye los mutex y las variables de condición
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&vacio);
    pthread_cond_destroy(&lleno);
    
    return 0;
}