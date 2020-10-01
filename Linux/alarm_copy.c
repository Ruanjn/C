/*
 * @Author: Cherry
 * @Date: 2020-09-27 14:41:44
 * @LastEditTime: 2020-09-28 09:42:51
 * @LastEditors: Please set LastEditors
 * @Description: Scheduled copy folder
 * @FilePath: ~/test/alarm_copy.c
 */
#include <dirent.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

/**
 * @description: return time info
 * @return {struct tm*}
 */
struct tm* getTime() {
    time_t tt;
    time(&tt);
    return localtime(&tt);
}
/**
 * @description: judge whether it's dir
 * @param {char*} path
 * @return {int}
 */
int is_dir(char* path) {
    struct stat st;
    stat(path, &st);
    if (S_ISDIR(st.st_mode)) {
        return 1;
    } else {
        return 0;
    }
}
/**
 * @description:
 * @param {type}
 * @return {type}
 */
int endwith(char* s, char c) {  //用于判断字符串结尾是否为“/”
    if (s[strlen(s) - 1] == c) {
        return 1;
    } else {
        return 0;
    }
}
char* str_contact(char* str1, char* str2) {  //字符串连接
    char* result;
    result = (char*)malloc(strlen(str1) + strlen(str2) +
                           1);  // str1的长度+str2的长度+\0;
    if (!result) {              //如果内存动态分配失败
        printf("字符串连接时，内存动态分配失败\n");
        exit(1);
    }
    memset(result, 0, sizeof(result));
    strcat(result, str1);
    strcat(result, str2);  //字符串拼接
    return result;
}
/*复制函数*/
void copy_file(char* source_path, char* destination_path) {  //复制文件
    char buffer[1024];
    FILE *in, *out;  //定义两个文件流，分别用于文件的读取和写入int len;
    if ((in = fopen(source_path, "r")) == NULL) {  //打开源文件的文件流
        printf("源文件打开失败！\n");
        exit(1);
    }
    if ((out = fopen(destination_path, "w")) == NULL) {  //打开目标文件的文件流
        printf("目标文件创建失败！\n");
        exit(1);
    }
    int len;  // len为fread读到的字节长
    while (
        (len = fread(buffer, 1, 1024, in)) >
        0) {  //从源文件中读取数据并放到缓冲区中，第二个参数1也可以写成sizeof(char)
        fwrite(buffer, 1, len, out);  //将缓冲区的数据写到目标文件中
    }
    fclose(out);
    fclose(in);
}
void copy_folder(char* source_path,
                 char* destination_path,
                 FILE* fp) {  //复制文件夹
    if (!opendir(destination_path)) {
        if (mkdir(destination_path, 0777))  //如果不存在就用mkdir函数来创建
        {
            printf("创建文件夹失败！");
        }
    }
    char* path;
    path = (char*)malloc(
        512);  //相当于其它语言的String
               // path=""，纯C环境下的字符串必须自己管理大小，这里为path直接申请512的位置的空间，用于目录的拼接
    memset(path, 0, 512);
    // strcpy(path,source_path);
    path = str_contact(path, source_path);  //这三句，相当于path=source_path
    struct dirent* filename;
    DIR* dp = opendir(path);  //用DIR指针指向这个文件夹
    while (filename =
               readdir(dp)) {  //遍历DIR指针指向的文件夹，也就是文件数组。
        memset(path, 0, sizeof(path));
        path = str_contact(path, source_path);
        //如果source_path,destination_path以路径分隔符结尾，那么source_path/,destination_path/直接作路径即可
        //否则要在source_path,destination_path后面补个路径分隔符再加文件名，谁知道你传递过来的参数是f:/a还是f:/a/啊？
        char* file_source_path;
        file_source_path = (char*)malloc(512);
        if (!endwith(source_path, '/')) {
            file_source_path = str_contact(file_source_path, source_path);
            file_source_path = str_contact(source_path, "/");
        } else {
            file_source_path = str_contact(file_source_path, source_path);
        }
        char* file_destination_path;
        file_destination_path = (char*)malloc(512);
        if (!endwith(destination_path, '/')) {
            file_destination_path =
                str_contact(file_destination_path, destination_path);
            file_destination_path = str_contact(destination_path, "/");
        } else {
            file_destination_path =
                str_contact(file_destination_path, destination_path);
        }
        //取文件名与当前文件夹拼接成一个完整的路径
        file_source_path = str_contact(file_source_path, filename->d_name);
        file_destination_path =
            str_contact(file_destination_path, filename->d_name);
        if (is_dir(file_source_path)) {  //如果是目录
            if (!endwith(
                    file_source_path,
                    '.')) {  //同时并不以.结尾，因为Linux在所有文件夹都有一个.文件夹用于连接上一级目录，必须剔除，否则进行递归的话，后果无法相像
                copy_folder(file_source_path, file_destination_path,
                            fp);  //进行递归调用，相当于进入这个文件夹进行复制～
            }
        } else {
            copy_file(
                file_source_path,
                file_destination_path);  //否则按照单一文件的复制方法进行复制。
            printf("复制%s到%s成功！\n", file_source_path,
                   file_destination_path);
            struct tm* sysTime = getTime();
            fprintf(fp, "%d-%d-%d %02d:%02d:%02d %s -> %s\n",
                    1900 + sysTime->tm_year, sysTime->tm_mon + 1,
                    sysTime->tm_mday, sysTime->tm_hour, sysTime->tm_min,
                    sysTime->tm_sec, file_source_path, file_destination_path);
        }
    }
    free(path);
}
void loopFunction() {
    printf("Start to Copy File\n");
    // Copy operation
    // DIR* source = opendir(source_path);
    // DIR* destination = opendir(destination_path);
    // if (!source || !destination) {
    //     printf("你输入的一个参数或者第二个参数不是文件夹！\n");
    // }
    // free(source);
    // free(destination);
    FILE* fp;
    char source1[17] = "/usr/local/data";
    char source2[17] = "/home/user/backup";
    char* source_path;
    char* destination_path;
    source_path = source1;
    destination_path = source2;
    fp = fopen("/home/user/list", "a");
    if (fp == NULL) {
        printf("File creats error\n");
        return;
    }
    // lseek(fp,0,SEEK_END);
    fprintf(fp, "-----------------------------------\n");
    copy_folder(source_path, destination_path, fp);  //进行文件夹的拷贝
    fprintf(fp, "-----------------------------------\n");
    fclose(fp);
    printf("Copy File succeed\n");
    signal(SIGALRM, loopFunction);
    alarm(10);
}
int main() {
    loopFunction();
    int i = 0;
    for (i = 1; i < 7201; i++) {
        printf("sleep %d...\n", i);
        sleep(1);
    }
    return 0;
}
