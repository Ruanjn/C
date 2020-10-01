#define PI 3.1415926
#ifndef _Debug
#include <time.h>
#endif  // !_Debug

double arcArea(double range);
double arcPerimeter(double range);
double sphereVolume(double range);
void bubbleSort(int* p, int size);
void swapSort(int* p, int size);
void insertSort(int* p, int size);
void insertSort(int* p, int size);
void showTime();

/** @name arcArea
 *  @brief 计算圆面积
 *  @param range type:double;圆半径
 *  @return 返回圆面积
 *  @version 0.0.1
 *  @date 2020/8/31
 *  */
double arcArea(double range) {
    return range * range * PI;
}

/** @name arcPerimeter
 *  @brief 计算圆周长
 *  @param range type:double;圆半径
 *  @return 返回圆周长
 *  @version 0.0.1
 *  @date 2020/8/31
 *  */
double arcPerimeter(double range) {
    return 2 * range * PI;
}

/** @name sphereVolume
 *  @brief 计算球体体积
 *  @param range type:double;球半径
 *  @return 返回球体体积
 *  @version 0.0.1
 *  @date 2020/8/31
 *  */
double sphereVolume(double range) {
    return 4.0 / 3.0 * PI * range * range * range;
}

/** @name bubbleSort
 *  @brief 冒泡排序 升序
 *  @param p type:int point 数组头指针
 *  @param size type:int  数组长度
 *  @return void
 *  @version 1.0.0
 *  @date 2020/9/2
 *  */
void bubbleSort(int* p, int size) {
    int iTmp;
    for (int i = 0; i < size; i++) {
        for (int j = size - 1; j >= i; j--) {
            if (p[j] < p[j - 1]) {
                iTmp = p[j];
                p[j] = p[j - 1];
                p[j - 1] = iTmp;
            }
        }
    }
    return;
}

/** @name swapSort
 *  @brief 交换排序 升序
 *  @param p type:int point 数组头指针
 *  @param size type:int  数组长度
 *  @return void
 *  @version 1.0.0
 *  @date 2020/9/2
 *  */
void swapSort(int* p, int size) {
    int iTmp;
    for (int i = 0; i < size; i++)
        for (int j = i + 1; j < size; j++) {
            if (p[i] > p[j]) {
                iTmp = p[i];
                p[i] = p[j];
                p[j] = iTmp;
            }
        }
    return;
}

/** @name insertSort
 *  @brief 插入排序 升序
 *  @param p type:int point 数组头指针
 *  @param size type:int  数组长度
 *  @return void
 *  @version 1.0.0
 *  @date 2020/9/3
 *  */
void insertSort(int* p, int size) {
    int cur, i, j;
    for (i = 1; i < size; i++) {
        cur = p[i];
        for (j = i - 1; j >= 0 && p[j] > cur; j--) {
            p[j + 1] = p[j];
        }
        p[j + 1] = cur;
    }
    return;
}

/** @name showTime
 *  @brief 打印系统当前时间
 *  @return void
 *  @version 0.0.1
 *  @date 2020/9/4
 *  */
void showTime() {
    struct tm* sysTime;
    time_t nowTime;
    time(&nowTime);
    sysTime = localtime(&nowTime);
    printf("System Time: %d-%d-%d %02d:%02d:%02d\n", 1900 + sysTime->tm_year,
           sysTime->tm_mon + 1, sysTime->tm_mday, sysTime->tm_hour,
           sysTime->tm_min, sysTime->tm_sec);
    return;
}
