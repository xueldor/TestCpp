#include <iostream>
#include <cctype>
using namespace std;

void testFunc(){
	char ch = 'A';
	cout<<"is 'A' Alphabet : "<<isalpha(ch)<<endl;//�ǲ�����ĸ
	
	cout<<"is '5' Alphabet : "<<isalpha('5')<<endl;//����0����false
	cout<<"is '5' digit : "<<isdigit('5')<<endl;//�ǲ�������

	cout<<"is '5' punctuation : "<<ispunct('5')<<endl;//�ǲ��Ǳ�����
	cout<<"is '.' punctuation : "<<ispunct('.')<<endl;//�ǲ��Ǳ�����
	
	cout<<"'A' to lower "<<(char)tolower('A')<<endl;//תСд
}

int main7(){
	testFunc();

	return 0;
}
