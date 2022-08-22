#include "a.h"
template<class T>
void foo(T a)
{
	//打印a;
}

//如果此代码以源码形式给别人用，或许没有必要显式实例化，但是如果你编译成库文件，就必须写下面这行声明，否则你的库里没有foo(int)这个函数
template void foo<int>(int);