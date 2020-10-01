#include <math.h>
#include <stdio.h>
#include <stdlib.h>
int r[] = {1, 1, 2, 3, 5, 7};  //储存圆半径的数组
#define length 6               //数组长度
double x[length];              //横坐标
int b[6];                      //最佳排列的数组
int Note = 0;

double minlength =
    1000;  //最小值的长度，只有小于这个值才能符合条件，所以不能为0

int Swap(int r[], int x, int y) {
    int iTemp = r[x];
    r[x] = r[y];
    r[y] = iTemp;
}

double center(int t) {
    double distance = 0;
    if (t == 0) {
        distance = 0;
    } else {
        for (int i = 0; i < t; ++i) {
            if (x[i] + 2 * sqrt(r[i] * r[t]) >
                distance)  //如果符合，说明真正相切的圆在后面
                distance = x[i] + 2 * sqrt(r[i] * r[t]);
            else
                i++;
        }
    }
    return distance;
}

int Calculate(int t) {
    x[t] = center(t);  //获取x的横坐标
    double left =
        0;  // left,right是这一次比较中的临时变量，用于代表最左的坐标和最右的坐标
    double right = 0;
    for (int i = 0; i < length; ++i) {
        if (x[i] - r[i] < left)
            left = x[i] - r[i];
        if (x[i] + r[i] > right)
            right = x[i] + r[i];
    }
    if ((right - left) <=
        minlength) {  //如果这次的长度小于minlength，则为目前最优解
        minlength = right - left;  //更新最小长度
        for (int i = 0; i < length; ++i)
            b[i] = r[i];  //记录当前最佳数组排列
        printf("\nminlength update!is %f\n", minlength);
    } else
        printf("\nnow %f large minlength = %f ?\n", right - left, minlength);
    printf("\n--------------------------------------------\n");
}

int Solve(int t) {
    if (t == length - 1) {  //如果已经到了最后一个圆
        Calculate(t);       //则进入计算该排列组合的长度函数中
        Note++;             //已经经过calculate
    } else {
        for (int i = t; i < length; ++i) {
            printf("\nnow,is %d th for\n", t + 1);
            Swap(r, t, i);  //在i=t之后进行全排序
            if (Note == 1)
                i--;
            else if (Note == 2) {
                Note = 0;
                return 0;
            }
            printf("the list now:\n");
            for (int j = 0; j < length; ++j)
                printf("%d ", r[j]);
            x[i] = center(i);  //获取x的横坐标
            printf("\njudging %d ,value %d is vaild\n", i, r[i]);
            if (r[1] + x[i] + r[i] <
                minlength)  //剪枝判断：如果大于则进入else将数组复原
            {
                printf("success!next for \n");
                Solve(t + 1);
            } else {
                printf("failed,back for\n");
                Swap(r, t, i);
            }
        }
    }
}

int main(int argc, char const* argv[]) {
    /* code */
    int t = 0;  //数组游标
    for (int i = 0; i < length; ++i)
        x[i] = 0;
    Solve(t);
    printf("\nthe last:\nminlength = %f\n array: ", minlength);
    for (int i = 0; i < length; ++i)
        printf("%d ", b[i]);
    system("pause");
    return 0;
}