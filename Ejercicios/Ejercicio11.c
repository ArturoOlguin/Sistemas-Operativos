#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define CAPACIDAD_CINTA 10 // Capacidad de la cinta transportadora

// Semáforos
sem_t vacio;    // Indica si hay espacio en la cinta
sem_t lleno;    // Indica si hay piezas en la cinta
sem_t mutex;    // Exclusión mutua para acceso a la cinta

int cinta[CAPACIDAD_CINTA];  // Cinta transportadora
int piezas_cinta = 0;        // Número de piezas en la cinta

// Función de la máquina de inyección
void* maquina_inyectar(void* arg) {
    while (1) {
        sem_wait(&vacio);  // Espera hasta que haya espacio en la cinta
        sem_wait(&mutex);  // Bloquea acceso a la cinta

        // Agregar pieza a la cinta
        cinta[piezas_cinta++] = 1;  // 1 representa una pieza
        printf("Máquina produjo una pieza. Piezas en cinta: %d\n", piezas_cinta);

        sem_post(&mutex);  // Libera la cinta
        sem_post(&lleno);  // Indica que hay una nueva pieza en la cinta
        sleep(1);  // Simulación del tiempo de producción
    }
}

// Función del robot
void* robot(void* arg) {
    while (1) {
        sem_wait(&lleno);  // Espera hasta que haya piezas en la cinta
        sem_wait(&mutex);  // Bloquea acceso a la cinta

        // Robot recoge una pieza
        piezas_cinta--;
        printf("Robot recogió una pieza. Piezas restantes en cinta: %d\n", piezas_cinta);

        sem_post(&mutex);  // Libera la cinta
        sem_post(&vacio);  // Indica que hay un espacio disponible en la cinta
        sleep(2);  // Simulación del tiempo de embalaje
    }
}

// Función del operario
void* operario(void* arg) {
    while (1) {
        sem_wait(&mutex);  // Bloquea acceso a la cinta

        // El operario recoge 3 piezas solo si hay suficientes
        if (piezas_cinta >= 3) {
            piezas_cinta -= 3;
            printf("Operario realizó control de calidad con 3 piezas. Piezas restantes en cinta: %d\n", piezas_cinta);

            sem_post(&mutex);  // Libera la cinta
            sem_post(&vacio);  // Libera 3 espacios en la cinta
            sem_post(&vacio);
            sem_post(&vacio);
        } else {
            sem_post(&mutex);  // Libera la cinta si no hay suficientes piezas
        }
        sleep(3);  // Simulación del tiempo de control de calidad
    }
}

int main() {
    pthread_t t1, t2, t3;

    // Inicialización de semáforos
    sem_init(&vacio, 0, CAPACIDAD_CINTA);  // Al principio, la cinta está vacía
    sem_init(&lleno, 0, 0);  // No hay piezas al principio
    sem_init(&mutex, 0, 1);  // Control de acceso a la cinta

    // Creación de hilos
    pthread_create(&t1, NULL, maquina_inyectar, NULL);
    pthread_create(&t2, NULL, robot, NULL);
    pthread_create(&t3, NULL, operario, NULL);

    // Esperar a que terminen los hilos (en un programa real, usaríamos un mecanismo de terminación)
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    // Destruir los semáforos
    sem_destroy(&vacio);
    sem_destroy(&lleno);
    sem_destroy(&mutex);

    return 0;
}
