#include <stdio.h>
#include <unistd.h>	//包含sleep等函数
#include <stdbool.h>
#include <threads.h>	//包含多线程支持库头文件
#include <stdlib.h>	//包含exit等函数

int thr_fun(void *);

int test_thread(void) {
    thrd_t thr;
    int ret; //保存thrd_create函数的返回值用于判断线程是否创建成功：0为成功，1为失败。
    ret = thrd_create(&thr, thr_fun, NULL); //将thr_fun函数放在一个新的线程中执行
    if (ret != thrd_success) {
        printf("error!!!\n");
        getchar();
        exit(-1);
    }
    ret = thrd_detach(thr); //通知操作系统，该线程结束时由操作系统负责释放资源。
    if (ret != thrd_success) {
        printf("error!!!\n");
        getchar();
        exit(-1);
    }
    for (int i = 0; i < 10; i++) {
        sleep(2);
        printf("I love ibadboy.net~~~\n");
    }
    getchar();
    return 0;
}

int thr_fun(void *argv) {
    int i = 0;
    while (true) {
        i++;
        sleep(1);
        printf("He love ibadboy.net!!!\n");
        if (i == 10) {
            thrd_exit(0);
        }
    }
}