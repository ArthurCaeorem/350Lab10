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

//memory struct
struct Memory {
int status; 
int gostop; 
int i[5];
int count;
int Psleep;
int Csleep;
};

/*
program that simulates the producer-consumer problem utilizing both shared memory and semaphores.
This process simulates the consumer
*/

//decrements semaphore value
void down(int semid, int index)
{
struct sembuf buf = {index, -1, 0};
semop(semid, &buf, 1);
}
//increments semaphore value
void up(int semid, int index)
{
struct sembuf buf = {index, 1, 0};
semop(semid, &buf, 1);
}

//union used for arg
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
key = ftok(".",'G'); //key is retrieved
ID = shmget(key,sizeof(struct Memory *),0666); //shared memory is retrieved
shm = (struct Memory *) shmat(ID,NULL,0); //shared memory is accessed
semID = semget(key,3,0666); //semaphores are retrieved

int item=0;
while(1){
    down(semID,FULL);
    down(semID,MUTEX); //mutex becomes blocked
    shm->count--; //decrement count
    item = shm->i[shm->count]; //records this shm->i location as item
    shm->i[shm->count] = 0;
    printf("%d has been consumed.\n",item);
    printf("consumer finished.\n");
    sleep(2);
    up(semID,MUTEX); //mutex is unblocked
         if(shm->count == 0){ //once count is exhausted, 5 runs of the producer are set.
            for(int i = 0; i < 5; i++){
         up(semID,EMPTY);
            }
        }
    }
    
    exit(0);
}
