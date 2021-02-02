#include <iostream>
#include <string>
#include "a.h"
using namespace std;

//-------
//����
template<typename T>
void Swaptemplate(T &a,T &b);//��Ȼ������������ľ���ʵ�֣�����������ʵ�ǲ���Ҫ�ġ�ֻ����ʾ�﷨��

//ʵ��
//����ģ�屾�������ɺ������壬ֻ���ṩһ���������ɱ��������ݴ������ɶ���
template<class T> //same as template<typename AnyType>,������Ҫ���������ݣ�����Ӧ�þ���ʹ��typename
void Swaptemplate(T &a,T &b){
	cout<<"����ģ��Swaptemplate(T &a,T &b)"<<endl;
	T tmp = a;
	a = b;
	b = tmp;
}
//���ص�ģ��
template<typename T>
void Swaptemplate(T a[],T b[],int n){
	cout<<"����ģ��Swaptemplate(T &a,T &b,int n)"<<endl;
	T tmp;
	for(int i = 0;i<n;i++){
		tmp = a[i];
		a[i] = b[i];
		b[i] = tmp;
	}
}
//--------end
//1. ��ʽʵ������ �����ڼ䣬���д������ʱ���������Զ����ݴ���Ĳ������ͣ���ģ�����ɺ�������.�� tag 1

//2. ��ʽʵ������ ͨ���������������ȷҪ�����������ģ�����ɺ�������
template void Swaptemplate<long>(long&, long&);//template����û��<>,��ʾ��ʽʵ��������������ģ������ʵ�֣����Ժ��治��Ҫ�������壬�����������ʽ���廯
template void Swaptemplate<float>(float&, float&);
//��Ȼ������ʽʵ��������Ϊʲô����Ҫ��ʽʵ�����أ����a.h ��a.cpp ,Ϊ�������߼����ҽ�foo��ʵ�ַ���a.cpp�a.h��ֻ����������ô������a.cpp������ʽʵ���������ܵ��ã�����ú���������(�޷��������ⲿ����)��
//Ҳ����˵����ʽʵ����ֻ���Զ����ɱ��ļ��Ļ��߱�include�����ļ���ģ�庯����������д����һ���⣬�����������ã���ô������ʽʵ������

//��ͨ�ĺ�����������ģ���޹أ����Ƿ�ģ������������ȼ�����ʽʵ�����������ߣ���������Ҫע�͵������򽫵��÷�ģ��汾
//void Swaptemplate(long,long);

//3. ��ʽ���⻯����ʽר�û�����ʽ���廯�� : �е�ʱ�򣬶���ĳ�����ͣ�ģ�庯���е��߼������ã�ϣ�������������ר��ʵ��һ���߼���
template<> void Swaptemplate(string& a,string& b);//��������Ȼ������������ľ���ʵ�֣�����������ʵ�ǲ���Ҫ�ġ�ֻ����ʾ�﷨��
template<> void Swaptemplate(string& a,string& b){//ʵ��
	cout<<"����ģ��Swaptemplate��������"<<endl;
}



//ģ���֪ʶ���Բο� https://qixinbo.info/2017/07/09/cplusplus-template/
int main_ft(){
	int s1 = 2,s2 = 3;
	//��ʽʵ����
	Swaptemplate(s1,s2);//tag 1

	long s3 = 2,s4 = 3;
	Swaptemplate(s3, s4);

	int a=1;
	foo(a);

	string aStr = "aa";
	string bStr = "bb";
	Swaptemplate(aStr,bStr);

	//��ʽģ��ʵ�Σ������ں���ģ�壬���ڵ��ú���ʱ��ʽָ��Ҫ���õ�ʵ�ε�����
	cout<<"��ʽģ��ʵ��:"<<endl;
	//Swaptemplate<short>(s1,s2);��ȷָ��ģ������������short������ᱨ�����ܽ����� 1 �ӡ�int��ת��Ϊ��short &��
	Swaptemplate<short>((short&)s1,(short&)s2);



	//���������void change(int a[],int b[],int n);�����ȵ��÷�ģ��汾
	//�������������template<> void change(int a[],int b[],int n);�����ģ���������İ汾
	//�������ģ�庯��������Ĵ�����ʾ

	int arr1[]={1,2,3};
	int arr2[]={4,5,6};
	void callChange(int arr1[],int arr2[],int len);
	callChange(arr1,arr2,3);


	void callChange();
	void callChange2();//������

	callChange();
	callChange2();


	return 0;
}


