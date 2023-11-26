#include <iostream>           // std::cout
#include <thread>             // std::thread, std::this_thread::yield
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable

std::mutex mtx;
std::condition_variable cv;
int value = 0; // 假设在子线程上获取value,并在主线程等待获取到value

void getValue() {
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::unique_lock<std::mutex> lck(mtx);
    std::cout<<"before get value"<<std::endl;
    value = 5;
    std::cout<<"get value"<<std::endl;
    cv.notify_one();
}

int main() {
    value =  0;
    std::thread get_value_thread(getValue);

    while (value == 0) std::this_thread::yield(); // 主线程让出时间片，子线程执行
    std::unique_lock<std::mutex> lck(mtx);//自动上锁
    //第二个参数为false才阻塞（wait），阻塞完即unlock，给其它线程资源
    std::cout<<"before wait"<<std::endl;
    cv.wait(lck, []{
        return value != 0;
    });
    std::cout<<"after wait, got value="<<value<<std::endl;

    get_value_thread.join();
    return 0;
}
