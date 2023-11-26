#include <iostream>
#include <thread>  // std::thread
#include <mutex>  // std::mutex

int g_i = 0;
std::mutex g_i_mutex;

// test lock_guard
void safe_increment() {
    const std::lock_guard<std::mutex> lock(g_i_mutex);
    ++g_i;
    std::cout << std::this_thread::get_id() << ": " << g_i << '\n';
    // g_i_mutex自动解锁
}

// test unique_lock
struct Box {
    explicit Box(int num) : num_things{num} {}

    int num_things;
    std::mutex m;
};
void transfer(Box &from, Box &to, int num) {
    // defer_lock表示暂时unlock，默认自动加锁
    std::unique_lock<std::mutex> lock1(from.m, std::defer_lock);
    std::unique_lock<std::mutex> lock2(to.m, std::defer_lock);

    //两个同时加锁
    std::lock(lock1, lock2);//或者使用lock1.lock()

    from.num_things -= num;
    to.num_things += num;
    //作用域结束自动解锁,也可以使用lock1.unlock()手动解锁
}

int main() {
    std::cout << "main id: " << std::this_thread::get_id() << std::endl;
    std::cout << "main: " << g_i << '\n';

    std::thread t1(safe_increment);
    std::thread t2(safe_increment);

    t1.join();
    t2.join();

    std::cout << "main: " << g_i << '\n';


    // unique_lock
    {
        Box acc1(100);
        Box acc2(50);
        std::thread t1(transfer, std::ref(acc1), std::ref(acc2), 10);
        std::thread t2(transfer, std::ref(acc2), std::ref(acc1), 5);
        t1.join();
        t2.join();
        std::cout << "acc1 num_things: " << acc1.num_things << std::endl;
        std::cout << "acc2 num_things: " << acc2.num_things << std::endl;
    }

    return 0;
}