#include <iostream>
using namespace std;

//λ��������������<<,>>,~,&,|,^
void testbit(){
	int aa = 1;
	cout<<(aa<<2)<<endl;//������λ����λ��0

	int bb = -256;
	cout<<(bb>>2)<<endl;//�����з���������λ��������λ������λ����Ϊ��������

	unsigned cc = 0xFFFFFFFF;
	cout<<(cc>>2)<<"   "<<hex<<(cc>>2)<<dec<<endl;//�����޷���������λ��������λ��0����Ϊ�߼�����

	int dd = 1;
	cout<<"��λȡ�� "<<(~dd)<<endl;//��λȡ��
	cout<<"�߼��� "<<(!!dd)<<endl;//�ǲ�������trueת��false��falseת��true

	cout<<(aa&bb)<<endl;//λ��
	cout<<(aa|bb)<<endl;//λ��
	cout<<(aa^bb)<<endl;//���
}


/**
 * ѭ������
 */
unsigned char rolByte(unsigned char val, int size)
{
  unsigned char res = val << size;
  res |= val >> (sizeof(val)*8 - size);
  return res;
}

/*ѭ�������ֽ�*/
unsigned char rorByte(unsigned char val, int size)
{
  unsigned char res = val >> size;
  res |= val << (sizeof(val)*8 - size);
  return res;
}


/**
 * ѭ������int
 */
int rolInt(int val, int size)
{
  int res = val << size;
  res |= ((unsigned)val) >> (sizeof(val)*8 - size);
  return res;
}

/*ѭ������int*/
int rorInt(int val, int size)
{
  int res = ((unsigned)val) >> size;
  res |= val << (sizeof(val)*8 - size);
  return res;
}


int main5(){
	testbit();

	cout<<"һ�ֽ�ѭ������ "<<(int)rolByte((char)129,1)<<endl;//10000001->00000011,���3
	cout<<"һ�ֽ�ѭ������ "<<(int)rorByte((char)129,1)<<endl;//10000001->11000000,���192
	cout<<"intѭ������ "<<(int)rorInt(0x80000000,1)<<endl;//10000000000000000000000000000000->01000000000000000000000000000000,���1,073,741,824
	cout<<"intѭ������ "<<(int)rolInt(0x80000001,1)<<endl;//����˻���int��32λ��10000000000000000000000000000001->00000000000000000000000000000011,���3

	return 0;
}