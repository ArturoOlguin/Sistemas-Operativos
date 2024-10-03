#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>  
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>  

#define SHMKEY 75
#define true 1

int region_critica(int pid);
int region_no_critica(int pid);

int esperando_turno(int pid);

int main(){
    int shmid,pid;
    char *addr,*turno;
    pid=getpid();
    shmid = shmget(SHMKEY,10,0777|IPC_CREAT);
    addr= shmat(schmidt,0,0);
    turno = (char *) addr;
    
    printf("\n [|] Variables declaradas");
    sleep(5);
    (*turno)='0';
    printf("\n [|] Iniciando preocesos de turnos con turno inicial: %c",(*turno));
    
    while(true){
        while((*turno) != '0'){
            esperando_turno(pid);
        }
        
        region_critica(pid);
        sleep(1);
        (*turno)='1';
        region_no_critica(pid);
    }
    
    shmdt(addr);
    
    shmctl(shmid,IPC_RMID,0);
    return 0;
}

int esperando_turno(int pid){
    printf("\n[|] Proceso %d y esperando turno: ",pid); //falto el % para declarar la Variable
    sleep(2);
    return 0;
}

int region_critica(int pid){
    printf("\n\n [O] Cambiando Variables");
    for(int i=0 ; i<5 ; i++){
        printf("\n [O] turno: %d ", i+1);
        sleep(1);
    }
    return 0;
}

int region_no_critica(int pid){
    printf("\n[O] Proceso %d y turno tomado :)))\n",pid);
    return 0;
}