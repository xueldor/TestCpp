#include<stdio.h>
#include <stdlib.h>
#include <new.h>

//本示例用来剖析new的本质。
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
大致相当于new A(3)。
1、malloc分配内存，用sizeof计算对象大小。
2、调用构造函数。注意要加A::。调用普通方法当然不需要。
3、返回指针

当然，实际中new的实现更复杂，比如分配内存失败时的异常处理等。因此我们要尽可能的使用new。
*/
A* newA(){
	A* pa = (A*)malloc(sizeof(A)); 
	pa->A::A(3);
	return pa;
}


//C++中的new, 三种用法：
//1、new operator，就是new一个对象。比如new A;
//2、operator new: 重载new
//3、placement new: 在用户指定的内存上构造对象，内存可以是栈区。需要#include <new.h>
class AB
{
	int member;
public: 
	//重载new符号
	static void* operator new(size_t size)
	{//先打印日志，再调用全局的new（也就是原来的new）
		printf("AB::operator new called,size=%d\n",size); 
		return ::operator new(size);
	}
	//重载delete符号
	static void operator delete(void* pdead)
	{//先打印日志，再调用全局的delete（也就是原来的delete）
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
		printf("AB::operator delete[] called,point at %p\n",pdead);//pdead指向 “表示数组长度的四个字节”的首地址，而不是数组的首地址。所以free(pdead)是彻底的。
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
	//当显式调用operator new时，要自己计算对象的大小。
	test_new::AB* pab2 = (test_new::AB*)test_new::AB::operator new(sizeof(test_new::AB));
	delete pab2;

	//通过printf("AB::operator new[] called,size=%d\n",size); 打印的日志，你会看到size=28
	//一个对象大小是4byte。数组是6，那么内存应该是4*6=24。多出4byte，用来记录数组的长度，这样delete[]时，才知道数组大小。
	test_new::AB *pabArr = new test_new::AB[6];
	//printf("pointer new() at %p\n",tmp);跟下面这行打印的地址，相差了4个字节。
	printf("pointer new[] at %p\n",pabArr);
	//但这并不是绝对的。比如把AB类的析构函数删掉，就不会分配额外的4字节了。我们不要关心什么时候会分配。

	delete []pabArr;

	//placement new,要#include <new.h>
	int place[3] = {7,2,3};
	int* pplace = new(place)int;
	int* pplace2 = new(place + 1)int;
	int* pplace3 = new(&place[2])int;
	printf("pplace=%d\n",*pplace);
	printf("pplace=%d\n",*pplace2);
	printf("pplace=%d\n",*pplace3);



	return 0;

}