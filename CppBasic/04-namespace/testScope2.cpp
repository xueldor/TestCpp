#include <iostream>
#include <string>
using namespace std;

extern int global;
//wrong: extern const int global2;
extern const int global3;
extern int global4;

#include "testnamespace.h"
using namespace 张三;
using 李四::payed;

void printV(){
	cout<<"global3 "<<global3<<endl;
	cout<<"global4 "<<global4<<endl;

}

void onlyThisFile(){
	using namespace std;
	cout<<"Can only call in this file 22"<<endl;
}

void printName(){
	cout<<"printName "<<张三::name<<endl;
//wrong     	payed();//同时引入了张三和李四两个命名空间，其中都包含payed，所以直接调用payed有二义性

	李四::payed();
}