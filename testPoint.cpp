#include <iostream>
using namespace std;


void testpoint(){
//wrong,���ܶԳ���ȡ��ַ :  int *ps = &8;

	const int a = 6;
	cout<<&a<<endl;//OK

	int * pa = 0;//NULL
	delete pa;//OK
	delete pa;//OK,�յ�ַ��delete���ǰ�ȫ��


	int *pt = (int*)0xB8000000U;//��ַ������int��C99��׼֮ǰ��C���Կ���ֱ�Ӹ�ֵ��C++�б���ǿת��
	long val = (long)pt;


	int* pb = new int;
	cout<<"ָ�������ȣ�"<<sizeof pb<<endl;
	cout<<"ָ��ָ�����ݵĳ��ȣ�"<<sizeof *pb<<endl;
	delete pb;
//wrong ,����delete����	��  delete pb;

	int arr1[5];
	cout<<"��̬���������sizeof���С��"<<sizeof arr1/sizeof arr1[0]<<endl;;

	int * arr2 = new int[5];
	cout<<"���Ƕ�̬��������鲻�ܣ�"<<sizeof arr2<<" ,����ָ��ĳ��ȣ�����64λ��ַ���8"<<endl;

	cout<<"ָ��+1��ָ��ֵ����ָ������͵��ֽ�����"<<*(arr2+1)<<endl;
	
	cout<<"ָ��+1��ָ��ֵ����ָ������͵��ֽ���,(int)(arr2+1)-(int)arr2 = "<<(int)(arr2+1)-(int)arr2<<endl;

	int *pt1 = (int*)0xB8000000U;
	int *pt2 = (int*)0xB8000004U;
	cout<<"ָ��������ڵ�ַ�Ĳ�������ʹ�С�� "<<pt2-pt1<<endl;//���1

	delete[]arr2;

}

void testconstPoint (const int* param){//ָ�����һ��Ӧ��������Ϊ����

	const float g = 9.8f;
	const float *pg = &g;
//wrong,*pg is const	*pg = 9.9f;

	float e = 2.7f,pi=3.14f;
	float * const ph = &e;
//wrong,ph is const	ph = &pi;

	float *pf = const_cast<float*>(pg);//ȥ��const
	*pf = 11.0f;
	cout<<*pf<<endl;
}

void testref(){

	//���﷨����Ƕȿ��������൱�ڱ�����d��d_at������ֵ���ǵ�ַ��һ��
	int d = 56;
	int& d_at = d;//����������ʱ��ʼ��
	cout<<d<<"  "<<d_at<<"  "<<&d<<"  "<<&d_at<<endl;

	//�ӱ������Ƕȣ����õ�ʵ��ֻ�ǻ���ָ��Ĵ������һ���ӿڣ�*pd�൱��d_at,pd�൱��&d_at
	int * const pd = &d;//���ýӽ�constָ��
	cout<<d<<"  "<<*pd<<"  "<<&d<<"  "<<pd<<endl;



	const int aaa = 99;
	const int &bbb = aaa;//OK
}

int main_p(){
	testpoint();
	int a = 10;
	testconstPoint (&a);
	testref();

	return 0;
}