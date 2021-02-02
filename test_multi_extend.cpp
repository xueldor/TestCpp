/************************************************************************/
/* 演示一下多重继承、二义性问题                                         */
/************************************************************************/
#include <iostream>
using namespace std;

class Base{
protected:
	long id;
public:
	Base(long i=0):id(i){};

	//只要显式提供了构造函数(不管无参还是有参)，就必须提供virtual的析构函数。否则vs上面报Stack around the variable 'XXX' was corrupted。
	//原因未知，也无法理解。linux上面用g++编译是没这个问题的。
	virtual ~Base(){}
};
class A:public Base{

};
class B: public Base{

};

class C :A,B{//class默认是private继承,struct则默认public
public:
	void printId(){
		//C里面有两个id，分别从A/B继承过来,所以不指定域的话，编译器不知道访问的是哪一个。
		A::id = 1;
		B::id = 2;
		//把继承关系用图画出来是一个菱形。这个继承关系还算比较简单，如果更复杂，用图可以直观的看出来：如何访问有二义性，如何访问没有二义性。
		cout<<A::id<<endl;//A中的id
		cout<<B::id<<endl;//B中的id

		//cout<<id<<endl;//二义性
		//cout<<Base::id<<endl;//理论上这样也是有二义性的。尽管vs用的A::id

	}
};
//虚基类的含义是，沿着所有路径，以"虚" 的方式继承的Base类共享一个，而不是多个，这样就避免了二义性的问题。
class VA:virtual public Base{

};

class VB:public virtual Base{

};

//由于VA、VB都是virtual继承Base，所以他们的Base的同一个，而B不是virtual，所以VC中有两个Base
class VC:public VA,VB,B{//VA是公有继承，VB是私有继承
public:
	void printId(){
		VA::id = 1;
		B::id = 4;
		cout<<VA::id<< "  same as " << VB::id<<endl;
		cout<<B::id<<endl;
		VB::id = 2;
		cout<<VA::id<< "  same as " << VB::id<<endl;
	}
};

int main14(){
	C c;
	c.printId();


	//Base * base = &c;//二义性,因为c中有两个Base，所以你要先转成B或A
	Base *baseA = (A*)&c;
	Base*baseB = (B*)&c;

	cout<<"--------"<<endl;

	VC vc;
	vc.printId();
	return 0;
}