//
// Created by lWoHvYe on 2023/8/20.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// 共享资源和互斥锁
int sharedCounter = 0;
pthread_mutex_t mutex;

// 线程函数
void *incrementCounter(void *arg) {
    printf("Start currency \n");
    for (int i = 0; i < 10000; i++) {
        pthread_mutex_lock(&mutex); // 上锁
        sharedCounter++;
        pthread_mutex_unlock(&mutex); // 解锁
    }
    printf("Finish currency \n");
    return NULL;
}

int test_demo() {
    pthread_t thread1, thread2, thread3, thread4;

    // 初始化互斥锁
    pthread_mutex_init(&mutex, NULL);

    // 创建线程
    // 在 C 和 C++ 中，函数指针的声明和使用都需要使用 (*) 这个语法。
    pthread_create(&thread1, NULL, incrementCounter, NULL);
    pthread_create(&thread2, NULL, incrementCounter, NULL);
    pthread_create(&thread3, NULL, incrementCounter, NULL);
    pthread_create(&thread4, NULL, incrementCounter, NULL);

    // 等待线程结束
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);

    // 销毁互斥锁
    pthread_mutex_destroy(&mutex);

    // 输出共享资源的值
    printf("Final sharedCounter value: %d\n", sharedCounter);

    return 0;
}
