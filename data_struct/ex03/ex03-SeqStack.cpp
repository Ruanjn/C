#include<stdio.h>
#include<stdlib.h>
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define OVERFLOW -2
typedef int ElemType;
typedef struct{
    ElemType *base;  //在构造和销毁之后，base为NULL
    ElemType *top;  //栈顶指针
    int stacksize;  //当前分配的内存空间
}SqStack;
// 初始化栈
int InitStack(SqStack &S){
    S.base = (ElemType * )malloc(STACK_INIT_SIZE * sizeof(ElemType));
    if(!S.base)exit(OVERFLOW);//分配内存失败，推出程序
    S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;
    return 1;
}//InitStack
// 栈顶元素出栈
int Pop(SqStack &S,ElemType &e){
    if(S.top == S.base)return 0;
    e = *--S.top;
    return 1;
}//Pop
// 元素入栈
int InSert(SqStack &S,ElemType e){
    if(S.top - S.base >= S.stacksize){
        S.base = (ElemType * )realloc(S.base,
                    (S.stacksize+STACKINCREMENT) * sizeof(ElemType));
    
    if(!S.base)exit(OVERFLOW);

    S.top = S.base + S.stacksize;
    S.stacksize += STACKINCREMENT;
    }
    * S.top++ = e;
    return 1;
}//Set
// 清空栈
int ClearStack(SqStack &S){
    S.top=S.base;
    return 1;
}//ClearStack
// 销毁栈
int DestroyStack(SqStack &S){
    free(S.base);
    S.base = NULL;
    S.top = NULL;
    S.stacksize = 0;
    return 1;
}//DestroyStack
// 判断是否为空栈
int StackEmpty(SqStack &S){
    if(S.base==S.top){
        return 1;
    }else{
        return 0;
    }
}
// 进制转换方法函数
void conversion(SqStack &SA,ElemType N,FILE *op){
    ElemType e;
    fprintf(op,"%d--->",N);    
    // 用2除余的方法将每一位入栈
    while (N){
        InSert(SA,N%2);
        N/=2;
    }
    // 出栈输出
    while(!StackEmpty(SA)){
        Pop(SA,e);
        fprintf(op,"%d",e);
    }
    // fprintf(op,"%d",Byte);
    fprintf(op,"\n");
}

int main(){
    int number;
    // 栈定义与初始化
    SqStack SA;
    InitStack(SA);
    // 文输入与输出文件的打开
    FILE *ip = fopen("input_2.txt","r");
    FILE *op = fopen("output_2.txt","a");
    while(1){
        fscanf(ip,"%d",&number);
        if(number==-1)break;
        conversion(SA,number,op);
    }
    // 释放栈的内存，关闭文件
    DestroyStack(SA);
    fclose(ip),fclose(op);
    return 0;
}