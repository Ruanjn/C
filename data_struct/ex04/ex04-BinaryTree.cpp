#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include"function.h"
BiTree Tree;
LinkQueue queue;
LinkStack stack;
int main(){    
    InitBiTree(Tree);
    InitLinkQueue(&queue);
    InitStack(&stack);
    CreatBiTree(Tree);
    // PreOrderTraverse(Tree);
    // printf("\n");
    // InOrderTraverse(Tree);
    // printf("\n");
    PostOrderTraverse(Tree);
    printf("\n");
    int a;
    a=1;
    return 0;
}
//ABD#G###CE##FH###