#include<stdio.h>
#include <stdlib.h>
#include <new.h>

//��ʾ����������new�ı��ʡ�
namespace test_new {
class A
{
private:
	int id;

public:
	A(int i) : id(i) {}
	void Say() { printf("id=%d\n", id); }

};

/*
�����൱��new A(3)��
1��malloc�����ڴ棬��sizeof��������С��
2�����ù��캯����ע��Ҫ��A::��������ͨ������Ȼ����Ҫ��
3������ָ��

��Ȼ��ʵ����new��ʵ�ָ����ӣ���������ڴ�ʧ��ʱ���쳣����ȡ��������Ҫ�����ܵ�ʹ��new��
*/
A* newA(){
	A* pa = (A*)malloc(sizeof(A)); 
	pa->A::A(3);
	return pa;
}


//C++�е�new, �����÷���
//1��new operator������newһ�����󡣱���new A;
//2��operator new: ����new
//3��placement new: ���û�ָ�����ڴ��Ϲ�������ڴ������ջ������Ҫ#include <new.h>
class AB
{
	int member;
public: 
	//����new����
	static void* operator new(size_t size)
	{//�ȴ�ӡ��־���ٵ���ȫ�ֵ�new��Ҳ����ԭ����new��
		printf("AB::operator new called,size=%d\n",size); 
		return ::operator new(size);
	}
	//����delete����
	static void operator delete(void* pdead)
	{//�ȴ�ӡ��־���ٵ���ȫ�ֵ�delete��Ҳ����ԭ����delete��
		printf("AB::operator delete called\n"); 
		return ::operator delete(pdead);
	}

	static void* operator new[](size_t size){
		printf("AB::operator new[] called,size=%d\n",size); 
		void* tmp =  ::operator new(size);
		printf("pointer new() at %p\n",tmp);
		return tmp;
	}
	static void operator delete[](void* pdead, size_t tt){
		printf("AB::operator delete[] called,point at %p\n",pdead);//pdeadָ�� ����ʾ���鳤�ȵ��ĸ��ֽڡ����׵�ַ��������������׵�ַ������free(pdead)�ǳ��׵ġ�
		free(pdead);
	}

	~AB(){}
};


}
int main15(){
	test_new::A* pa = new test_new::A(5);
	pa->Say();
	delete pa;

	test_new::A* pb = test_new::newA();
	pb->Say();
	delete pb;

	test_new::AB *pab = new test_new::AB;
	delete pab;
	//����ʽ����operator newʱ��Ҫ�Լ��������Ĵ�С��
	test_new::AB* pab2 = (test_new::AB*)test_new::AB::operator new(sizeof(test_new::AB));
	delete pab2;

	//ͨ��printf("AB::operator new[] called,size=%d\n",size); ��ӡ����־����ῴ��size=28
	//һ�������С��4byte��������6����ô�ڴ�Ӧ����4*6=24�����4byte��������¼����ĳ��ȣ�����delete[]ʱ����֪�������С��
	test_new::AB *pabArr = new test_new::AB[6];
	//printf("pointer new() at %p\n",tmp);���������д�ӡ�ĵ�ַ�������4���ֽڡ�
	printf("pointer new[] at %p\n",pabArr);
	//���Ⲣ���Ǿ��Եġ������AB�����������ɾ�����Ͳ����������4�ֽ��ˡ����ǲ�Ҫ����ʲôʱ�����䡣

	delete []pabArr;

	//placement new,Ҫ#include <new.h>
	int place[3] = {7,2,3};
	int* pplace = new(place)int;
	int* pplace2 = new(place + 1)int;
	int* pplace3 = new(&place[2])int;
	printf("pplace=%d\n",*pplace);
	printf("pplace=%d\n",*pplace2);
	printf("pplace=%d\n",*pplace3);



	return 0;

}