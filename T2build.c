#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<errno.h>
#define NOT_READY -1
#define FILLED 0 
#define TAKEN 1 
#define GO 2 
#define STOP 3 

/*
Program that creates a shared memory that is used to simulate the producer-consumer problem using two other processes.

*/

//struct used by shared memory
struct Memory {
int status; 
int gostop; 
int i[5];
int count;
int Psleep;
int Csleep;
};



int main(){
key_t key;
int ID;
struct Memory *shm;
key = ftok(".",'X'); //retrieve key
ID = shmget(key,sizeof(struct Memory *),0666 | IPC_CREAT); //retrieve ID
shm = (struct Memory *) shmat(ID,NULL,0);

shm->status = NOT_READY;
shm->gostop = GO;

    exit(0);
}
