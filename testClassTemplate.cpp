#include <iostream>
#include <string>
using namespace std;

#ifndef STACKTP_H
#define STACKTP_H

//模板不是类和成员的定义，而是“如何生成类和成员”的定义，不能单独编译，必须与特定的模板实例化一起使用。
//基本用法
template <typename T>//or template <class T>
class Stack{
private:
	enum {MAX = 10};
	T item[MAX];
	int top;
public:
	Stack();
	bool isEmpty();
};

template <typename T>
Stack<T>::Stack(){
	top = 0;
}
template <typename T>
bool Stack<T>::isEmpty(){
	return top == 0;
}

//模板参数
template <typename T, int maxsize = 100>//default maxsize is 100
class Array{
private:
	T item[maxsize];
	int top;
public:
	int maxSize();
};

template <typename T,int maxsize>
int Array<T,maxsize>::maxSize(){
	return maxsize;
}


#endif

int main(){
	//T是string
	Stack<std::string> stackStr;//函数模板可以根据参数由编译器隐式的推导出类型。但是类模板必须显式指定类型，比如这里是std::string
	cout<<stackStr.isEmpty()<<endl;

	//T是指针
	Stack<int*> stackInt;
	cout<<stackInt.isEmpty()<<endl;

	//T还可以是数组，但需要对Stack类做合理的设计，让他的逻辑支持T是数组
	Stack<int[5]> stackIntArr;
	cout<<stackIntArr.isEmpty()<<endl;

	//T代表的类型甚至可以嵌套模板类自身
	Stack<Stack<int>> stackIntStack;
	cout<<stackIntStack.isEmpty()<<endl;

	//通过模板参数，指定Array的最大容量
	Array<int> arr;//maxsize使用默认值(100)
	cout<<arr.maxSize()<<endl;
	Array<int,15> arr2;//maxsize=15
	cout<<arr2.maxSize()<<endl;

}