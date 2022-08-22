#include <iostream>
using namespace std;

namespace TestPoint {
    void testpoint() {
//wrong,不能对常量取地址 :  int *ps = &8;
        int ii = 9;
//wrong    cout<<&(ii+1)<<endl;
        &(ii + 1, ii);

        const int a = 6;
        cout << &a << endl;//OK

        int *pa = 0;//NULL
        delete pa;//OK
        delete pa;//OK,空地址用delete总是安全的


        int *pt = (int *) 0xB8000000U;//地址本质是int，C99标准之前的C语言可以直接赋值，C++中必须强转。
        long long val = (long long) pt;//我的当前环境long是32为，64位机，故用long long。


        int *pb = new int;
        cout << "指针自身长度：" << sizeof pb << endl;
        cout << "指针指向数据的长度：" << sizeof *pb << endl;
        delete pb;
//wrong ,不能delete两次	：  delete pb;

        int arr1[5];
        cout << "静态数组可以用sizeof求大小：" << sizeof arr1 / sizeof arr1[0] << endl;;

        int *arr2 = new int[5];
        cout << "但是动态分配的数组不能：" << sizeof arr2 << " ,这是指针的长度，比如64位地址输出8" << endl;

        cout << "指针+1，指针值增加指向的类型的字节数：" << *(arr2 + 1) << endl;

        //int数组，应该输出一个sizeof(int)
        cout << "指针+1，指针值增加指向的类型的字节数,(long long)(arr2+1)-(long long)arr2 = " << (long long) (arr2 + 1) - (long long) arr2 << endl;

        int *pt1 = (int *) 0xB8000000U;
        int *pt2 = (int *) 0xB8000004U;
        cout << "指针减，等于地址的差除以类型大小： " << pt2 - pt1 << endl;//输出1

        delete[]arr2;

    }

    void testconstPoint(const int *param) {//指针参数一般应尽量声明为常量

        const float g = 9.8f;
        const float *pg = &g;
//wrong,*pg is const。	*pg = 9.9f;

        float e = 2.7f, pi = 3.14f;
        float *const ph = &e;
//wrong,ph is const。	ph = &pi;

        float *pf = const_cast<float *>(pg);//去除const
        *pf = 11.0f;
        cout << *pf << endl;
    }

    void testref() {
        //从语法定义角度看，引用相当于别名，d和d_at无论是值还是地址都一样
        int d = 56;
        int &d_at = d;//必须在声明时初始化
        cout << d << "  " << d_at << "  " << &d << "  " << &d_at << endl;

        //从编译器角度，引用的实现只是基于指针的代码的另一个接口，*pd相当于d_at,pd相当于&d_at
        int *const pd = &d;//引用接近const指针
        cout << d << "  " << *pd << "  " << &d << "  " << pd << endl;


        const int aaa = 99;
        const int &bbb = aaa;//OK
    }

    int main() {
        testpoint();
        int a = 10;
        testconstPoint(&a);
        testref();

        return 0;
    }
}