#include <iostream>
#include <string>
using namespace std;

namespace TestFunction {
    void testFunc1(int arr[], int n) {
        //arr[]作为形参，其实是指针，也可写作int* arr。C++不支持数组直接赋值，所以调用时是将地址传给arr，显然arr是指针
        cout << "testFunc1 " << arr << " sizeof arr : " << sizeof arr << ",sizeof *arr:  " << sizeof *arr
             << endl;//指针的大小,int类型的大小

    }

//arr其实是指针，指向int[10][10]类型的数据，所以第一个方括号中的数字其实无效，可以写成arr[][10][10]
    void testFunc2(int arr[5][10][10], int n) {
        //*arr是int arr[10][10]，所以sizeof *arr是4*10*10
        cout << "testFunc2 sizeof arr : " << sizeof arr << ",sizeof *arr:  " << sizeof *arr
             << endl;//指针的大小，int arr[10][10]的大小
    }

    void testFunc3(int (*arr)[5], int n) {//或者写成arr[][5]。注意int (*arr)[5]中的括号
        cout << "testFunc2 sizeof arr : " << sizeof arr << ",sizeof *arr:  " << sizeof *arr
             << endl;//指针的大小，int arr[10][10]的大小
    }

    void testFunPoint(int a) {
        cout << "test function pointer " << a << endl;

    }

    int retA() {
        //a作为局部变量，函数返回后就会释放。a的值在返回时复制到临时存储区域
        int a = 90;
        cout << "函数中的变量的地址:" << &a << endl;
        return a;
    }

    int &retB() {
        //返回类型是int&，直接返回a的引用。因为a是局部变量，所以这样写后果是无法预期的
        int a = 90;
        cout << "函数中的变量的地址:" << &a << endl;
        return a;//编译器警告：返回局部变量或临时变量的地址,运行时可能直接崩溃
    }

//引用作为函数参数,使得函数直接使用原始数据
    void swap(int &a, int &b) {
        int temp = a;
        a = b;
        b = temp;

    }

//函数通过指针访问原始数据
    void swap2(int *a, int *b) {
        int temp = *a;
        *a = *b;
        *b = temp;

    }

    void cube(const int &a) {
        cout << a << endl;
    }

/**
 * 1、默认值必须从右到左
 * 2、必须通过函数原型
 */
    int harpo(int n, int m, int j = 5);

    int haha(int a[5]){}
//    int haha(int a[]){}
//    int haha(int a[10]){}//报错：重复定义。这三个haha函数参数实质是一样的,int* a,方括号里的数字没用。

    int main() {
        int a[10] = {0};
        cout << "val of a :" << a << "  size" << sizeof a << endl;
        testFunc1(a, 1);

        int b[10][10][10];//后面两个方括号数字必须与函数声明一致
        cout << sizeof b << " is b size" << endl;//4*10*10*10
        testFunc2(b, 1);

        int c[5][5];
        testFunc3(c, 5);

        //这四种调用完全一样
        testFunPoint(54);
        (*testFunPoint)(54);
        void (*pf)(int) = testFunPoint;
        pf(55);
        (*pf)(55);//the same

        int retval = retA();
        cout << "retA " << retval << " , address is " << &retval << endl;//可以看到retval的地址和函数中打印的地址不一样

        retB();
        cout << "返回值是函数中的局部变量的引用，局部变量在函数调用结束后自动释放，因此函数不应该这样写：" << retB() << endl;

        int s1 = 2, s2 = 3;
        swap(s1, s2);
        swap2(&s1, &s2);

        //引用是别名，不能将字面量或表达式赋给引用。函数swap参数是引用，所以这样调用会编译报错
//wrong:	swap(2,3);
//wrong:	swap(s1+s2,s1+s2);

        //但是如果形参是const，则可以。此时编译器会创建临时变量。因为声明了const，表明函数没有改变实参的意图，那么创建临时变量也就无所谓了
        cube(1 + 1 + a[0]);

        harpo(1, 2);

        return 0;
    }

    int harpo(int n, int m, int j) {
        cout << "j=" << j << endl;
        return 0;
    }

}
