/************************************************************************/
/* ��ʾһ�¶��ؼ̳С�����������                                         */
/************************************************************************/
#include <iostream>
using namespace std;

class Base{
protected:
	long id;
public:
	Base(long i=0):id(i){};

	//ֻҪ��ʽ�ṩ�˹��캯��(�����޲λ����в�)���ͱ����ṩvirtual����������������vs���汨Stack around the variable 'XXX' was corrupted��
	//ԭ��δ֪��Ҳ�޷���⡣linux������g++������û�������ġ�
	virtual ~Base(){}
};
class A:public Base{

};
class B: public Base{

};

class C :A,B{//classĬ����private�̳�,struct��Ĭ��public
public:
	void printId(){
		//C����������id���ֱ��A/B�̳й���,���Բ�ָ����Ļ�����������֪�����ʵ�����һ����
		A::id = 1;
		B::id = 2;
		//�Ѽ̳й�ϵ��ͼ��������һ�����Ρ�����̳й�ϵ����Ƚϼ򵥣���������ӣ���ͼ����ֱ�۵Ŀ���������η����ж����ԣ���η���û�ж����ԡ�
		cout<<A::id<<endl;//A�е�id
		cout<<B::id<<endl;//B�е�id

		//cout<<id<<endl;//������
		//cout<<Base::id<<endl;//����������Ҳ���ж����Եġ�����vs�õ�A::id

	}
};
//�����ĺ����ǣ���������·������"��" �ķ�ʽ�̳е�Base�๲��һ���������Ƕ���������ͱ����˶����Ե����⡣
class VA:virtual public Base{

};

class VB:public virtual Base{

};

//����VA��VB����virtual�̳�Base���������ǵ�Base��ͬһ������B����virtual������VC��������Base
class VC:public VA,VB,B{//VA�ǹ��м̳У�VB��˽�м̳�
public:
	void printId(){
		VA::id = 1;
		B::id = 4;
		cout<<VA::id<< "  same as " << VB::id<<endl;
		cout<<B::id<<endl;
		VB::id = 2;
		cout<<VA::id<< "  same as " << VB::id<<endl;
	}
};

int main14(){
	C c;
	c.printId();


	//Base * base = &c;//������,��Ϊc��������Base��������Ҫ��ת��B��A
	Base *baseA = (A*)&c;
	Base*baseB = (B*)&c;

	cout<<"--------"<<endl;

	VC vc;
	vc.printId();
	return 0;
}