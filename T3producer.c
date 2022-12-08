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
program that simulates the producer-consumer problem utilizing shared memory and semaphores.
this process simulates the producer.
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

//union for the semaphore
union semun {
    int val;
    struct sumid_ds *buf;
    unsigned short *array;
};

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



int main(){
    srand(time(0));
union semun arg;
key_t key;
int ID,semID;
struct Memory *shm;
key = ftok(".",'G'); //retrieves key
ID = shmget(key,sizeof(struct Memory *),0666); //creates shared memory
shm = (struct Memory *) shmat(ID,NULL,0);
semID = semget(key,3,0666); //creates 3 semaphores
int item;
while(1){
        down(semID,EMPTY);
        down(semID,MUTEX); //mutex is blocked
        item = rand()%9 + 1;
        printf("%d Has been produced.\n",item);
        shm->i[shm->count] = item;
        shm->count++;
        sleep(2);
        up(semID,MUTEX); //mutex is unblocked
        if(shm->count == 4){ //once count is full, 5 rounds of consumer are set.
        printf("Producer has finished.\n");
            for(int i = 0; i < 5; i++){
                up(semID,FULL);
            }
        }
}



    exit(0);
}
