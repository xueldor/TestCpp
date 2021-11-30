#include <iostream>
#include <string>

using namespace std;

void teststring(){
	string str1;
	string str2 = "Tom";
	str1 = str2;//数组不能赋值，string对象可以，因为C++中对象和结构可以直接赋值，内存中的对象会拷贝一份
	cout<<str1<<endl;

	str2+=" is stupid";//拼接
	cout<<str2<<endl;

	char hungry[] = " hungry boy";
	str1 += hungry;//与C风格字符串拼接
	cout<<str1<<endl;

	str1 = hungry;//C风格字符串赋值给string对象
	cout<<str1<<endl;

	const char* tom = str2.c_str();//string转C风格字符串
	cout<<tom<<endl;



}


int main4(){
	teststring();

	return 0;
}