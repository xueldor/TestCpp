//��ʾ�����ռ�
#include <iostream>
#include <string>

using std::cout;
using std::endl;

namespace ����{

	std::string name = "����";
	void payed(){
		cout<<name<<" payed "<<" 8Ԫ"<<endl;
	}
}

namespace ����{

	std::string name = "����";
	void payed(){
		cout<<name<<" payed "<<" 10Ԫ"<<endl;
	}

	namespace �׶���{
		std::string name = "��С��";
	}
}

namespace{//δ������namespace

	//��Ϊnamespace�����ƣ����޷��������ļ������ô˱������൱����ȫ����������ʹ��static�����ı���
	int onlyThisFile = 1;
}

extern void printName();//��������ʡ��extern

int main_space(){

	using namespace ����;
	cout<<����::name<<endl;

	using namespace ����;//OK,using����ָ��
	cout<<����::name<<endl;

	using namespace ����;//OK
	cout<<����::name<<endl;

	using ����::name;//using����
	using ����::name;//OK,��Ϊ����ͻ
//wrong:��ͻ	using ����::name;

	cout<<����::�׶���::name<<endl;

	cout<<onlyThisFile<<endl;
	cout<<::onlyThisFile<<endl;

	printName();//���ļ�testScope2.cpp��

	return 0;
}