#include <iostream>
#include "coordin.h"
#include "coordin.h"//ͨ��#ifndefָ����Եڶ��ΰ���������


//wrong : auto������������ ��auto int y;

void autoVariable(){
	//�Զ����������ڴ��ջ�У�����CPU�Ĵ�����
	using namespace std;
	auto int x;//same as int x;auto��������ʹ�ã����ʹ�ã�ֻ��Ϊ������߳��庬��

	register int y;//�Ĵ�������û�е�ַ
	int* py = &y;//���Ա�����ʵ��û��ʹ�üĴ������洢�ñ���
	cout<<py<<endl;
}

int i = 0;
//---------��̬��������Ĭ�϶���0
//ֻ��ʹ�ó������ʽ����ʼ��
int global = 1000;//��̬�洢���ⲿ���ӣ����������������ļ���ʹ�á������ļ���extern����һ�¾Ϳ���ʹ��
static int global_thisfile = 1200;//��̬�洢���ڲ����ӣ�����ֻ�ڴ��ļ���ʹ��
const int global2 = 44;//�ȼ���const static int global2 = 44;������const�������ڲ����ӣ�ֻ���ļ�����
extern const int global3 = 54;//��extern��ʽָ��Ϊ�ⲿ���ӣ�Ȼ���������ļ�����external����

extern int global4 = 46;//���Ƕ��壬�����ļ��в����ظ����ֶ���
extern int global5;//��������

void staticVariable(){
	using namespace std;
	//ֻ�ڴ˴������ã�������������ִ�����ڶ����ڡ�
	static int static_in_func = 2;//��̬�洢���������ԡ�ֻ��ʼ��һ��
	static_in_func++;
	if(i++<3){
		cout<<"static_in_func "<<static_in_func<<endl;
		staticVariable();//��Ȼ�������ã�����static_in_func���ᷴ����ʼ��
	}
}

void staticVariable2(){
	using namespace std;

	//������������ʱ���ֲ����������ھ�̬�������ڲ����ӵ��������ⲿ�����ġ�������ΧС�����ȼ�����
	cout<<"�ⲿ "<<global<<endl;
	int global = 1001;
	cout<<"�ֲ����� "<<global<<endl;
	cout<<"���ʱ����ص��ⲿ���� "<<::global<<endl;//ʹ��ȫ�����ƿռ��µ�global����

	cout<<"�ⲿ2 "<<global4<<endl;

	const int state = 100;//������Ϊ�����
}
//----------------END

//testScope2.cpp��Ҳ������onlyThisFile(),��������ʹ�ñ��ļ��е�static����
static void onlyThisFile();


//---------���Ե�������(Language linking)
//����֪ʶ��C���Ա��������ܽ���������Ϊ_spiff
//C++֧�����أ�����Ҫ����Ϊ��_spiff_i
//���ӳ���Ѱ�Һ���ʱ��C��C++�ǲ�һ���ġ���ô���C++������ʹ��C����Ԥ����ĺ����������Ҳ���
extern "C"void spiff(int);//��������£�ָ��extern "C",ʹ��C����������
extern "C++"void spot(int);//ָ��C++�������ӡ�

//-----END




int main_scope(){
	autoVariable();
	staticVariable();
	staticVariable2();

	//������
	extern void printV();
	printV();

	onlyThisFile();


	void testplacementNew();//����
	testplacementNew();
	return 0;
}

//------ͨ��static����������������Ϊ�ڲ���������Ĭ�϶����ⲿ��
static void onlyThisFile(){
	using namespace std;
	cout<<"Can only call in this file"<<endl;
}

//ָ��λ�ù�����󡣿�����ջ�ϣ�Ҳ�����ڶ���
#include<new>
void testplacementNew(){
	using namespace std;
	char buffer[10];
	char * pbuf = new (buffer)char;//��buffer��λ�����ɶ���
	//��ַӦ��һ��
	cout<<"pbuf�ĵ�ַ��"<<(void*)pbuf<<",buffer���׵�ַ��"<<(void*)buffer<<endl;//ת��void*��Ϊ��cout�����ַ�������ַ���

	pbuf = new ((int*)buffer+1)char;////�ڵ�ַbuffer+sizeof(int)��λ�����ɶ���
	cout<<"pbuf�ĵ�ַ��"<<(void*)pbuf<<endl;
	//����Ҫʹ��delete�ͷţ�����Ҳ����������


}