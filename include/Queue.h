#include<stdio.h>
#define MAXQSIZE 100
typedef struct{
    QElemType *base;
    int front;
    int rear;
}SqQueue;

int InitQueue(SqQueue &Q){
    Q.base = (QElemType * )malloc(MAXQSIZE * sizeof (QElemType));
    if(!Q.base)return 0;
    Q.front = Q.rear=0;
}

int QueueLength(SqQueue &Q){
    return(Q.rear-Q.front +MAXQSIZE) % MAXQSIZE;
}
int ENQueue(SqQueue &Q,QElemType e){
    if((Q.rear+1)% MAXQSIZE == Q.front)return 0;
     Q.base[Q.rear]=e;
     Q.rear=(Q.rear+1)%MAXQSIZE;
 }
int isFull(SqQueue &Q){
    if((Q.rear+1)% MAXQSIZE == Q.front)
        return 1;
    else 
        return 0;
}
int isEmpty(SqQueue &Q){
    if(Q.front==Q.rear)
        return 1;
    else
        return 0;
    
}
int DeQueue(SqQueue &Q,QElemType &e){
    if(Q.front==Q.rear)return 1;
    e=Q.base[Q.front];
    Q.front=(Q.front+1)% MAXQSIZE;
    return 0;
}

// int main(){
//     SqQueue Queue;
//     InitQueue(Queue);
//     ENQueue(Queue,20);
//     ENQueue(Queue,40);
//     int a;
//     a=1;
// }