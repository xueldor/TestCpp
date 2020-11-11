#include <iostream>
#include <string>
using namespace std;


void testFunc1(int arr[],int n){
	//arr[]作为形参，其实是指针，也可写作int* arr。C++不支持数组直接赋值，所以调用时是将地址传给arr，显然arr是指针
	cout<<"testFunc1 "<<arr<<" sizeof arr : "<<sizeof arr<<",sizeof *arr:  "<<sizeof *arr<<endl;//指针的大小,int类型的大小

}

//arr其实是指针，指向int[10][10]类型的数据，所以第一个方括号中的数字其实无效，可以写成arr[][10][10]
void testFunc2(int arr[5][10][10],int n){
	//*arr是int arr[10][10]，所以sizeof *arr是4*10*10
	cout<<"testFunc2 sizeof arr : "<<sizeof arr<<",sizeof *arr:  "<<sizeof *arr<<endl;//指针的大小，int arr[10][10]的大小
}

void testFunc3(int (*arr)[5],int n){//或者写成arr[][5]。注意int (*arr)[5]中的括号
	cout<<"testFunc2 sizeof arr : "<<sizeof arr<<",sizeof *arr:  "<<sizeof *arr<<endl;//指针的大小，int arr[10][10]的大小
}

void testFunPoint(int a){
	cout<<"test function pointer "<<a<<endl;

}

int retA(){
	//a作为局部变量，函数返回后就会释放。a的值在返回时复制到临时存储区域
	int a = 90;
	cout<<"函数中的变量的地址:"<<&a<<endl;
	return a;
}
int& retB(){
	//返回类型是int&，直接返回a的引用。因为a是局部变量，所以这样写后果是无法预期的
	int a = 90;
	cout<<"函数中的变量的地址:"<<&a<<endl;
	return a;//编译器警告：返回局部变量或临时变量的地址
}

//引用作为函数参数,使得函数直接使用原始数据
void swap(int &a,int &b){
	int temp = a;
	a = b;
	b = temp;
	
}
//函数通过指针访问原始数据
void swap2(int *a,int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
	
}

void cube(const int&a){
	cout<<a<<endl;
}

/**
 * 1、默认值必须从右到左
 * 2、必须通过函数原型
 */
int harpo(int n,int m,int j = 5);

//函数声明
template<typename AnyType>
void Swaptemplate(AnyType &a,AnyType &b);

template void Swaptemplate<int>(int&,int&);//tag1,template后面没有<>,表示显式实例化，后面不需要函数定义，编译器自己生成。区别于显式具体化

//---------声明
template<typename AnyType>
void Swaptemplate(AnyType a[],AnyType b[],int n);

template<> void Swaptemplate(int a[],int b[],int n);//tag2,显式具体化,后面需要自己根据此声明定义函数的实现。同一个编程单元，同一种类型，不能一起使用显式具体化和显式实例

void Swaptemplate(int a[],int b[],int n);//这三个声明对应下面的三个定义
//------------

int main_fu(){
	int a[10] = {0};
	cout<<"val of a :"<<a<<"  size"<<sizeof a<<endl;
	testFunc1(a,1);

	int b[10][10][10];//后面两个方括号数字必须与函数声明一致
	cout<<sizeof b<<" is b size"<<endl;//4*10*10*10
	testFunc2(b,1);

	int c[5][5];
	testFunc3(c,5);

	//这四种调用完全一样
	testFunPoint(54);
	(*testFunPoint)(54);
	void (*pf)(int) = testFunPoint;
	pf(55);
	(*pf)(55);//the same

	int retval = retA();
	cout<<"retA "<<retval<<" , address is "<<&retval<<endl;//可以看到retval的地址和函数中打印的地址不一样

	retB();
	cout<<"返回值是函数中的局部变量的引用，局部变量在函数调用结束后自动释放，因此函数不应该这样写："<<retB()<<endl;

	int s1 = 2,s2 = 3;
	swap(s1,s2);
	swap2(&s1,&s2);

	//引用是别名，不能将字面量或表达式赋给引用。函数swap参数是引用，所以这样调用会编译报错
//wrong:	swap(2,3);
//wrong:	swap(s1+s2,s1+s2);

	//但是如果形参是const，则可以。此时编译器会创建临时变量。因为声明了const，表明函数没有改变实参的意图，那么创建临时变量也就无所谓了
	cube(1+1+a[0]);

	harpo(1,2);

	Swaptemplate(s1,s2);



	int arr1[]={1,2,3};
	int arr2[]={4,5,6};
	//调用的是哪个方法取决于前面有没有声明
	//如果声明了void Swaptemplate(int a[],int b[],int n);则优先调用此函数
	//否则如果声明了template<> void Swaptemplate(int a[],int b[],int n);则调用此函数
	//否则调用模板函数
	Swaptemplate(arr1,arr2,3);

	return 0;
}

int harpo(int n,int m,int j){
	cout<<"j="<<j<<endl;
	return 0;
}

//函数模板本身不会生成函数定义，只是提供一个方案，由编译器根据代码生成定义
template<class AnyType> //same as template<typename AnyType>,除非需要考虑向后兼容，否则应该尽量使用typename
void Swaptemplate(AnyType &a,AnyType &b){
	AnyType tmp = a;
	a = b;
	b = tmp;
}
//如果调用Swaptemplate(2,3)，编译器自动根据模板生成一个void Swaptemplate(int&,int&)的函数，这个过程称为“隐式实例化(implicit instantiation)”
//有隐式就有显式，tag1处：template void Swaptemplate<int>(int&,int&);称为“显式实例化(explicit instantiation)”,也就是明确要求编译器生成实例
//有时，当type是某个类型时，不希望按照模板的代码逻辑实现，该特定的类型需要特别实现，于是又有了“显式具体化（explicit specialization）”,见tag2和tag3
//所以你应该很容易理解为什么同一个类型显式实例化和显式具体化不能同时使用
//--------------------


//-------------下面是三个几乎一样的方法
//重载的模板
template<typename AnyType>
void Swaptemplate(AnyType a[],AnyType b[],int n){
	AnyType tmp;
	for(int i = 0;i<n;i++){
		tmp = a[i];
		a[i] = b[i];
		b[i] = tmp;
	}
}
//tag3,具体化模板类型
template<> void Swaptemplate(int a[],int b[],int n){
	int tmp;
	for(int i = 0;i<n;i++){
		tmp = a[i];
		a[i] = b[i];
		b[i] = tmp;
	}
}
void Swaptemplate(int a[],int b[],int n){
	int tmp;
	for(int i = 0;i<n;i++){
		tmp = a[i];
		a[i] = b[i];
		b[i] = tmp;
	}

}
//--------------------------------
