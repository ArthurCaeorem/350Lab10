#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>
#include <sys/sem.h>
#include<errno.h>
#define MUTEX 0
#define FULL 1
#define EMPTY 2
#define NOT_READY -1
#define FILLED 0 
#define TAKEN 1 
#define GO 2 
#define STOP 3 
#define SIZE 5

/*
program that simulates the producer-consumer problem like task 2, but while utilizing semaphores along with shared memory
*/

//memory struct
struct Memory {
int status; 
int gostop; 
int i[5];
int count;
int Psleep;
int Csleep;
};

//union for arg
union semun {
    int val;
    struct sumid_ds *buf;
    unsigned short *array;
};

int main(){
    union semun arg;
key_t key;
int ID,semID;
struct Memory *shm;
key = ftok(".",'G'); //creates key
ID = shmget(key,sizeof(struct Memory *),0666 | IPC_CREAT); //creates ID
shm = (struct Memory *) shmat(ID,NULL,0);
semID = semget(key,3,0666 | IPC_CREAT); //creates 3 semaphores
arg.val = 1; //sets value for MUTEX semaphore
semctl(semID,MUTEX,SETVAL,arg);
arg.val = 0; //sets value for FULL semaphore
semctl(semID,FULL,SETVAL,arg);
arg.val = 5; //sets value for EMPTY semaphore
semctl(semID,EMPTY,SETVAL,arg);
shm->count = 0;
shm->status = NOT_READY;
shm->gostop = GO;
//semctl(semID,0,IPC_RMID,arg);
//shmctl(ID, IPC_RMID, NULL);
    exit(0);
}
