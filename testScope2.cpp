#include <iostream>
#include <string>
using namespace std;

extern int global;
//wrong: extern const int global2;
extern const int global3;
extern int global4;

#include "testnamespace.h"
using namespace ����;
using ����::payed;

void printV(){
	cout<<"global3 "<<global3<<endl;
	cout<<"global4 "<<global4<<endl;

}

void onlyThisFile(){
	using namespace std;
	cout<<"Can only call in this file 22"<<endl;
}

void printName(){
	cout<<"printName "<<����::name<<endl;
//wrong     	payed();//ͬʱ�������������������������ռ䣬���ж�����payed������ֱ�ӵ���payed�ж�����

	����::payed();
}