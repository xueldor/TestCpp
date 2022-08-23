#include <iostream>
#include <string>
using namespace std;

namespace TestFunction {
    /**
     * C语言不支持数组作为函数的 参数 和 返回值。可以认为这是一个设计上的缺陷。
     * C++为了兼容C，同样不允许数组作为返回值和参数。
     * 我们知道数组是不能直接赋值给另外一个数组的，既然如此，当然也就不能作为函数参数和返回值了（调用函数时，会把参数复制给形参，除非加引用。既然数组不能整个复制，当然也就不能作为参数。返回值同理）
     * 当然，数组可以赋给指针，但赋值的是地址而已，并不是整个数组内存上的整个对象。
     * 当需要返回数组时，
     * 1. 用out参数，即增加一个数组类型的参数，用来放结果。参考string.h里的一系列字符串处理函数的设计。
     * 2. 返回类型声明为指针，然后函数体内返回数组名（即地址）。缺点是：
     *      1）调用者不知道数组长度；
     *      2）开发者及其容易犯错，因为这种设计，数组往往是在函数体内创建的，是局部变量，调用结束后即释放，调用者继续使用这个地址的内存，如果恰好这个内存没有被覆盖，则正常工作，反之则不能，这种不明确的行为导致开发者发现问题很困难。
     *         而如果采用动态分配的方法，调用者就需要记得释放内存，违法了谁分配谁释放的原则。想象一下，调用者并不关心返回的数组是在堆上还是在栈上，如果调用者每次调用别人提供的函数，都要去查一下这个函数返回的对象是在堆上还是栈上，这就很离谱。
     *       所以这种方案不推荐，除非返回的数组是全局变量或类的成员。
     *
     *  下面这个函数，表面上参数是arr[]，看起来是一个数组，实际上编译器把它转成指针。用sizeof一试便知。
     *  而返回类型如果写成int[],编译器直接报错。
     */
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
        //cout << "返回值是函数中的局部变量的引用，局部变量在函数调用结束后自动释放，因此函数不应该这样写：" << retB() << endl;

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
