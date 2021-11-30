#include <stdlib.h> 
#include <iostream>

//良好的设计，应该放到头文件里。这里只是演示
class Time{
private :
	int hours;
	int minutes;

public:
	Time(int h,int m=0):hours(h),minutes(m){};

	//提高效率避免拷贝对象，参数应该声明为&
	//但是返回值不能用引用，因为sum是一个局部变量。
	Time addTime(const Time &time)const{//两个const表示，函数不应该改变参数的值，不应该修改类成员
		Time sum(0);
		sum.minutes = minutes + time.minutes;
		sum.hours = hours + time.hours + sum.minutes /60;
		sum.minutes %= 60;
		return sum;
	}

	//运算符重载其实把`addTime` 换成`operator+` 就可以了
	Time operator+(const Time &time)const{
		return addTime(time);
	}

	void show()const{
		std::cout<<hours <<"h " <<minutes<<"m"<<std::endl;
	}
	/*
		重载<<, 实现show()函数同样的功能。
		如果直接重载，那么使用像这样：time<<cout, 很奇怪。希望的是 cout<<time。 
		但是又不能修改iostream 文件。因此必须使用 友元函数。
		返回值必须是ostream &，不能仅仅是ostream。因为如果返回ostream，会导致os对象拷贝。
	*/
	friend std::ostream & operator<<(std::ostream & os, const Time & t)//跟作为成员函数重载不同，非成员函数方式第一个参数是运算符左边，第二个参数是运算符右边
	{//添加了friend关键字，表明这个函数：1)不是Time类的成员； 2) 却与成员函数的访问权限相同
		//通常把函数体写在外面，不需要"Time::"修饰。
		os << t.hours << " hours, " << t.minutes << " minutes";
		return os;
	}

	//对于像Time * double 这样的操作，除了需要重载*实现Time * double之外，还应该通过友元的方式实现double * Time 。

	//重载单目运算符
	Time& operator ++();//前置运算符重载，后面的括号里无形参
	Time operator ++(int);//后置运算符重载，后面的括号里有形参，但是这个形参没用，只是表明后置。
	//如上，前置++是返回自身，所以返回类型是Time& 。后置是返回的不是自身，所以是Time

};
//已经在声明处实现了
//std::ostream & operator<<(std::ostream & os, const Time & t)
//{
//	os << t.hours << " hours, " << t.minutes << " minutes";
//	return os;
//}

Time& Time::operator ++(){//前置
	++minutes;
	if(minutes>=60){
		hours +=1;
		minutes -= 60;
	}
	return *this;
}
Time Time::operator ++(int){//后置
	Time old = *this;//产生拷贝
	++*this;//调用前置++自增。
	return old;
}

int main12(){
	Time a(3,10);
	Time b(2,5);

	//两种方法调用重载运算符
	Time c = a.operator+(b);//方法一。tag 1

	Time d = a + b;//方法二，左边a表示调用对象，右边b表示参数

	c.show();
	std::cout<<d<<std::endl;//重载了<<运算符。cout是第一个参数，d是第二个参数。相当于operator<<(std::cout, d)
	//cout<<d,d是Time类型，cout是ostream类型，ostream里面没有这个重载版本，所以不可能翻译成"cout.operator<<()",于是cout就成了第一个参数。
	operator<<(std::cout, d)<<std::endl;;//比较一下跟 tag 1 的区别

	std::cout<<(c++)<<std::endl;
	std::cout<<(++d)<<std::endl;

	system("pause");
	return 0;
}