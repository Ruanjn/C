#include<stdio.h>
#include<stdlib.h>

typedef char TElemType;

typedef struct BiTNode{
    TElemType data;
    struct BiTNode *lchild,*rchild;
}BiTNode,* BiTree;
void InitBiTree(BiTree &T){
    T=NULL;
}
void CreatBiTree(BiTree &T){
    char c;
    c=getchar();
    if(c=='#'||c==' ') T=NULL;
    else{
        T=new BiTNode;  T->data=c;
        CreatBiTree(T->lchild);
        CreatBiTree(T->rchild);
    }
};
 /**function：PreOrderTraverse
  * 前序遍历二叉树
  * 参数：BiTree类型 二叉树；
  */
void PreOrderTraverse(BiTree &T){
    if(T){
        printf("%c",T->data);
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
}
/**
 *function：InOrderTraverse
 * 后序遍历二叉树
 * 参数：BiTree类型 二叉树；
 */
void InOrderTraverse(BiTree &T){
    if(T){
        InOrderTraverse(T->lchild);
        printf("%c",T->data);
        InOrderTraverse(T->rchild);
    }
}
/**
 * function：PostOrderTraverse
 * 后序遍历二叉树
 * 参数：BITree 二叉树；
 */
void PostOrderTraverse(BiTree &T){
    if(T){
        PostOrderTraverse(T->lchild);
        PostOrderTraverse(T->rchild);
        printf("%c",T->data);
    }
}
/**
 * 层次遍历二叉树
 * 参数
 */
void LevelOrderTraverse(BiTNode node){
    int front=0,rear=0;
    LinkQueue Queue;
    BiTree ptr;
    if(!ptr) return;
    AddQ( &Queue,ptr);
    for(;;){
        DeletQ(&Queue,&ptr);
        if(ptr){
        printf("%d",ptr->data);
        if(ptr->lchild)
        AddQ(&Queue,ptr->lchild);
        if(ptr->rchild)
        AddQ(&Queue,ptr->rchild);
    }else break;
    
}
}
int iterInorder(BiTree &T,LinkStack *S){
    BiTree p;
    InitStack(S);
    Push(S,T);
    while(!StackEmpty(S)){
        while(GetTop(S,p)&&p)Push(S,p->lchild);
        pop(S,p);
        if(!StackEmpty(S)){
            pop(S,p);
            if(p->data==NULL)return -1;
            Push(S,p->rchild);
        }
    }
    return 0;
}
int leaf(BiTree &T){
    if(T==NULL)return 0;
    if(T->lchild==NULL&&T->rchild==NULL)
        return 1;
    else return (leaf(T->lchild)+leaf(T->rchild));
}

int height(BiTree &T){
    int n=0,m=0;
    if(T ==NULL) return 0;
    else{
        m=height(T->lchild);
        n=height(T->rchild);
        if(m>n) return (m+1);
        else return (n+1);
    }
}
//---------------------------------------------------------
//---------------------------------------------------------
typedef BiTree SElemType;

typedef struct StackNode{
    SElemType data;
    struct StackNode* next;
}StackNode,* Linktop;

typedef struct LinkStack{
    Linktop top;
    SElemType count;
}LinkStack;

int  InitStack(LinkStack* stack){
    if(!stack)return 0;
    stack->top = NULL;
    stack->count = 0;
    return 1;
}
SElemType GetTop(LinkStack* stack,SElemType stackNode){
    if(!stack)return 0;
    return stack->top->data;
}
int pop(LinkStack* stack,SElemType &e){
    if(!stack && stack->count)return 0;
    StackNode* node = stack->top;
    e = node->data;
    stack->top=node->next;
    free(node);
    stack->count--;
    return 1;
}
int Push(LinkStack* stack,SElemType e){
    if(!stack)return 0;
    StackNode* node = (StackNode*)malloc(sizeof(StackNode));
    node->next = stack->top;
    node->data = e;
    stack->top = node;
    stack->count++;
    return 1;
}
int ClearStack(LinkStack* stack){
    if(!stack||stack->count)return 0;
    while(stack->count){
        StackNode* node = stack->top;
        stack->top=node->next;
        free(node);
        stack->count--;
    }
    return 1;
}
int destroyStack(LinkStack* stack){
    ClearStack(stack);
    free(stack->top);
    return 1;
}
int StackEmpty(LinkStack* stack){
    if(!stack)return 0;
    return stack->count == 0?1:0;
}
//-----------------------------------------------------------------
//-----------------------------------------------------------------


typedef BiTree QElemtype;

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