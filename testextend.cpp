#include <iostream>
using namespace std;

class A{
public :
	A(){}
	A(int a){}
	void show(){cout<<"A show"<<endl;}
	virtual void show(int a){cout<<"virtual A show a"<<endl;}
	virtual void show(int a,int b){cout<<"virtual A show a b"<<endl;}
	void show(int a,int b,int c){cout<<"A show a b c"<<endl;}

	void tostring(){cout<<"A tostring"<<endl;}

	virtual void print(){cout<<"B print"<<endl;}

	A* get(){return this;}

	/*
	析构函数必须声明为virtual，因为，
	假设有 A* a = new B;
	如果不是virtual，那么delete a, 会只调用A的析构函数。B中分配的资源无法释放。
	而如果是virtual，delete a，会先调用 ~B(), 再调用 ~A()
	*/
	virtual ~A(){}
};
class B:public A{
public :
	//子类的构造函数总是要调用父类的构造函数。默认调用父类的无参构造函数
	B(int a,int b){}
	//通过成员初始化列表调用父类构造函数
	B(int a):A(a){}
	B():A(1){}

	void show(){cout<<"B show"<<endl;}
	virtual void show(int a){cout<<"virtual B show a"<<endl;}

	//因为父类中声明为virtual，故在子类里，自动是virtual
	void print(){cout<<"B print"<<endl;}

	//参数完全与父类相同，只是返回类型不同。称为返回类型协变。
	B* get(){return this;}
};

class C{
public:
	virtual int c()=0;//纯虚函数，类似java的abstract 或接口
};

int main_extend(){
	A a;
	B b;
	a.show();//声明类型和对象类型是A，所以调用A的方法。
	b.show();//声明类型和对象类型是B，所以调用B的方法。

	A *ap = &b;
	//指针的类型是A,而实际类型是B，要看方法是不是virtual的
	ap->show();//非virtual，静态联编，调用指针类型的方法
	ap->show(1);//virtual，动态联编，调用对象真实类型的方法

	//方法的隐藏。只要B实现了某个方法，父类里的所有同名重载方法都被隐藏。通过父类的引用可以调用，通过子类调用则编译报错。
	ap->show(1,2);//对象是B 类型，但是A可以调用。
	/*b.show(1,2);//实现在A中，B没有实现，被隐藏，B不能调用
	b.show(1,2,3);*/
	ap->show(1,2,3);//实现在A中，对B隐藏，但是可以通过A调用


	b.print();
	b.tostring();//tostring实现在A中，B继承过来。B中没有实现同名的tostring方法，所以不会隐藏

	/************************************************************************/
	/** 以上测试告诉我们：
		假设父类有一个函数show,并有若干个重载版本，那么在子类里面：
	    1. 要么不要实现show函数，继承父类的。	
		2. 只要实现了show函数，就要实现这个函数的所有重载函数。否则没有实现的函数会对子类隐藏。
		3. 子类重写父类方法，必须保证参数和方法名完全一致。返回类型可以不同。
	  
	*/
	/************************************************************************/


	cout<<"---------分隔 1 ---------"<<endl;
	b.show();
	b.A::show();

	b.show(1);
	b.A::show(1);
	//以上，演示了如何调用父类的函数。
	return 0;

}