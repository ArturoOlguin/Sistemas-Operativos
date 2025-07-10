#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define TAM_ARRE 100
#define ITERACIONES 200

int array[TAM_ARRE];
int array_aux[TAM_ARRE];
//pthread_barrier_t; /*Para asegurar que un hilo espere a otro*/

/*Inicializar el arreglo*/

void init_array(){
    for (int i = 0; i < TAM_ARRE; i++)
    {
        array[i]=i;
    }
    
}


int main(int argc, char const *argv[])
{
printf("Array final");
for (int i = 0; i < TAM_ARRE; i++) {
        printf("%d ", array[i]);
    }
}
