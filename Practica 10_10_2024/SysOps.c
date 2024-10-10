/*Ejemplo 2

Explicación del Código:
Estructura Vehiculo:

Representa un vehículo con un id único y una placa que almacena la matrícula del vehículo.
Parqueo Principal y Depósito:

parqueo[]: Representa los espacios del parqueo principal (RAM) donde se estacionan los vehículos.
deposito[]: Simula el depósito donde se mueven los vehículos más antiguos cuando el parqueo está lleno.
Función moverAlDeposito:

Si el parqueo está lleno, el vehículo más antiguo es movido al depósito. Esta función se asegura de que el depósito tenga espacio y, si lo tiene, mueve el vehículo allí.
Función agregarVehiculo:

Esta función agrega vehículos al parqueo principal. Si el parqueo está lleno, mueve el vehículo más antiguo al depósito para hacer espacio para el nuevo vehículo.
Funciones imprimirParqueo y imprimirDeposito:

Estas funciones imprimen los vehículos actualmente en el parqueo y el depósito.
Flujo del Programa:
Se agregan vehículos uno por uno al parqueo.
Cuando el parqueo se llena (con 6 vehículos), el vehículo más antiguo es movido al depósito para hacer espacio.
Finalmente, se imprime el estado del parqueo y del depósito.
Aplicación Real:
Este sistema simula un parqueo en un centro comercial o edificio, donde los vehículos que llevan más tiempo pueden ser movidos a un estacionamiento adicional o remoto para dejar espacio para los nuevos vehículos que llegan. Esta lógica es común en muchas ciudades o establecimientos con espacio limitado.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ESPACIOS 6  // Máximo número de vehículos en el parqueo principal
#define MAX_DEPOSITO 4  // Máximo número de vehículos en el depósito
#define UMBRAL_MOVER 5  // Mover vehículos al depósito cuando se alcanza este número en el parqueo

// Estructura para representar un vehículo
typedef struct {
    int id;
    char placa[10];
} Vehiculo;

// Arreglo para simular el parqueo principal
Vehiculo parqueo[MAX_ESPACIOS];

// Arreglo para simular el depósito
Vehiculo deposito[MAX_DEPOSITO];
int numVehiculosDeposito = 0;

// Función para imprimir los vehículos en el parqueo
void imprimirParqueo() {
    printf("Vehículos en el parqueo principal:\n");
    for (int i = 0; i < MAX_ESPACIOS; ++i) {
        if (parqueo[i].id != -1) {
            printf("ID: %d, Placa: %s\n", parqueo[i].id, parqueo[i].placa);
        }
    }
}

// Función para imprimir los vehículos en el depósito
void imprimirDeposito() {
    printf("Vehículos en el depósito:\n");
    for (int i = 0; i < numVehiculosDeposito; ++i) {
        printf("ID: %d, Placa: %s\n", deposito[i].id, deposito[i].placa);
    }
}

// Función para mover vehículos al depósito
void moverAlDeposito(Vehiculo vehiculo) {
    if (numVehiculosDeposito < MAX_DEPOSITO) {
        deposito[numVehiculosDeposito] = vehiculo;
        numVehiculosDeposito++;
        printf("Vehículo ID: %d, Placa: %s fue movido al depósito.\n", vehiculo.id, vehiculo.placa);
    } else {
        printf("El depósito está lleno, no se puede mover el vehículo.\n");
    }
}

// Función para agregar un vehículo al parqueo
void agregarVehiculo(Vehiculo vehiculo) {
    int agregado = 0;
    for (int i = 0; i < MAX_ESPACIOS; ++i) {
        if (parqueo[i].id == -1) {  // Espacio libre encontrado en el parqueo
            parqueo[i] = vehiculo;  // Agregamos el vehículo al parqueo
            agregado = 1;
            break;
        }
    }
    if (!agregado) {
        // Si no hay espacio en el parqueo, movemos el vehículo más antiguo al depósito
        moverAlDeposito(parqueo[0]);  // Movemos el primer vehículo al depósito
        // Desplazamos los vehículos en el parqueo
        for (int i = 0; i < MAX_ESPACIOS - 1; ++i) {
            parqueo[i] = parqueo[i + 1];
        }
        parqueo[MAX_ESPACIOS - 1] = vehiculo;  // Agregamos el nuevo vehículo en el último lugar
    }
}

int main() {
    // Inicializamos el parqueo y el depósito con espacios vacíos
    for (int i = 0; i < MAX_ESPACIOS; ++i) {
        parqueo[i].id = -1;  // Marcamos los espacios del parqueo como vacíos
    }

    // Inicializamos el depósito vacío
    for (int i = 0; i < MAX_DEPOSITO; ++i) {
        deposito[i].id = -1;  // Marcamos los espacios del depósito como vacíos
    }

    // Ejemplo de uso: Agregamos algunos vehículos al parqueo
    agregarVehiculo((Vehiculo){1, "ABC123"});
    agregarVehiculo((Vehiculo){2, "DEF456"});
    agregarVehiculo((Vehiculo){3, "GHI789"});
    agregarVehiculo((Vehiculo){4, "JKL012"});
    agregarVehiculo((Vehiculo){5, "MNO345"});
    agregarVehiculo((Vehiculo){6, "PQR678"});  // En este punto, el parqueo está lleno

    // Intentamos agregar un nuevo vehículo, lo que provocará que el más antiguo se mueva al depósito
    agregarVehiculo((Vehiculo){7, "STU901"});

    // Mostramos el contenido final del parqueo y del depósito
    printf("\nEstado final del parqueo:\n");
    imprimirParqueo();

    printf("\nEstado final del depósito:\n");
    imprimirDeposito();

    return 0;
}
