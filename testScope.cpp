#include <iostream>
#include "coordin.h"
#include "coordin.h"//通过#ifndef指令忽略第二次包含的内容


//wrong : auto不能用在这里 ：auto int y;

void autoVariable(){
	//自动变量放在内存堆栈中（或者CPU寄存器）
	using namespace std;
	auto int x;//same as int x;auto几乎不会使用，如果使用，只是为了向读者澄清含义

	register int y;//寄存器变量没有地址
	int* py = &y;//所以编译器实际没有使用寄存器来存储该变量
	cout<<py<<endl;
}

int i = 0;
//---------静态持续变量默认都是0
//只能使用常量表达式来初始化
int global = 1000;//静态存储，外部链接，即：可以在其它文件中使用。其它文件用extern声明一下就可以使用
static int global_thisfile = 1200;//静态存储，内部链接，即：只在此文件中使用
const int global2 = 44;//等价于const static int global2 = 44;即加了const，就是内部链接，只本文件可用
extern const int global3 = 54;//用extern显式指定为外部链接，然后在其它文件先用external声明

extern int global4 = 46;//这是定义，所有文件中不能重复出现定义
extern int global5;//这是声明

void staticVariable(){
	using namespace std;
	//只在此代码块可用，但在整个程序执行周期都存在。
	static int static_in_func = 2;//静态存储，无链接性。只初始化一次
	static_in_func++;
	if(i++<3){
		cout<<"static_in_func "<<static_in_func<<endl;
		staticVariable();//虽然反复调用，但是static_in_func不会反复初始化
	}
}

void staticVariable2(){
	using namespace std;

	//当变量名重名时，局部变量优先于静态变量、内部链接的优先于外部变量的。即：范围小的优先级更高
	cout<<"外部 "<<global<<endl;
	int global = 1001;
	cout<<"局部优先 "<<global<<endl;
	cout<<"访问被隐藏的外部变量 "<<::global<<endl;//使用全局名称空间下的global变量

	cout<<"外部2 "<<global4<<endl;

	const int state = 100;//作用域为代码块
}
//----------------END

//testScope2.cpp中也定义了onlyThisFile(),但是优先使用本文件中的static函数
static void onlyThisFile();


//---------语言的链接性(Language linking)
//背景知识：C语言编译器可能将函数翻译为_spiff
//C++支持重载，故需要翻译为：_spiff_i
//链接程序寻找函数时，C和C++是不一样的。那么如果C++程序中使用C库中预编译的函数，将会找不到
extern "C"void spiff(int);//这种情况下，指定extern "C",使用C语言链接性
extern "C++"void spot(int);//指定C++语言链接。

//-----END




int main_scope(){
	autoVariable();
	staticVariable();
	staticVariable2();

	//先声明
	extern void printV();
	printV();

	onlyThisFile();


	void testplacementNew();//声明
	testplacementNew();
	return 0;
}

//------通过static将函数链接性设置为内部，否则函数默认都是外部的
static void onlyThisFile(){
	using namespace std;
	cout<<"Can only call in this file"<<endl;
}

//指定位置构造对象。可以在栈上，也可以在堆上
#include<new>
void testplacementNew(){
	using namespace std;
	char buffer[10];
	char * pbuf = new (buffer)char;//在buffer的位置生成对象。
	//地址应该一样
	cout<<"pbuf的地址："<<(void*)pbuf<<",buffer的首地址："<<(void*)buffer<<endl;//转成void*是为了cout打出地址而不是字符串

	pbuf = new ((int*)buffer+1)char;////在地址buffer+sizeof(int)的位置生成对象。
	cout<<"pbuf的地址："<<(void*)pbuf<<endl;
	//不需要使用delete释放，而且也不能这样做


}