#include <iostream>
#include <thread>  // std::thread
#include <mutex>  // std::mutex

std::mutex mtx;  // mutex for critical section
void print_block(int n, char c) {
// critical section (exclusive access to std::cout signaled by locking mtx):
    mtx.lock();
    for (int i = 0; i < n; ++i) {
        std::cout << c;
    }
    std::cout << '\n';
    mtx.unlock();
}

void print_block2(int n, char c) {
    std::cout << "before lock" << std::endl;
    mtx.lock();
    std::cout << "middle lock" << std::endl;
    mtx.lock();  // 会在这里停住，这说明std::mutex是不可重入锁
    std::cout << "after lock" << std::endl;
    for (int i = 0; i < n; ++i) {
        std::cout << c;
    }
    std::cout << '\n';
    mtx.unlock();
    mtx.unlock();
}
void print(char c) {
    mtx.lock();
    std::cout<<c<<std::endl;
    mtx.unlock();
}
void print_block3(int n, char c) {
    std::cout << "before lock" << std::endl;
    mtx.lock();
    for (int i = 0; i < n; ++i) {
        std::cout << "middle lock" << std::endl;
        print(c);
        std::cout << "after lock" << std::endl;
    }
    std::cout << '\n';
    mtx.unlock();
}
int main() {
    std::thread th1(print_block, 50, '*');//线程1：打印*
    std::thread th2(print_block, 50, '$');//线程2：打印$

    th1.join();
    th2.join();

    std::thread th3(print_block3, 50, '%');
    th3.join();
    return 0;
}