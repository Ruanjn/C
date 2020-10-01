

typedef BiTree* QElemtype;

typedef struct  QueueNode{
    QElemtype e;
    struct QueueNode* next;
}QueueNode,*LinkeQueuePoi;

typedef struct LinkQueue{
    LinkeQueuePoi front;
    LinkeQueuePoi rear;
}LinkQueue;

int  InitLinkQueue(LinkQueue* queue){
    if(!queue){
     return 1;   
    }
    QueueNode* node=(QueueNode*)malloc(sizeof(QueueNode));
    node->next=NULL;
    queue->front = queue->rear =node;
}
int ClearLinkQueue(LinkQueue* queue){
    if(!queue)return 1;
    if(queue->front==queue->rear){
        return 1;
    }
    QueueNode* node =queue->front->next;
    while(node){
        queue->front->next=node->next;
        if(queue->rear ==node){
            queue->rear = queue->front;
        }
        free(node);
        node=queue->front->next;
            }
}
int isEmpty(LinkQueue* queue){
    if(!queue){
        return 1;
    }
    if(queue->front ==queue->rear){
        return 1;
    }
    return 0;
}
int AddQ(LinkQueue* queue,QElemtype e){
    if(!queue)return 1;
    QueueNode* node =(QueueNode*)malloc(sizeof(QueueNode));
    if(!node){
        return 1;
    }
    node->next=NULL;
    node->e=e;
    queue->rear->next =node;
    queue->rear =node;
    return 0;
}
int DeletQ(LinkQueue* queue,QElemtype *e){
    if(!queue)return 1;
    QueueNode* node = queue->front->next;
    queue->front->next=node->next;
    *e=node->e;
    if(node = queue->rear){
        queue->rear=queue->front;
    }
    return 0;
}
int LengthLinkQueue(LinkQueue* queue){
    if(!queue)return 1;
    if(queue->front ==queue->rear)return 0;
    QueueNode* node =queue->front ->next;
    int num=0;
    while(node){
        node = node->next;
        num++; 
    }
    return num;
}

/* int main(int argc,char *argv[]){
    LinkQueue queue;
    InitLinkQueue(&queue);
    int max=10;
    int i=0;
    for(i=0;i<max;i++){
        AddQ(&queue,i);
    }
    DeletQ(&queue);
    DeletQ(&queue);
    ClearLinkQueue(&queue);
} */