//-----------demo2 start

//Ҫ������ģ��ԭ�ͣ�Ȼ���������template<> void change(int a[],int b[],int n)
template<typename AnyType>
void change(AnyType a[],AnyType b[],int n);

void callChange(int arr1[],int arr2[],int len){
	{
		//�������ڴ�������棬��Ӱ�����档����ģ�岻���ڷ�����������
		void change(int a[],int b[],int n);//�ڷ�����������������õ����棬���÷�Χ����Ӱ�����Ĵ���

		change(arr1,arr2,len);//����û��ģ��İ汾

		//��ģ���������int[]���ͣ������long[]���ͣ���ô�Ƿ��Ӧ�õ���ģ���ʵ�ְ汾�أ�ʵ���������ǻ���÷�ģ��ʵ�֣�Ȼ����뱨��long[]�޷�ת��Ϊint[]
		long arr3[]={1,2,3};
		long arr4[]={4,5,6};
		//change(arr1,arr4,3);//long[]�޷�ת��Ϊint[]

	}
	int arr3[]={1,2,3};
	int arr4[]={4,5,6};
	//change(arr1,arr4,3);//������õľ���ģ���ʵ�ְ汾�ˡ�����ִ�����л����һ��AnyTypeΪint�ĺ���ʵ�֣�����������һ��int���͵�����������������ע�͵����Ͼ�����������һģһ���ĺ�����
	//Ҳ����˵��ͬһ����̵�Ԫ��ͬһ������ԭ�ͣ�ͬһ�����ͣ�����һ��ʹ����ʽ���廯����ʽʵ��

	long arr5[]={1,2,3};
	long arr6[]={4,5,6};
	change(arr5,arr6,3);//����ģ���ʵ�ְ汾
}

//��������change��������
template<> void change(int a[],int b[],int n);
void callChange(){
	int arr1[]={1,2,3};
	int arr2[]={4,5,6};
	change(arr1,arr2,3);//ǰ���������������������������õ��������汾��(��tag 2)
}

void change(int a[],int b[],int n);//������ģ���change����
template<> void change(int a[],int b[],int n);//������������change����
void callChange2(){
	int arr1[]={1,2,3};
	int arr2[]={4,5,6};
	change(arr1,arr2,3);//ǰ��ͬʱ�����˷�ģ���ģ�壬��Ȼ���ȵ��÷�ģ��汾
}



//-------------��������������һ���ķ�������ômain����������ĸ�����ȡ���ڣ�ǰ����������ĸ��汾����������˶������ô��ģ��汾�����ȼ���ߵġ�
//ģ��
template<typename AnyType>
void change(AnyType a[],AnyType b[],int n){
	cout<<"call change template" << endl;
	AnyType tmp;
	for(int i = 0;i<n;i++){
		tmp = a[i];
		a[i] = b[i];
		b[i] = tmp;
	}
}
//���int����������
template<> void change(int a[],int b[],int n){//tag 2
	cout<<"call change template specialization" << endl;
	int tmp;
	for(int i = 0;i<n;i++){
		tmp = a[i];
		a[i] = b[i];
		b[i] = tmp;
	}
}
//��ģ��汾
void change(int a[],int b[],int n){
	cout<<"call change no template" << endl;
	int tmp;
	for(int i = 0;i<n;i++){
		tmp = a[i];
		a[i] = b[i];
		b[i] = tmp;
	}

}
//--------------------------------