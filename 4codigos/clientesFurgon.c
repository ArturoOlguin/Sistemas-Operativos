#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_CLIENTES 100
#define CLIENTES_POR_FURGON 20

//Definir semáforos y variables de control
sem_t clientes_en_sucursal;
sem_t operacion_en_curso;
pthread_mutex_t mutex;

int clientes = 0;

__id_t llegada_cliente(void* arg){ //se cambio de id* a __id_t 
    while(1){
        usleep(rand() % 3000000);
        pthread_mutex_lock(&mutex);
        clientes ++;
        printf("Cliente entró a la sucursal. CLientes en la sucursal: %d \n", clientes);
        if(clientes  && CLIENTES_POR_FURGON == 0 && clientes <= MAX_CLIENTES){ //Se agregaron los dos && que faltaban 
            printf("\n ¡El furgón blindado está llegando! La sucursal se está vaciando... \n \n");
            sem_wait(&operacion_en_curso);
            for(int i = clientes; i > 0; i--){
                printf("CLiente salió de la sucursal.CLientes en la sucursal: %d", 1);
                usleep(500000);
            }
            printf(" EL furgón blindado puede realizar la operación ahora. ");
            sem_post(&operacion_en_curso);
        }
        pthread_mutex_unlock(&mutex);
        sem_post(&clientes_en_sucursal);
    }
}
__id_t operacion_furgon(void* arg){ //se cambio de id* a __id_t 
    while(1)
    sem_wait(&clientes_en_sucursal);
    if(clientes % CLIENTES_POR_FURGON == 0 && clientes <= MAX_CLIENTES){
        sem_wait(&operacion_en_curso);
        printf("Furgón blindado realizando la operación de carga/descarga de número... ");
        usleep(rand() % 2000000);
        sem_post(&operacion_en_curso);
        printf("Furgón blindado completó la operación. ");
    }
}

int main(){
    pthread_t hilo_clientes, hilo_furgon;
    sem_init(&clientes_en_sucursal,0,0);
    sem_init(&operacion_en_curso,0,1);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&hilo_clientes, NULL, llegada_cliente, NULL);
    pthread_create(&hilo_furgon, NULL, operacion_furgon, NULL);
    pthread_join(hilo_clientes, NULL);
    pthread_join(hilo_furgon, NULL);

    sem_destroy(&clientes_en_sucursal);
    sem_destroy(&operacion_en_curso);
    pthread_mutex_destroy(&mutex);

    return 0;
}