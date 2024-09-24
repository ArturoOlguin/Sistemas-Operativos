/*EQUIPO TACOS LINUXEROS*/


/*1. En una nave industrial existe una máquina de inyectar que deja cada pieza producida en una cinta transportadora de tamaño limitado.
Existe un robot que recoge las piezas de la cinta (una cada vez) y las deja en las cajas de embalaje.
Finalmente, tenemos un operario que, de vez en cuando, recoge 3 piezas para realizar el control de calidad, si no hay tres piezas en la cinta lo intentará más tarde.
Resuelve el escenario anterior mediante semáforos*/

/*El codigo funciona de la siguiente manera
sem_t lleno se usa para saber si hay una nueva pieza
sem_t vacio se usa para saber si hay capacidad

En la inyeccion lleno se usa para saber que hay una nueva pienza y vacio para para la capacidad
En el robot lleno se usa para saber si hay una pieza para tomar y vacio para indicar que ya la recogio
El operario unicamente si hay 3 piezas en la banda analiza 3, si no espera hasta que haya 3*/

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

#define CAPACIDAD_MAX_CINTA 10

/*Declaracion de los semaforos*/
sem_t lleno;
sem_t vacio;
sem_t mutex;

/*Variables iniciales*/
int cinta [CAPACIDAD_MAX_CINTA];
int piezas_cinta = 0; //Inicia sin piezas

/*Funciones para cada participante*/

/*Funcion de la maquina de inyeccion*/
void* inyeccion (void* arg){
    while(1){

        sem_wait (&vacio);
        sem_wait(&mutex);
   
        cinta[piezas_cinta++]=1; //Agrega una pieza a la cinta
        printf("Maquina produjo una pieza\n");
        printf("\t\t\t\t Piezas en la cinta %d\n", piezas_cinta);
        
        sem_post(&mutex);
        sem_post(&lleno);

        sleep(1);
    }
}

/*Funcion del robot*/
void* robot (void* arg){
    while(1){
        sem_wait (&vacio);
        sem_wait(&mutex);

        piezas_cinta--; // Recoge una pieza de la cinta

        printf("Robot tomo una pieza\n"); 
        printf("\t\t\t\t Piezas en la cinta %d\n", piezas_cinta);
        sem_post(&mutex);
        sem_post(&lleno);

        sleep(3);
    }
}

/*Funcion del operario*/
void* operario (void* arg){
    while(1){

        sem_wait (&mutex);

        if (piezas_cinta >= 3){
            piezas_cinta -=3;

            printf ("Operario toma 3 piezas\n");
            printf("\t\t\t\t Piezas en la cinta %d\n", piezas_cinta);

            sem_post(&mutex);
            sem_post(&vacio);
            sem_post(&vacio);
            sem_post(&vacio);
        }
        else{
            sem_post(&mutex);
        }
        
        sleep(1);
        
    }
}

int main(int argc, char const *argv[])
{
    /*Declaracion de hilos*/
    pthread_t hilo1, hilo2, hilo3;

    /*Inicializacion de los semaforos*/
    sem_init(&vacio, 0, CAPACIDAD_MAX_CINTA);  /*La cinta inicia vacia*/
    sem_init(&lleno, 0, 0);  /*Sin piezas al inicio*/
    sem_init(&mutex, 0, 1);  /*Saber si esta disponible la cinta*/

    /*Creacion de hilos*/
    pthread_create(&hilo1, NULL, inyeccion, NULL);
    pthread_create(&hilo2, NULL, robot, NULL);
    pthread_create(&hilo3, NULL, operario, NULL);

   /*Finalizacion de hilos*/
    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);
    pthread_join(hilo3, NULL);

    /*Destruccion de semaforos*/
    sem_destroy(&vacio);
    sem_destroy(&lleno);
    sem_destroy(&mutex);

    return 0;
}
