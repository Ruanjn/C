
/*
 * @Author: Natsukiz
 * @Date: 2020-10-11 00:48:20
 * @LastEditTime: 2020-10-11 00:54:03
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /home/natsuki/ex02/ex02.c
 */

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
/**
 * [get_error get error information from log file]
 * @param fp [the pointer of log file]
 */
void get_error(FILE* fp) {
    char buffer[1024];
    char buffer_err[1024];

    char number[10] = {'\0'};
    int i = 0;

    char* n = NULL;
    char* err = NULL;
    char* p = NULL;
    const char error_char[6] = "error";

    // open error.log FILE
    FILE* save;
    save = fopen("/home/natsuki/error.log", "a");
    if (save == NULL) {
        printf("File open error\n");
        return;
    }
    // read file by line
    while (fgets(buffer, sizeof(buffer), fp)) {
    START:
        p = strstr(buffer, "error");
        if (p) {
            // printf("%s", buffer);
            fprintf(save, "%s", buffer);
            memset(number, '\0', sizeof(number));
            n = strchr(buffer, '[');
            for (int i = 1; n[i] != ']'; i++) {
                number[i - 1] = n[i];
            }
            strncpy(number, number, i);
            while (fgets(buffer_err, sizeof(buffer_err), fp)) {
                if (strstr(buffer_err, number)) {
                    // printf("%s\n", buffer_err);
                    fprintf(save, "%s", buffer_err);
                } else {
                    strcpy(buffer, buffer_err);
                    goto START;
                }
            }
        }
    }
    free(n);
    free(err);
    free(p);
    fclose(save);
}
/**
 * [main description]
 * @param  argc [int amounts of args]
 * @param  argv [char*]
 * @return      [int]
 */
int main(int argc, char* argv[]) {
    FILE* fd;
    // check argc and args
    int ret = 0;
    if (argc != 2) {
        printf("Please provide the filename as argument to read\n");
        exit(EXIT_FAILURE);
    }
    // open log file & check
    fd = fopen(argv[1], "r");
    if (!fd) {
        printf("Error in opening the file error=%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    // get error
    get_error(fd);

    fclose(fd);

    return EXIT_SUCCESS;
}