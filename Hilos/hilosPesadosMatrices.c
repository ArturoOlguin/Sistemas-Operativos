/*EQUIPO TACOS LINUXEROS*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 3 

int A[N][N], B[N][N], C[N][N]; 
pthread_t threads[N][N]; 

typedef struct {
    int row;
    int col;
} ThreadArgs;

void* multiply_matrices(void* arg) {
    ThreadArgs* args = (ThreadArgs*) arg;
    int row = args->row;
    int col = args->col;
    free(arg); 

    C[row][col] = 0; 
    for (int i = 0; i < N; i++) {
        C[row][col] += A[row][i] * B[i][col]; 
    }
    pthread_exit(NULL);
}

int main() {
    printf("Matriz A:\n");
    for (int i = 0; i < N; i++) {
            A[i][j] = rand() % 10; 
            printf("%d ", A[i][j]);
        }
        printf("\n");

    printf("\nMatriz B:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            B[i][j] = rand() % 10; 
            printf("%d ", B[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            ThreadArgs* args = malloc(sizeof(ThreadArgs)); 
            args->row = i;
            args->col = j;
            pthread_create(&threads[i][j], NULL, multiply_matrices, args); 
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {

        }
    }

    printf("\nMatriz C (producto de A y B):\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

}
