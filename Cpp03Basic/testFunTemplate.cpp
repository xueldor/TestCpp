#include <iostream>
#include <string>
#include "a.h"
using namespace std;
namespace TestFunTemplate {
//-------
//声明
    template<typename T>
    void Swaptemplate(T &a, T &b);//当然由于下面紧跟的就是实现，所以这里其实是不需要的。只是演示语法。

//实现
//函数模板本身不会生成函数定义，只是提供一个方案，由编译器根据代码生成定义
    template<class T>
    //same as template<typename AnyType>,除非需要考虑向后兼容，否则应该尽量使用typename
    void Swaptemplate(T &a, T &b) {
        cout << "我是模板Swaptemplate(T &a,T &b)" << endl;
        T tmp = a;
        a = b;
        b = tmp;
    }

//重载的模板
    template<typename T>
    void Swaptemplate(T a[], T b[], int n) {
        cout << "我是模板Swaptemplate(T &a,T &b,int n)" << endl;
        T tmp;
        for (int i = 0; i < n; i++) {
            tmp = a[i];
            a[i] = b[i];
            b[i] = tmp;
        }
    }
//--------end
//1. 隐式实例化(implicit instantiation)： 编译期间，当有代码调用时，编译器自动根据传入的参数类型，从模板生成函数定义.见 tag 1

//2. 显式实例化(explicit instantiation)： 通过下面的声明，明确要求编译器根据模板生成函数定义
    template void Swaptemplate<long>(long &, long &);//template后面没有<>,表示显式实例化，编译器从模板生成实现，所以后面不需要函数定义，这点区别于显式具体化
    template void Swaptemplate<float>(float &, float &);
//既然可以隐式实例化，那为什么还需要显式实例化呢？请打开a.h 和a.cpp ,为了隐藏逻辑，我将foo的实现放在a.cpp里，a.h中只有声明，那么必须在a.cpp里面显式实例化，才能调用，否则该函数不存在(无法解析的外部符号)。
//也就是说，隐式实例化只能自动生成本文件的或者被include到本文件的模板函数。假设你写的是一个库，打包后给别人用，那么必须显式实例化。

//普通的函数声明，跟模板无关，但是非模板的声明，优先级比显式实例化的声明高，所以下面要注释掉，否则将调用非模板版本
//void Swaptemplate(long,long);

//3. 显式特殊化（显式专用化、显式具体化）（explicit specialization） : 有的时候，对于某个类型，模板函数中的逻辑不适用，希望针对这种类型专门实现一套逻辑。
    template<>
    void Swaptemplate(string &a, string &b);//声明。当然由于下面紧跟的就是实现，所以这里其实是不需要的。只是演示语法。
    template<>
    void Swaptemplate(string &a, string &b) {//实现
        cout << "我是模板Swaptemplate的特例话" << endl;
    }

    //N 是非类型模板形参,只有整形，指针和引用才能作为非类型形参，而且绑定到该形参的实参必须是常量表达式，即编译期就能确认结果。
    template <class T, size_t N> void array_init(T (&parm)[N])
    {
        cout<<"value of N is "<<N<<endl;
//        N = 9;//wrong，N在编译期间就确定了，不是变量，不能赋值
        for (size_t i = 0; i != N; ++i) {
            parm[i] = 0;
        }
    }



