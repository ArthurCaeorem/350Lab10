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
    key_t key;
    int msgqID;
    if ((key = ftok("msgQsnd.c", 'A')) == -1) { 
perror("ftok error");
exit(1);
}
/* open message queue already created by kirk.c */
if ((msgqID = msgget(key, 0644)) == -1) {
perror("msgget error");
exit(1);
}
    while(msgrcv(msgqID, (struct msgbuf *)&buf, sizeof(buf), 0, 0) != -1){
        int in1 = atoi(buf.i1);
        int in2 = atoi(buf.i2);
        printf("Sum of number is %d \n",in1 + in2);
    }
    exit(0);
}
