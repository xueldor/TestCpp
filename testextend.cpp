#include <iostream>
using namespace std;

class A{
public :
	A(){}
	A(int a){}
	void show(){cout<<"A show"<<endl;}
	virtual void show(int a){cout<<"virtual A show a"<<endl;}
	virtual void show(int a,int b){cout<<"virtual A show a b"<<endl;}
	void show(int a,int b,int c){cout<<"A show a b c"<<endl;}

	void tostring(){cout<<"A tostring"<<endl;}

	virtual void print(){cout<<"B print"<<endl;}

	A* get(){return this;}

	/*
	����������������Ϊvirtual����Ϊ��
	������ A* a = new B;
	�������virtual����ôdelete a, ��ֻ����A������������B�з������Դ�޷��ͷš�
	�������virtual��delete a�����ȵ��� ~B(), �ٵ��� ~A()
	*/
	virtual ~A(){}
};
class B:public A{
public :
	//����Ĺ��캯������Ҫ���ø���Ĺ��캯����Ĭ�ϵ��ø�����޲ι��캯��
	B(int a,int b){}
	//ͨ����Ա��ʼ���б���ø��๹�캯��
	B(int a):A(a){}
	B():A(1){}

	void show(){cout<<"B show"<<endl;}
	virtual void show(int a){cout<<"virtual B show a"<<endl;}

	//��Ϊ����������Ϊvirtual������������Զ���virtual
	void print(){cout<<"B print"<<endl;}

	//������ȫ�븸����ͬ��ֻ�Ƿ������Ͳ�ͬ����Ϊ��������Э�䡣
	B* get(){return this;}
};

class C{
public:
	virtual int c()=0;//���麯��������java��abstract ��ӿ�
};

int main13(){
	A a;
	B b;
	a.show();//�������ͺͶ���������A�����Ե���A�ķ�����
	b.show();//�������ͺͶ���������B�����Ե���B�ķ�����

	A *ap = &b;
	//ָ���������A,��ʵ��������B��Ҫ�������ǲ���virtual��
	ap->show();//��virtual����̬���࣬����ָ�����͵ķ���
	ap->show(1);//virtual����̬���࣬���ö�����ʵ���͵ķ���

	//���������ء�ֻҪBʵ����ĳ�������������������ͬ�����ط����������ء�ͨ����������ÿ��Ե��ã�ͨ�������������뱨��
	ap->show(1,2);//������B ���ͣ�����A���Ե��á�
	/*b.show(1,2);//ʵ����A�У�Bû��ʵ�֣������أ�B���ܵ���
	b.show(1,2,3);*/
	ap->show(1,2,3);//ʵ����A�У���B���أ����ǿ���ͨ��A����


	b.print();
	b.tostring();//tostringʵ����A�У�B�̳й�����B��û��ʵ��ͬ����tostring���������Բ�������

	/************************************************************************/
	/** ���ϲ��Ը������ǣ�
		���踸����һ������show,�������ɸ����ذ汾����ô���������棺
	    1. Ҫô��Ҫʵ��show�������̳и���ġ�	
		2. ֻҪʵ����show��������Ҫʵ������������������غ���������û��ʵ�ֵĺ�������������ء�
		3. ������д���෽�������뱣֤�����ͷ�������ȫһ�¡��������Ϳ��Բ�ͬ��
	  
	*/
	/************************************************************************/


	cout<<"---------�ָ� 1 ---------"<<endl;
	b.show();
	b.A::show();

	b.show(1);
	b.A::show(1);
	//���ϣ���ʾ����ε��ø���ĺ�����
	return 0;

}