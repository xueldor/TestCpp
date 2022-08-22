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
	void init(int i){
	    id = i;
	}
	void Say() { printf("id=%d\n", id); }

};

/*
C++的new运算符分两部：
 1）调用系统默认的全局::operator new(size_t )，系统默认的全局::operator new(size_t size)也只是调用malloc分配内存，并且返回一个void*指针。
 2）调用构造函数
这个函数做了以下事件：
1、malloc分配内存，用sizeof计算对象大小。
2、调用构造函数。注意要加A::。调用普通方法当然不需要。(新编译器已经不支持)
3、返回指针
所以这个函数大致相当于new A(3)。
当然，实际中new的实现更复杂，比如分配内存失败时的异常处理等。因此我们要尽可能的使用new。
*/
A* newA(){
	A* pa = (A*)malloc(sizeof(A)); 
//	pa->A::A(3);//invalid on new compiler
    pa->init(3);
	return pa;
}


//C++中的new, 三种用法：
//1、new 运算符，就是new一个对象。比如new A;
//2、operator new函数: 重载operator new函数，分为全局重载和类重载
//3、placement new: 在用户指定的内存上构造对象，内存可以是栈区。需要#include <new.h>

/**
 * 类重载
 * 如果类重载了operator new，那么将调用A::operator new(size_t )，如果没有重载，就调用::operator new(size_t )即系统提供的全局实现
 */
class AB
{
	int member;
public: 
	//重载new符号
	static void* operator new(size_t size) {
        //先打印日志，再调用全局的new（也就是原来的new）。
		printf("AB::operator new called,size=%d\n",size); 
		return ::operator new(size);//因为我在tag1处连全局的new一起重载了，所以这里调用的不是系统默认行为，而是我的自定义行为
	}
	//重载delete符号
	static void operator delete(void* pdead) {
        //先打印日志，再调用全局的delete（也就是原来的delete）
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

}//end of namespace

/**
 * tag1
 * 重载系统的全局operator new
 */
void* operator new(size_t sz){
    printf("正在分配内存 by test_new size=%d \n", sz);
    void* mem = malloc(sz);
    if(mem){
        return mem;
    } else {
        throw std::bad_alloc();
    }
}
void operator delete(void* ptr, size_t sz) {//tag2
    printf("正在回收内存 by test_new at %p \n", ptr);
    free(ptr);
}

int main_new(){
	test_new::A* pa = new test_new::A(5);
	pa->Say();
	delete pa;

	test_new::A* pb = test_new::newA();
	pb->Say();
	delete pb;

    {
        printf("测试new int\n");
        int *pint = new int(5);
        delete pint;//执行tag2
        pint = NULL;
        printf("测试delete\n");
    }

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

	//---------测试placement new,要#include <new>
    void testplacementNew();//声明
    testplacementNew();
    //-----------------

	return 0;

}
//指定位置构造对象。可以在栈上，也可以在堆上
#include<new>
void testplacementNew(){
    //test 1
    int place[3] = {7,2,3};
    int* pplace = new(place)int;
    int* pplace2 = new(place + 1)int;
    int* pplace3 = new(&place[2])int;
    printf("pplace=%d\n",*pplace);
    printf("pplace=%d\n",*pplace2);
    printf("pplace=%d\n",*pplace3);

    //test 2
    using namespace std;
    char buffer[10];
    char * pbuf = new (buffer)char;//在buffer的位置生成对象。
    //地址应该一样
    printf("pbuf的地址：%p ,buffer的首地址：%p\n", pbuf, buffer);

    pbuf = new ((int*)buffer+1)char;////在地址buffer+sizeof(int)的位置生成对象。
    printf("pbuf的地址：%p \n", pbuf);
    //不需要使用delete释放，而且也不能这样做

}