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
Program that simulates the consumer side of the producer-consumer problem. 
Recieves array from producer and removes each entry while printing each entry it removes out.

*/

//struct for memory
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
key = ftok(".",'X'); //retrieves key
ID = shmget(key,sizeof(struct Memory *),0666); //ID is retrieved
shm = (struct Memory *) shmat(ID,NULL,0);
shm->count = 0;
int item;
while(1){
    if(shm->count < 0){
        printf("Queue is empty. Sending back to Producer.\n");
        shm->Csleep = 1; //consumer is put to sleep
        shm->Psleep = 0; //producer is woken up
    }
   while(shm->Csleep == 1){ //consumer is woken up
    sleep(2);
   }
   //item records shm entry
   item = shm->i[shm->count];
   printf("%d has been removed. \n",item);
   shm->i[shm->count] = 0;
   shm->count = shm->count - 1;
   item = 0;
}
    shmdt((void *) shm); //shm is detatched
    exit(0);
}
