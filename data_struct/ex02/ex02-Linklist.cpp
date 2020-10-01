#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#define OVERFLOW -2


//--------------------关键变量声明区域-------------------
typedef int ElemType;//顺序表初始化时用到InitList

typedef struct LNode{
    ElemType data;
    struct LNode *next;
}LNode, *LinkList;//定义链表

int iCount;//用于计算案例数量的计数器0
int Listlength;

LinkList LA;LinkList LB;LinkList LC;
//创建链表LA，LB，LC，前两者用于储存输入的数据，后者用于存储排序后的数据
FILE *fp = fopen("input.txt", "r");
//在程序最开头打开文件（危险）
//因为在初始化链表的函数中使用了文件的指针，只是在main函数中打开文件无法编译



//----------------------------函数声明区域----------------------
//初始化链表函数，参数为要初始化的链表和链表的总长度
LinkList CreateList_L(LinkList &L,int n){
    int i;
    //顺位序输入n个元素的值，建立表头结点的单链线性表L
    L = (LinkList)malloc(sizeof(LNode));
    L->next = NULL;//先建立一个带头结点的单链表
    LinkList p;
    LinkList r=L;
    int numbers;
    for(i=n;i>0;--i){
        p = (LinkList)malloc(sizeof(LNode));//给p分配内存；
        fscanf(fp, "%d", &p->data);//对应程序开头的文件打开；
        p->next = NULL;r->next = p;r=p;
    }//读取文件中的数据赋给每个结点的数据data
    r->next = NULL;//制定尾结点的指针为空
    return L;
}
void MergeList_L(LinkList &La,LinkList &Lb,LinkList &Lc){
    int i;
    LinkList pa,pb,pc;
    //已知单链线性表La和Lb的元素按值非递减排列
    //归并La和Lb得到新的单链线性表Lc，Lc的元素也按值非递减排列
    pa = La->next; pb = Lb->next;
    Lc = pc =La;//用La的头结点作为Lc的头结点
    while(pa&&pb){
        if(pa->data<= pb->data){
            pc->next = pa;pc = pa;pa = pa->next;
        }else{
            pc->next = pb;pc = pb;pb =pb->next;
        }
    }//通过改变pc->next的指向而不是重新给Lc、pc分配内存
    pc->next = pa ? pa :pb;//当一个链表指针遍历完后，将当前结点的指针指向另一链表的下一级结点
    free(Lb);
    FILE *fo = fopen("output.txt", "a");//打开输出文件output.txt
    fprintf(fo, "case %d:%d\n", iCount,Listlength);//输出案例组别
    pc=Lc->next;//将pc重新指向数据有意义的第一结点
    while (pc){
        fprintf(fo, "%d ", pc->data);//循环输出Lc元素
        pc=pc->next;
    }
    free(Lc);
    fprintf(fo, "\n");
    fclose(fo);//关闭输出文件
}

void Listinput(FILE *fp){
    int i = 0;
    int number;
    Listlength=0;
    fscanf(fp, "%d", &number);
    if (number == -1){
        fprintf(fp, "Order list sort\n");
        fclose(fp);
        exit(OVERFLOW);
    }//判断文件是否终止（-1），【清除LA与LB缓存并关闭文件后】退出
    Listlength+=number;
    LA=CreateList_L(LA,number);
    fscanf(fp, "%d", &number);
    Listlength+=number;
    LB=CreateList_L(LB,number);
}

//--------------------主函数执行区域-----------------------

int main(){
    iCount = 0;//计数器初始化
    while (1){
        iCount++;
        Listinput(fp);//顺序表赋值
        MergeList_L(LA, LB, LC);//顺序表组合与输出
    }
    fclose(fp);
    return 0;
}