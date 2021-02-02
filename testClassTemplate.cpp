#include <iostream>
#include <string>
using namespace std;

#ifndef STACKTP_H
#define STACKTP_H

//ģ�岻����ͳ�Ա�Ķ��壬���ǡ����������ͳ�Ա���Ķ��壬���ܵ������룬�������ض���ģ��ʵ����һ��ʹ�á�
//�����÷�
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

//ģ�����
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
	//T��string
	Stack<std::string> stackStr;//����ģ����Ը��ݲ����ɱ�������ʽ���Ƶ������͡�������ģ�������ʽָ�����ͣ�����������std::string
	cout<<stackStr.isEmpty()<<endl;

	//T��ָ��
	Stack<int*> stackInt;
	cout<<stackInt.isEmpty()<<endl;

	//T�����������飬����Ҫ��Stack�����������ƣ��������߼�֧��T������
	Stack<int[5]> stackIntArr;
	cout<<stackIntArr.isEmpty()<<endl;

	//T�����������������Ƕ��ģ��������
	Stack<Stack<int>> stackIntStack;
	cout<<stackIntStack.isEmpty()<<endl;

	//ͨ��ģ�������ָ��Array���������
	Array<int> arr;//maxsizeʹ��Ĭ��ֵ(100)
	cout<<arr.maxSize()<<endl;
	Array<int,15> arr2;//maxsize=15
	cout<<arr2.maxSize()<<endl;

}