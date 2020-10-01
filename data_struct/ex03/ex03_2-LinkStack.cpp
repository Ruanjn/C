#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#define OVERFLOW -2
typedef int ElemType;

typedef struct StackNode{
    ElemType data;
    struct StackNode* next;
}StackNode,* Linktop;

typedef struct LinkStack{
    Linktop top;
    ElemType count;
}LinkStack;
// 初始化
ElemType InitStack(LinkStack* stack){
    if(!stack)return 0;
    stack->top = NULL;
    stack->count = 0;
    return 1;
}
// 获取栈顶指针
ElemType GetTop(LinkStack* stack,StackNode** stackNode){
    if(!stack)return 0;
    *stackNode =stack->top;
    return 1;
    
}
// 出栈
ElemType pop(LinkStack* stack,ElemType &e){
    if(!stack && stack->count)return 0;
    StackNode* node = stack->top;
    e = node->data;
    stack->top=node->next;
    free(node);
    stack->count--;
    return 1;
}
// 入栈
ElemType Insert(LinkStack* stack,ElemType e){
    if(!stack)return 0;
    StackNode* node = (StackNode*)malloc(sizeof(StackNode));
    node->next = stack->top;
    node->data = e;
    stack->top = node;
    stack->count++;
    return 1;
}
// 清空栈
ElemType ClearStack(LinkStack* stack){
    if(!stack||stack->count)return 0;
    while(stack->count){
        StackNode* node = stack->top;
        stack->top=node->next;
        free(node);
        stack->count--;
    }
    return 1;
}
// 销毁栈
ElemType destroyStack(LinkStack* stack){
    ClearStack(stack);
    free(stack->top);
    return 1;
}
// 判断栈是否空
ElemType StackEmpty(LinkStack* stack){
    if(!stack)return 0;
    return stack->count == 0?1:0;
}
// 进制转换
ElemType conversion(LinkStack* S,ElemType N ,FILE *p){
    ElemType e;
    fprintf(p,"%d--->",N);
    while(N){
        Insert(S,N%2);
        N/=2;
    }
    while(!StackEmpty(S)){
        pop(S,e);
        fprintf(p,"%d",e);
    }
        fprintf(p,"\n");
}
int main(){
    int number;
    int byte;
    LinkStack S;
    InitStack(&S);
    FILE *ip = fopen("input_2.txt","r");
    FILE *op = fopen("output_2.txt","a");
    while(1){
        fscanf(ip,"%d",&number);
        if(number==-1)break;
        conversion(&S,number,op);
    }
    // 释放栈的内存，关闭文件
    destroyStack(&S);
    fclose(ip),fclose(op);
}