    //模板的知识可以参考 https://qixinbo.info/2017/07/09/cplusplus-template/
    int main() {
        int s1 = 2, s2 = 3;
        //隐式实例化
        Swaptemplate(s1, s2);//tag 1

        long s3 = 2, s4 = 3;
        Swaptemplate(s3, s4);

        int a = 1;
        foo(a);

        string aStr = "aa";
        string bStr = "bb";
        Swaptemplate(aStr, bStr);

        //显式模板实参：适用于函数模板，即在调用函数时显式指定要调用的实参的类型
        cout << "显式模板实参:" << endl;
        //Swaptemplate<short>(s1,s2);明确指定模板代表的类型是short。这里会报错：不能将参数 1 从“int”转换为“short &”
        Swaptemplate<short>((short &) s1, (short &) s2);



        //如果声明了void change(int a[],int b[],int n);则优先调用非模板版本
        //否则如果声明了template<> void change(int a[],int b[],int n);则调用模板特例话的版本
        //否则调用模板函数。下面的代码演示

        int arr1[] = {1, 2, 3};
        int arr2[] = {4, 5, 6};
        void callChange(int arr1[], int arr2[], int len);
        callChange(arr1, arr2, 3);


        void callChange();
        void callChange2();//先声明

        callChange();
        callChange2();

        int x[42],y[10];
        array_init(x);
        array_init(y);

        return 0;
    }


//-----------demo2 start

//要先声明模板原型，然后才能声明template<> void change(int a[],int b[],int n)
    template<typename AnyType>
    void change(AnyType a[], AnyType b[], int n);

    void callChange(int arr1[], int arr2[], int len) {
        {
            //声明放在代码块里面，不影响外面。但是模板不能在方法体内声明
            void change(int a[], int b[], int n);//在方法体内声明。如果拿到外面，作用范围变大会影响后面的代码

            change(arr1, arr2, len);//调用没有模板的版本

            //非模板的声明是int[]类型，下面的long[]类型，那么是否就应该调用模板的实现版本呢？实践表明还是会调用非模板实现，然后编译报错，long[]无法转换为int[]
            long arr3[] = {1, 2, 3};
            long arr4[] = {4, 5, 6};
            //change(arr1,arr4,3);//long[]无法转换为int[]

        }
        int arr3[] = {1, 2, 3};
        int arr4[] = {4, 5, 6};
        //change(arr1,arr4,3);//这里调用的就是模板的实现版本了。不过执行这行会产生一个AnyType为int的函数实现，而后面又有一个int类型的特例化，所以这里注释掉。毕竟不能有两个一模一样的函数。
        //也就是说，同一个编程单元，同一个函数原型，同一种类型，不能一起使用显式具体化和显式实例

        long arr5[] = {1, 2, 3};
        long arr6[] = {4, 5, 6};
        change(arr5, arr6, 3);//调用模板的实现版本
    }

//特例化的change方法声明
    template<>
    void change(int a[], int b[], int n);

    void callChange() {
        int arr1[] = {1, 2, 3};
        int arr2[] = {4, 5, 6};
        change(arr1, arr2, 3);//前面的声明是特例话，所以这里调用的特例话版本，(见tag 2)
    }

    void change(int a[], int b[], int n);//声明非模板的change方法
    template<>
    void change(int a[], int b[], int n);//声明特例化的change方法
    void callChange2() {
        int arr1[] = {1, 2, 3};
        int arr2[] = {4, 5, 6};
        change(arr1, arr2, 3);//前面同时声明了非模板和模板，显然优先调用非模板版本
    }


//-------------下面是三个几乎一样的方法，那么main函数里调用哪个方法取决于，前面的声明是哪个版本。如果声明了多个，那么非模板版本是优先级最高的。
//模板
    template<typename AnyType>
    void change(AnyType a[], AnyType b[], int n) {
        cout << "call change template" << endl;
        AnyType tmp;
        for (int i = 0; i < n; i++) {
            tmp = a[i];
            a[i] = b[i];
            b[i] = tmp;
        }
    }

//针对int类型特例话
    template<>
    void change(int a[], int b[], int n) {//tag 2
        cout << "call change template specialization" << endl;
        int tmp;
        for (int i = 0; i < n; i++) {
            tmp = a[i];
            a[i] = b[i];
            b[i] = tmp;
        }
    }

//非模板版本
    void change(int a[], int b[], int n) {
        cout << "call change no template" << endl;
        int tmp;
        for (int i = 0; i < n; i++) {
            tmp = a[i];
            a[i] = b[i];
            b[i] = tmp;
        }

    }
//--------------------------------

}