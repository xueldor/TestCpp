#include <iostream>
#include <functional>

using namespace std;

namespace f7 {

    void doActionA() {
        int list1[10] = {1,2,3,4,5,6,7,8,9,10};
        int list2[10] = {11,12,12,14,15,16,17,18,19,20};

        for (int i = 0; i < 10; i++) {
            cout<<list1[i]<<"\t";
        }
        cout<<endl;
        for (int i = 0; i < 10; i++) {
            cout<<list2[i]<<";";
        }
        cout<<endl;
    }

    void foreach(int arr[], int size, void (*fun)(int)){
        for (int i = 0; i < size; i++) {
            fun(arr[i]);
        }
        cout<<endl;
    }
    void log1(int val) {
        cout<<val<<"\t";
    }
    void log2(int val) {
        cout<<val<<";";
    }
    void doActionB() {
        int list1[10] = {1,2,3,4,5,6,7,8,9,10};
        int list2[10] = {11,12,12,14,15,16,17,18,19,20};

        foreach(list1, 10 ,log1);
        foreach(list2, 10 ,log2);

    }

    void foreach2(int arr[], int size, std::function<void(int)> fun){
        for (int i = 0; i < size; i++) {
            fun(arr[i]);
        }
        cout<<endl;
    }
    using Callback = std::function<void(int)>;
    void foreach3(int arr[], int size, Callback fun){
        for (int i = 0; i < size; i++) {
            fun(arr[i]);
        }
        cout<<endl;
    }
    void doActionC() {
        int list1[10] = {1,2,3,4,5,6,7,8,9,10};
        int list2[10] = {11,12,12,14,15,16,17,18,19,20};

        foreach(list1, 10 ,[](int a){
            cout<<a<<"\t";
        });
        char separator = ';';
        foreach(list2, 10 ,[](int a){
            cout<<a<<";";
        });

    }
    void doActionD() {
        int list1[10] = {1,2,3,4,5,6,7,8,9,10};
        int list2[10] = {11,12,12,14,15,16,17,18,19,20};

        char separator;

        auto log = [&separator](int a){
            cout<<a<<separator;
        };

        separator = '\t';
        foreach2(list1, 10 , log);

        separator = ',';
        foreach2(list2, 10 ,log);

    }
    void doActionE() {
        int list1[10] = {1,2,3,4,5,6,7,8,9,10};
        int list2[10] = {11,12,12,14,15,16,17,18,19,20};

        char separator;

        Callback log = [&separator](int a){//知道类型名是Callback，而且很简洁，也就不必使用auto
            cout<<a<<separator;
        };

        separator = '\t';
        foreach3(list1, 10 , log);

        separator = ',';
        foreach3(list2, 10 ,log);

    }
    void doActionF() {
        int list1[10] = {1,2,3,4,5,6,7,8,9,10};
        int list2[10] = {11,12,12,14,15,16,17,18,19,20};

        //这里我不捕获separator了，而是作为lambda的参数
        auto log = [](int a, char separator){
            cout<<a<<separator;
        };

        //log有两个参数，显然不能直接传给foreach3，需要用std::bind变成一个参数
        Callback call = std::bind(log, std::placeholders::_1, '\t');
        foreach3(list1, 10 , call);

        Callback call2 = std::bind(log, std::placeholders::_1, ',');
        foreach3(list2, 10 ,call2);
    }
    Callback testScope() {
        char separator = ',';

        Callback log = [&separator](int a){//按引用捕获，separator是局部变量，虽然被捕获，但是执行这个lambda时已经释放
            cout<<a<<separator;
        };

        return log;
    }

    double my_divide(double x, double y) { return x/y; }

    void main() {
//        auto fn_half = std::bind(my_divide,std::placeholders::_1,2);
//        std::cout << fn_half(10) << '\n';                        // 5

//        doActionA();
//        doActionB();
//        doActionC();
//        doActionD();
//        doActionE();
//        doActionF();
        Callback log = testScope();
        log(3);
        cout<<"这里插入一行"<<endl;
        log(3);//separator应该释放掉了
    }
}