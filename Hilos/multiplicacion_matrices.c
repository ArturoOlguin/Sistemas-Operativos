/*EQUIPO TACOS LINUXEROS*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define N 2 // Tamaño de la matriz NxN

// Definimos las matrices globales
int A[N][N] = {{1, 2}, {3, 4}};
int B[N][N] = {{5, 6}, {7, 8}};
int C[N][N]; // Matriz resultado

// Función que calculará una fila de la matriz resultante
void* multiplyRow(void* arg) {
    int row = *((int*)arg); // Obtener el índice de la fila
    for (int j = 0; j < N; j++) {
        C[row][j] = 0; // Inicializar la celda de la matriz resultante
        for (int k = 0; k < N; k++) {
            C[row][j] += A[row][k] * B[k][j];
        }
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[N];
    int thread_args[N];

    // Crear un hilo por cada fila de la matriz
    for (int i = 0; i < N; i++) {
        thread_args[i] = i; // Pasar el índice de la fila como argumento
        pthread_create(&threads[i], NULL, multiplyRow, (void*)&thread_args[i]);
    }

    // Esperar a que todos los hilos terminen
    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    // Imprimir la matriz resultante
    printf("Resultado de la multiplicación de matrices:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}
