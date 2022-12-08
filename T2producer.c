#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<errno.h>
#include<stdlib.h>
#define NOT_READY -1
#define FILLED 0 
#define TAKEN 1 
#define GO 2 
#define STOP 3 

/*
Program that simulates the producer in the producer-consumer problem with a size 5 integer array. 
utilizes Psleep and Csleep to control when each process activates
*/

struct Memory {
int status; 
int gostop; 
int i[5];
int count;
int Psleep;
int Csleep;
};


int main(){
    srand(time(0));
key_t key;
int ID;
struct Memory *shm;
key = ftok(".",'X'); //retrieve key
ID = shmget(key,sizeof(struct Memory *),0666); //retrieve ID
shm = (struct Memory *) shmat(ID,NULL,0);
shm->count = 0;
int item;

while(1){
    item = rand() % 9 + 1; //item is created
    if(shm->count == 5){ //when array is full
        for(int i = 0; i < 5; i++){
        printf("%d has been added.\n",shm->i[i]);
        }
        printf("\nQueue is full, waiting for consumer.\n");
        shm->count--;
        shm->Psleep = 1; //puts producer asleep
        shm->Csleep = 0; //wakes up consumer
        }
   while(shm->Psleep == 1){ //producer is put to sleep
    sleep(2);
   }
   shm->i[shm->count] = item; 
   shm->count = shm->count+1;
}
    shmdt((void *) shm); //shm is detatched
    exit(0);
}
