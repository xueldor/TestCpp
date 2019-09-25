﻿#include <iostream>
using namespace std;

void initArray(){
	int yams[3];//先声明
//报错,未初始化：cout<<yams[0]<<endl;

	yams[0] = 1;//再赋值
	yams[1] = 2;
	yams[2] = 3;

	int yam2[10] = {4,5,6};//创建和初始化，ANSI C之前的版本不支持这样写
	cout<<yam2[2]<<"  "<<yam2[3]<<endl;//yam2包含10个元素，只初始化了3个，后面的默认全是0

	int yam2_1[10] = {1};//第一个设置为1，其他全是0
	cout<<yam2_1[0]<<"  "<<yam2_1[1]<<endl;


	int yam3[] = {7,8,9};//编译器计算元素个数
	cout<<yam3<<endl;//输出yam3的地址，也就是指向第一个元素的指针

	const int yam4[] = {0};//数组名本质是常量指针。前面再加const表示数组中每个元素都是常量
//wrong:不能给常量赋值	yam4[0] = 2;
//wrong,const不能赋给变量	int* yam4_1 = yam4;

	const int* const yam5 = yam3;
	cout<<"yam5 and yam3指向同一个地方："<<yam5+1<<"  "<<yam3+1<<endl;
//	yam5[1] = 2;//但是声明yam5时使用const修饰，所以不能通过yam5修改数组内容
	yam3[1] = 3;//仍然可以通过yam4修改
}

void testCStyleString(){//C风格的字符串
	char dog[5] = {'a','d','o','g','\0'};//如果没有\0，将在内存中一直向后读，直到发现\0为止
	cout<<dog<<endl;

	//更简便的方法
	char cat[] = "I am cat";//编译器自动补\0

	//字符串常量自动拼接
	cout<<"I""CAT"<<endl;
	cout<<"I" "CAT"<<endl;
	cout<<"I"
		"CAT"<<endl;

	char name[20];
	cin>>name;//只能读一个单词；有超出数组大小的风险
	cout<<name<<endl;

	cin.get();//跳过前一行代码最后的回车
	cin.get(name,10);//从输入缓冲区读9个字符，放入name，并补\0
	cout<<name<<endl;
}

void initMulArr(){
	int temps[2][3] = {
		{1,2,3},
		{2,3,4}
	};

	int* p1[2];//指针数组
	int (*p)[2];//指向数组的指针

	//二维数组即数组的数组，temps[0]就是int*,所以可以赋值给p1[0]
	p1[0] = temps[0] + 1;//temps[0] + 1就是temps[0][1]的地址
	cout<<*p1[0]<<endl;//输出2


	
}


int main3(){
	initArray();

	testCStyleString();
	initMulArr();

	return 0;
}