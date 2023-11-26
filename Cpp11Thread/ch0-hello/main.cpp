#include <iostream>
#include <thread>
#include <sys/syscall.h>
#include <zconf.h>

pid_t gettid() {
    return syscall(SYS_gettid);
}

void thread_fun() {
    std::cout << "thread_fun " << gettid() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void thread_fun_x(int x) {
    std::cout << "thread_fun_x " << x << "  " << gettid() << std::endl;
    if (x > 0) {
        std::thread myThread(thread_fun_x, x - 1);
        myThread.detach();
    }
}

int main() {
    std::cout << "Hello, Thread! " << gettid() << std::endl;
    std::thread myThread(thread_fun); //线程是这里立即执行的
    std::cout << "finish" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    myThread.join(); // 尝试注释掉，哪怕前面sleep了，仍然报 terminate called without an active exception

    std::thread myThread2(thread_fun_x, 5);
    myThread2.join();
    std::cout << "return" << std::endl;
    return 0;
}
