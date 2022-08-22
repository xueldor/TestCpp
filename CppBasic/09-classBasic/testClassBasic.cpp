#include <iostream>
using namespace std;

/**
 * 1. 新的C++标准可以在成员变量声明时给赋值
 * 2. const变量如果声明时没有给初始值，就必须在构造函数的初始化列表里对它初始化。这种设计是很好理解的。
 * 3. static 成员变量不能在类的内部初始化，必须放到类外面（见tag 1）。而且，请不要把初始化放头文件，否则会引起重复定义这样的错误。即使加上#ifndef #define #endif或者#pragma once也不行。
 * 4. const static不能赋值（除了const static int是个例外）
 *
 * 之所以const static int有这种特权，是为了设计一个更明确（类型）的常量定义语法来取代用enum定义常量的旧方式。因为出发点是这个，所以才仅仅只是对静态整形常量特殊处理，因为enum也只能是整型值。
 */
class Basic{
private:
    int num ;//right
    int num2 = 2 ;//C++ 03不支持，VS2008报错，较新一点的g++可能会提示你加上'-std=c++11'参数
    const int c ;//必须通过构造函数初始化列表进行初始化
    const int c2 = 2;
public :
    const static int d = 4;//OK.只有const static int可以
//    const static float l2 = 9;//不OK，只有const static int可以初始化
    constexpr static float l3 = 9;//OK，新标准(C++11)。对于"a=b"这样的预计，加const表示表示a是常量，即a不能被修改；加constexpr表示等号后面的b是一个常量表达式
    const static float l ;//要在类外面初始化，见tag 2

    static int accu;//要在类外面初始化，见tag 1
//    static int accu2 = 3;//wrong，标准C++不允许在类的内部初始化,应把初始化放外面

    enum AA{ aa1 = 2, aa2 =3,aa3,aa4};
    static const AA a = aa1;//OK

    Basic():c(1){
        cout<<"num没有初始化,l="<<l<<endl;
    }
    Basic(int n):num(n),c(1){}

    void printNum(){
        cout<<"num="<<num<<endl;
    }
    void setNum(int n){num = n;}

	 ~Basic(){}
};
int Basic::accu = 4;//初始化static，不带static关键字,tag 1
const float Basic::l = 3;//初始化const static，同样不带static关键字，带上要带const,tag 2

int main_basic_class(){
    Basic basic1;
    basic1.printNum();
    basic1.setNum(3);
    Basic basic2(8);

    Basic::accu = 4;//修改值。必须要先在tag 1处初始化
    cout<<Basic::l<<endl;
	return 0;

}