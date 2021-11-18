#include <iostream>
using namespace std;

class Basic{
private:
    int num ;//right
    int num2 = 2 ;//C++ 03不支持，VS2008报错，最新g++提示你加上'-std=c++11'参数
//    const int c ;//wrong
    const static int d = 4;//OK
    const static float l = 9;//不OK，float和double不属于整形。VS2008报错
    const static double m = 9;//但是最新的g++通过
public :
    static int accu;
//    static int accu2 = 3;//wrong，标准C++不允许不能初始化,应把初始化放外面

    enum AA{ aa1 = 2, aa2 =3,aa3,aa4};
    static const AA a = aa1;//OK

    Basic(){
        cout<<"num没有初始化,l="<<l<<endl;
    }
    Basic(int n):num(n){}

    void printNum(){
        cout<<"num="<<num<<endl;
    }
    void setNum(int n){num = n;}

	 ~Basic(){}
};
int Basic::accu = 4;//初始化,tag 1
int main_basic_class(){
    Basic basic1;
    basic1.printNum();
    basic1.setNum(3);
    Basic basic2(8);

    Basic::accu = 4;//修改值。必须要先在tag 1处初始化
	return 0;

}