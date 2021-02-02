#include <iostream>
#include <string>
using namespace std;


void testFunc1(int arr[],int n){
	//arr[]��Ϊ�βΣ���ʵ��ָ�룬Ҳ��д��int* arr��C++��֧������ֱ�Ӹ�ֵ�����Ե���ʱ�ǽ���ַ����arr����Ȼarr��ָ��
	cout<<"testFunc1 "<<arr<<" sizeof arr : "<<sizeof arr<<",sizeof *arr:  "<<sizeof *arr<<endl;//ָ��Ĵ�С,int���͵Ĵ�С

}

//arr��ʵ��ָ�룬ָ��int[10][10]���͵����ݣ����Ե�һ���������е�������ʵ��Ч������д��arr[][10][10]
void testFunc2(int arr[5][10][10],int n){
	//*arr��int arr[10][10]������sizeof *arr��4*10*10
	cout<<"testFunc2 sizeof arr : "<<sizeof arr<<",sizeof *arr:  "<<sizeof *arr<<endl;//ָ��Ĵ�С��int arr[10][10]�Ĵ�С
}

void testFunc3(int (*arr)[5],int n){//����д��arr[][5]��ע��int (*arr)[5]�е�����
	cout<<"testFunc2 sizeof arr : "<<sizeof arr<<",sizeof *arr:  "<<sizeof *arr<<endl;//ָ��Ĵ�С��int arr[10][10]�Ĵ�С
}

void testFunPoint(int a){
	cout<<"test function pointer "<<a<<endl;

}

int retA(){
	//a��Ϊ�ֲ��������������غ�ͻ��ͷš�a��ֵ�ڷ���ʱ���Ƶ���ʱ�洢����
	int a = 90;
	cout<<"�����еı����ĵ�ַ:"<<&a<<endl;
	return a;
}
int& retB(){
	//����������int&��ֱ�ӷ���a�����á���Ϊa�Ǿֲ���������������д������޷�Ԥ�ڵ�
	int a = 90;
	cout<<"�����еı����ĵ�ַ:"<<&a<<endl;
	return a;//���������棺���ؾֲ���������ʱ�����ĵ�ַ
}

//������Ϊ��������,ʹ�ú���ֱ��ʹ��ԭʼ����
void swap(int &a,int &b){
	int temp = a;
	a = b;
	b = temp;
	
}
//����ͨ��ָ�����ԭʼ����
void swap2(int *a,int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
	
}

void cube(const int&a){
	cout<<a<<endl;
}

/**
 * 1��Ĭ��ֵ������ҵ���
 * 2������ͨ������ԭ��
 */
int harpo(int n,int m,int j = 5);

int main_fu(){
	int a[10] = {0};
	cout<<"val of a :"<<a<<"  size"<<sizeof a<<endl;
	testFunc1(a,1);

	int b[10][10][10];//�����������������ֱ����뺯������һ��
	cout<<sizeof b<<" is b size"<<endl;//4*10*10*10
	testFunc2(b,1);

	int c[5][5];
	testFunc3(c,5);

	//�����ֵ�����ȫһ��
	testFunPoint(54);
	(*testFunPoint)(54);
	void (*pf)(int) = testFunPoint;
	pf(55);
	(*pf)(55);//the same

	int retval = retA();
	cout<<"retA "<<retval<<" , address is "<<&retval<<endl;//���Կ���retval�ĵ�ַ�ͺ����д�ӡ�ĵ�ַ��һ��

	retB();
	cout<<"����ֵ�Ǻ����еľֲ����������ã��ֲ������ں������ý������Զ��ͷţ���˺�����Ӧ������д��"<<retB()<<endl;

	int s1 = 2,s2 = 3;
	swap(s1,s2);
	swap2(&s1,&s2);

	//�����Ǳ��������ܽ�����������ʽ�������á�����swap���������ã������������û���뱨��
//wrong:	swap(2,3);
//wrong:	swap(s1+s2,s1+s2);

	//��������β���const������ԡ���ʱ�������ᴴ����ʱ��������Ϊ������const����������û�иı�ʵ�ε���ͼ����ô������ʱ����Ҳ������ν��
	cube(1+1+a[0]);

	harpo(1,2);

	return 0;
}

int harpo(int n,int m,int j){
	cout<<"j="<<j<<endl;
	return 0;
}
