#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

void imprimeDePipe(int leePipe); //Funcionalidad para el hijo
void enviaAPipe(int escribePipe); //FUncionalidad para el padres

int main(){
    pid_t procHijo;
    int pipeFileDescriptors[2]; //Descriptores de ambos extremos
    if(pipe(pipeFileDescriptors) == -1){ //Genera pipe
        printf("Error al crear pipe \n");
        exit(1);
    }
    procHijo=fork(); //Genera proceso hijo
    if(procHijo < 0){
        int interrnum=errno;//preservamos código de error
        printf("Errror %d al generar proceso hijo con fork \n", errno);
        exit(1);
    }

    if(procHijo==0){
        //Es el hijo, cierra pipe de envío y procede 
        close(pipeFileDescriptors[1]);
        imprimeDePipe(pipeFileDescriptors[0]);
    }

    if(procHijo>0){
        //Es el padre, cierra pide de recepción y procede
        close(pipeFileDescriptors[0]);
        enviaAPipe(pipeFileDescriptors[1]);
    }

    return 0;
}

/**
 * Funcionalidad para el hijo, lee el pipe de cadena enviada, imprime
 * el contenido de esta a STDOUT, cierra su extremo del pipe (lectura)
 * y termina su proceso
 */

void imprimeDePipe(int leePipe){
    char buf; //carácter de buffer
    printf("Proceso hijo, esperando cadena... \n");
    while (read(leePipe, &buf, 1) > 0)
        write(STDOUT_FILENO, &buf, 1);
    write(STDOUT_FILENO, "\n",1); //Fin de línea
    close(leePipe);
    printf("Proceso hijo, finalizando \n");
    exit(0);
}

void enviaAPipe(int escribeṔipe){
    char buf[10]; //buffer de hasta 256 carácteres
    printf("Proceso padre, ingresa una cadena de 10 carácteres y enter: \n");
    scanf("%c", &buf)
   printf("\n \n"); //separa la entrada de las futuras salidas
    write(escribePipe, &buf, strlen(buf));
    close (escribePipe); //Presenta EOF al proceso hijo
    wait(NULL); //Espera terminación de hijo
    printf("HIjo terminado, terminando proceso padre \n");
    exit(0);
    }
    