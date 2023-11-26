#include <iostream>
#include <thread>
#include <atomic>
#include <time.h>
#include <mutex>

using namespace std;

/**
 * 我们将一个数加一再减一，循环一定的次数，开启20个线程来观察，这个正确的结果应该是等于0的。
 * 1. 不加锁也不用原子变量，会得到错误结果
 * 2. 加锁
 * 3. 使用atomic_int
 * 分别实现这3种，并计算运行时间，比较性能差距
 */
#define MAX 100000
#define THREAD_COUNT 20
int total = 0;

//-------不加锁也不用原子变量
void thread_task() {
    for (int i = 0; i < MAX; i++) {
//        total += 1;
//        total -= 1;
        //有人说++i是原子操作，经验证并非如此
        ++total;
        --total;
    }
}

int no_mutex() {
    total = 0;
    clock_t start = clock();
    thread t[THREAD_COUNT];
    for (int i = 0; i < THREAD_COUNT; ++i) {
        t[i] = thread(thread_task);
    }
    for (int i = 0; i < THREAD_COUNT; ++i) {
        t[i].join();
    }
    clock_t finish = clock();
    cout << "no_mutex, result: " << total << " duration: " << (finish - start)*1000/CLOCKS_PER_SEC << "ms" << endl;
    return 0;
}
//不加锁也不用原子变量------END

//-------加锁
mutex mt;

void thread_task2() {
    for (int i = 0; i < MAX; i++) {
        mt.lock();
        total += 1;
        total -= 1;
        mt.unlock();
    }
}

int use_mutex() {
    total = 0;
    clock_t start = clock();
    thread t[THREAD_COUNT];
    for (int i = 0; i < THREAD_COUNT; ++i) {
        t[i] = thread(thread_task2);
    }
    for (int i = 0; i < THREAD_COUNT; ++i) {
        t[i].join();
    }
    clock_t finish = clock();
    cout << "use_mutex, result: " << total << " duration: " << (finish - start)*1000/CLOCKS_PER_SEC << "ms" << endl;
    return 0;
}
//加锁------END

//-------使用atomic_int
atomic_int total_a(0);//atomic_int是atomic<int>的别名

void thread_task3() {
    for (int i = 0; i < MAX; i++) {
        total_a += 1;
        total_a -= 1;
    }
}

int use_atomic() {
    total = 0;
    clock_t start = clock();
    thread t[THREAD_COUNT];
    for (int i = 0; i < THREAD_COUNT; ++i) {
        t[i] = thread(thread_task3);
    }
    for (int i = 0; i < THREAD_COUNT; ++i) {
        t[i].join();
    }
    clock_t finish = clock();
    cout << "use_atomic, result: " << total << " duration: " << (finish - start)*1000/CLOCKS_PER_SEC << "ms" << endl;
    return 0;
}
//使用atomic_int------END

int main() {
    no_mutex();
    use_mutex();
    use_atomic();
    /*
     * one time result:
     * no_mutex, result: -108 duration: 55ms
     * use_mutex, result: 0 duration: 2011ms
     * use_atomic, result: 0 duration: 612ms
     */
    return 0;
}
