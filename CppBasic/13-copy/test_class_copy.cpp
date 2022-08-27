
#include <iostream>
using namespace std;

/**
 * 主要是拷贝构造函数，和赋值运算符重载函数会影响类对象的复制
 * 如果不手动提供，编译器自动提供默认的，默认行为是按位拷贝
 */
class Date {
public:
    //1. 无参构造函数
    Date(){
        cout<<"无参构造"<<endl;
    }
    //2. 带参数的构造函数
    Date(int year, int month, int day){
        cout<<"带参构造"<<endl;
        this->year = year;
        this->month = month;
        this->day = day;
    }

    Date(const Date& d){
        cout<<"拷贝构造函数"<<endl;
        this->year = d.year;
        this->month = d.month;
        this->day = d.day;
    }
    Date& operator=(Date& d){
        cout<<"重载等号"<<endl;

    }

    int year;
    int month;
    int day;
};

void main_test_class_copy(){
    //调用构造函数
    Date d1(2022, 1, 1);

    //调用拷贝构造函数
    Date d2(d1);
    cout<<d2.year<<endl;

    //也是调用拷贝构造函数。不要看到等号就认为是调用operator=。这里从无到有创建了d3对象，显然必须调用某个构造函数。而operator=不是构造函数，是已经有对象后的赋值。
    //当等号左边有新对象定义出现时，调用拷贝构造函数；当等号左边的对象是已经存在的实例，则调用拷贝操作符’=’。
    Date d3 = d1;

    //调用operator=
    d3 = d1;
    //-----个人觉得，operator=和拷贝构造函数应该保持一样，即Date d3 = d1;和"Date d3;d3 = d1;"最终d3应该是一样的。
}