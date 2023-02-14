#include <iostream>

using namespace std;

namespace f6 {

    template<typename T>
    void g(T &) {
        cout << "T&" << endl;
    }

    template<typename T>
    void g(T &&) {
        cout << "T&&" << endl;
    }

    template<typename T>
    void f(T &&a) {
        g(a);//始终调用的g(T &)
        g(std::move(a));//始终调用的g(T &&)
        //如果参数引用的是左值，就调用g(T &)；右值就调用g(T &&)；称为完美转发
        g(std::forward<T>(a));
    }

    void main() {
        int a;
        f(0);//g(std::forward<T>(a));调的是g(T &&)
        cout<<"---分隔"<<endl;
        f(a);//g(std::forward<T>(a));调的是g(T &)
    }
}