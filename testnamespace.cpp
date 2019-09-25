//演示命名空间
#include <iostream>
#include <string>

using std::cout;
using std::endl;

namespace 张三{

	std::string name = "张三";
	void payed(){
		cout<<name<<" payed "<<" 8元"<<endl;
	}
}

namespace 李四{

	std::string name = "李四";
	void payed(){
		cout<<name<<" payed "<<" 10元"<<endl;
	}

	namespace 亲儿子{
		std::string name = "李小四";
	}
}

namespace{//未命名的namespace

	//因为namespace无名称，故无法在其它文件中引用此变量。相当于在全局作用域中使用static声明的变量
	int onlyThisFile = 1;
}

extern void printName();//函数可以省略extern

int main_space(){

	using namespace 李四;
	cout<<李四::name<<endl;

	using namespace 张三;//OK,using编译指令
	cout<<张三::name<<endl;

	using namespace 张三;//OK
	cout<<张三::name<<endl;

	using 李四::name;//using声明
	using 李四::name;//OK,因为不冲突
//wrong:冲突	using 张三::name;

	cout<<李四::亲儿子::name<<endl;

	cout<<onlyThisFile<<endl;
	cout<<::onlyThisFile<<endl;

	printName();//在文件testScope2.cpp中

	return 0;
}