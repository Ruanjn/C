#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#define LIST_INIT_SIZE 100
#define OVERFLOW -2

//------------------------------关键变量声明区域-----------------------------
int iCount;//用于最后输出时case后的计数
int Listlength;//用于表示归并后表的长度
typedef int ElemType;//顺序表初始化时用到InitList

typedef struct{
    ElemType *elem;//分配的内存空间
    int length;//实际长度
    int listsize;//最大长度
} SqList;//定义顺序表

SqList LA;
SqList LB;//定义顺序表LA与LB与Lc
SqList Lc;

//------------------------------函数声明区域----------------------------
int InitList_Sq(SqList &L){
    L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));//顺序表分配内存空间
    if (!L.elem)
        exit(OVERFLOW);//分配失败退出
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;//顺序表长度与最大长度初始化
    return 1;
}

void DestroyList(SqList &L){
    if (L.elem)
        delete[] L.elem;
}//删除顺序表，释放内存

void clean(){
    DestroyList(LA);
    DestroyList(LB);
}//快速删除顺序表操作
void Listinput(FILE *fp){
    int i = 0;
    int number;
    Listlength=0;
    fscanf(fp, "%d", &number);
    if (number == -1){
        clean();
        fprintf(fp, "Linked list sort\n");
        fclose(fp);
        exit(OVERFLOW);
    }//判断文件是否终止（-1），【清除LA与LB缓存并关闭文件后】退出
    Listlength+= number;
    LA.length = number;//确定顺序表长度
    for (i = 0; i < LA.length; i++){
        fscanf(fp, "%d", &number);
        LA.elem[i] = number;//赋值给顺序表
    }
    fscanf(fp, "%d", &number);
    Listlength+= number;
    LB.length = number;
    for (i = 0; i < LB.length; i++){
        fscanf(fp, "%d", &number);
        LB.elem[i] = number;
    }
}
void MergeList(SqList &A, SqList &B){
    SqList Lc;
    iCount++;//每次进入MergeList，关于case的计数器iCount++
    int i = 0;//用于此函数最后阶段的循环输出
    int *pa = A.elem;
    int *pb = B.elem;//定义指向A与B顺序表中的元素
    int *pc, *pa_last, *pb_last;//分别为指向C中元素的指针，与指向A、B元素末尾的指针
    Lc.listsize = Lc.length = A.length + B.length;//定义Lc的长度为A+B
    pc = Lc.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));//分配Lc的内存空间
    if (!Lc.elem)exit(OVERFLOW);//分配失败退出
    pa_last = A.elem + (A.length - 1);
    pb_last = B.elem + (B.length - 1);//使指针指向A、B末尾
    while (pa <= pa_last && pb <= pb_last){//判断pa与指针pb是否达到末尾
        if (*pa <= *pb) *pc = *pa,pa++, pc++;
        else *pc = *pb,pc++, pb++;
    }//按从小到大的顺序赋值给Lc
    while (pa <= pa_last){
        *pc = *pa,pc++,pa++;
    }//若LB有剩余，将LB中元素赋值给LC
    while (pb <= pb_last){
        *pc = *pb, pc++,pb++;
    }//若LB有剩余，将LB中元素赋值给LC

    FILE *fo = fopen("output.txt", "a");//打开输出文件output.txt
    fprintf(fo, "case %d:%d\n", iCount,Listlength);//输出案例组别
    for (i = 0; i < Lc.length; i++)
        fprintf(fo, "%d ", Lc.elem[i]);//循环输出Lc元素
    fprintf(fo, "\n");
    fclose(fo);//关闭输出文件
    DestroyList(Lc);//释放Lc内存
}

//--------------------主函数执行区域-----------------------
int main(){
    iCount = 0;//计数器初始化
    FILE *fp = fopen("input.txt", "r");//打开输入文件
    while (1){
        InitList_Sq(LA);
        InitList_Sq(LB);//创建顺序表
        Listinput(fp);//顺序表赋值
        MergeList(LA, LB);//顺序表组合与输出
        clean();//【释放LA，LB内存】
    }
    fclose(fp);
    return 0;
}