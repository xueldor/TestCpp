#include <iostream>
using namespace std;

class WrapArray{
public:
    int arr[10];
    int* pArr;
};
void tryCopyArray(){
    int a[] = {1,2,3};
    //数组与数组之间不能直接赋值：
//    int b[] = a;

    //因为数组名可视作地址，故可以赋给指针。但这不是数组的拷贝，因为指针指向原来的空间，并没有发生数组内存的复制。
    int *pa = a;


    WrapArray wrapArray {
        .arr = {1 ,2,3,4,5,6,7,8,9,0}
    };
    wrapArray.pArr = wrapArray.arr;

    cout<<"arr address=" <<wrapArray.arr<<",pArr="<<wrapArray.pArr<<endl;

    //类对象可以直接赋值。从打印结果看，类里面包着一个数组的话，数组也发生了复制。当然了，指针成员拷贝的是指针的值（即地址），而不是指向的空间
    //从对象内存看，int arr[10]使WrapArray的对象增大sizeof(int)*10, 而pArr只占用一个地址的大小。所有，虽然数组名是地址，但数组类型和指针类型是不一样的。
    WrapArray wrapArray2 = wrapArray;
    cout<<"wrapArray2 arr address=" <<wrapArray2.arr<<",pArr="<<wrapArray2.pArr<<endl;

    cout<<"wrapArray.arr==wrapArray2.arr？ "<<(wrapArray.arr==wrapArray2.arr?"true":"false" )<<"\nwrapArray.pArr==wrapArray2.pArr？ " <<(wrapArray.pArr==wrapArray2.pArr ? "true":"false")<<endl;
}
//演示拷贝数组的几种方法
void copyArray(){
    int a[] = {1,2,3, 4, 5};

    //方法一，循环赋值
    int b[5];
    for(int i = 0; i < 5; i++){
        b[i] = a[i];
    }

    //方法二，用memcpy
    int c[5];
    memcpy(c, a, sizeof a);
    cout<<"c[4]="<<c[4]<<endl;
}
int main_test_arr_copy(){
    tryCopyArray();
    copyArray();
}