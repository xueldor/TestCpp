#include <iostream>
#include <string>

using namespace std;

void teststring(){
	string str1;
	string str2 = "Tom";
	str1 = str2;//���鲻�ܸ�ֵ��string������ԣ���ΪC++�ж���ͽṹ����ֱ�Ӹ�ֵ���ڴ��еĶ���´��һ��
	cout<<str1<<endl;

	str2+=" is stupid";//ƴ��
	cout<<str2<<endl;

	char hungry[] = " hungry boy";
	str1 += hungry;//��C����ַ���ƴ��
	cout<<str1<<endl;

	str1 = hungry;//C����ַ�����ֵ��string����
	cout<<str1<<endl;

	const char* tom = str2.c_str();//stringתC����ַ���
	cout<<tom<<endl;



}


int main4(){
	teststring();

	return 0;
}