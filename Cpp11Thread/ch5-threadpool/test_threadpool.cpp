#ifndef _THREADPOOL_H
#define _THREADPOOL_H

#include <vector>
#include <queue>
#include <thread>
#include <iostream>
#include <condition_variable>

using namespace std;

const int MAX_THREADS = 100; //最大线程数目

template<typename T>
class ThreadPool {
public:
    ThreadPool(int number = 1);

    ~ThreadPool();

    bool append(T *task);

private:
    //工作线程需要运行的函数,不断的从任务队列中取出并执行
    static void *worker(void *arg);

    void run();

    //工作线程
    vector<thread> workThread;
    //任务队列
    queue<T *> taskQueue;
    mutex mt;
    condition_variable condition;
    bool stop;
};

template<typename T>
ThreadPool<T>::ThreadPool(int number) : stop(false) {
    if (number <= 0 || number > MAX_THREADS)
        throw exception();
    for (int i = 0; i < number; i++) {
        cout << "create thread：" << i << endl;
        workThread.emplace_back(worker, this);
    }
}

template<typename T>
inline ThreadPool<T>::~ThreadPool() {
    {
        unique_lock<mutex> unique(mt);
        stop = true;
    }
    condition.notify_all();
    for (auto &wt : workThread)
        wt.join();
    cout<<"~ThreadPool"<<endl;
}

template<typename T>
bool ThreadPool<T>::append(T *task) {
    // 如果已经stop，不再接受新的task，但是要保证已有的tasks执行完成
    if(stop) return false;
    //往任务队列添加任务的时候，要加锁，因为这是线程池，肯定有很多线程
    unique_lock<mutex> unique(mt);
    taskQueue.push(task);
    unique.unlock();
    //任务添加完之后，通知阻塞线程过来消费任务，有点像生产消费者模型
    condition.notify_one();
    return true;
}

template<typename T>
void *ThreadPool<T>::worker(void *arg) {
    ThreadPool *pool = (ThreadPool *) arg;
    pool->run();
    return pool;
}

template<typename T>
void ThreadPool<T>::run() {
    while (true) {
        unique_lock<mutex> unique(this->mt);
        //如果任务队列为空，就停下来等待唤醒，等待另一个线程发来的唤醒请求
        while (this->taskQueue.empty()) {
            if (stop) return; //unique可以自动释放
            this->condition.wait(unique);
        }
        T *task = this->taskQueue.front();
        this->taskQueue.pop();
        unique.unlock();
        if (task)
            task();
    }
}

#endif

int main() {
    ThreadPool<void()> threadPool(5);
    threadPool.append([]() {
        // 测试发现cout输出会乱序，故改成printf
//        std::cout << "\nhello, thread id="<<std::this_thread::get_id() << endl;
        printf("hello, thread id=%d \n", std::this_thread::get_id());
    });
    threadPool.append([]() {
        printf("hello, thread id=%d \n", std::this_thread::get_id());
    });
    threadPool.append([]() {
        printf("hello, thread id=%d \n", std::this_thread::get_id());
    });
}
