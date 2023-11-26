#include<iostream>
#include<thread>

#include<future>

using namespace std;

int mythread() { //线程入口函数
    cout << "mythread start" << "threadid= " << std::this_thread::get_id() << endl; //打印线程id

    std::chrono::milliseconds dura(5000); //定一个5秒的时间
    std::this_thread::sleep_for(dura);  //休息一定时常

    cout << "mythread end" << "threadid= " << std::this_thread::get_id() << endl; //打印线程id

    return 5;
}

int main() {
    cout << "main" << "threadid= " << std::this_thread::get_id() << endl;
    std::future<int> result = std::async(std::launch::deferred,mythread);//流程并不卡在这里
    cout << "continue....." << endl;

    // block
    // wait_for会暂停等一段时间。不影响其它，也不是一定要调用，就是单纯阻塞。wait_for结束时，如果子线程已经结束，返回status为ready；如果没结束，返回status为超时。
    // 但是不影响什么，即使返回的是超时，result.get()还是会阻塞到子线程返回，和wait_for没关系。
    std::future_status status = result.wait_for(std::chrono::seconds(3));//等待一秒
    cout << "after wait....." << endl;

    if (status == std::future_status::deferred) {
        //线程被延迟执行了，系统资源紧张
        cout << result.get() << endl; //此时采取调用mythread()
    } else if (status == std::future_status::timeout) {
        //超时：表示线程还没执行完；我想等待你1秒，希望你返回，你没有返回，那么 status = timeout
        //线程还没执行完
        cout << "超时：表示线程还没执行完!"<<endl;
        cout << result.get() << endl;
    } else if (status == std::future_status::ready) {
        //表示线程成功返回
        cout << "线程成功执行完毕，返回!" << endl;
        cout << result.get() << endl;
    }
    cout << "I love China!" << endl;
    return 0;
}