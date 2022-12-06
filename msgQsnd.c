#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
struct ints{
    long mtype;
char i1[20];
char i2[20];
};
int main(){
    struct ints buf;
    int l,e = 0;
    key_t key;
    int msgqID;
    key = ftok("msgQsnd.c", 'A');
    msgqID = msgget(key, 0644 | IPC_CREAT);
    buf.mtype = 1;
    while(!feof(stdin)){
        printf("Print 1st number: ");
        l = scanf("%s",buf.i1);
        if(l == -1){
            break;
        }
        printf("Print 2nd number: ");
        e = scanf("%s",buf.i2);
        if(e == -1){
            break;
        }
        msgsnd(msgqID, (struct msgbuf *)&buf, sizeof(buf), 0);
    }
    printf("\n");
    msgctl(msgqID, IPC_RMID, NULL);
    exit(0);
}
