#include <iostream>
#include <string>

using namespace std;

/**
 * C语言没有字符串类型，用char数组表示字符串，用\0表示字符串的结束
 * C++当然支持C语言风格的字符串，另外以标准库的方法提供了string类。
 */
void teststring(){
    string str1;
    string str2 = "Tom";
    //数组不能赋值，string对象可以，因为C++中对象和结构可以直接赋值，内存中的对象会拷贝一份。不过要说的是，string内部
    str1 = str2;
    cout<<str1<<endl;

    str2+=" is stupid";//拼接
    cout<<str2<<endl;

    char hungry[] = " hungry boy";
    str1 += hungry;//与C风格字符串拼接
    cout<<str1<<endl;

    str1 = hungry;//C风格字符串赋值给string对象
    cout<<str1<<endl;

    const char* tom = str2.c_str();//string转C风格字符串
    cout<<tom<<endl;
}
void testString2(){
    string str = "a";
    string str2 = "abcdefghijklmnopqrstuvwxyz";
    string str3 = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz";
    cout<<"size of str="<<sizeof str<<endl;
    cout<<"size of str2="<<sizeof str2<<endl;
    cout<<"size of str3="<<sizeof str3<<endl;
    //----输出都是32，于是我们判断 1)要么string类内部持有的char*，长度较小时（一定小于32），分配在栈上，长了以后一定会分配到堆上面；
    //2） 要么string类内部的char*全是在堆上，append时丢弃原来的内存重新分配
    cout<<"str 的内存 "<<&str<<endl;
    str += "bc";
    str.append("de");
    cout<<"str 的内存 "<<&str<<endl;//内存地址不变

    //既然string类内部的字符串内容是在堆上，用指针指向它，就有个问题，拷贝时是浅拷贝还是深拷贝
    string str_clone = str;//这里发生了拷贝，string类是否只拷贝了指针？
    cout<<"str content address " <<(void*)(str.c_str())<<endl;
    cout<<"str_clone content address " <<(void*)str_clone.c_str()<<endl;
    //----打印的地址是一样的，似乎只拷贝了指针，即str_clone和str内部指向同一个char*。但者不符合常理。

    string str_clone2 = str;
    cout<<"str char address " <<(void*)(str.c_str())<<endl;//0xa6209ff620,和上面一样
    cout<<"str_clone2 char address " <<(void*)str_clone2.c_str()<<endl;//0xa6209ff5a0
    str_clone2.append("ef");
    cout<<"str_clone2 content address " <<(void*)str_clone2.c_str()<<endl;//0xa6209ff5a0
    //----我们发现，只要对str_clone2进行了修改，地址就变了，这说明string内部采用了 "copy on write"，提高了性能

    string str_test;
    {
        string str_org = "a";
        str_test = str_org;
        //此时两者内部指针指向同一个地址的字符数组，那么局部语句块结束后，str_org的析构函数是否会delete内存？导致外面的str_test不可用？
    }
    cout<<"str_test "<<str_test<<endl;//c++会妥善处理这些问题。应该内部有个引用计数，计数清零才delete。

}
void testString3(){
    cout<<"\ntestString3----"<<endl;
    char * p = new char[10];
    p[0] = 'a';
    p[1] = 'a';
    p[2] = 'a';
    p[3] = 'a';
    p[4] = 'a';
    p[5] = '\0';

    string str = p;//用初始化str
    p[1] = 'b';//修改p
    cout<<"str="<<str<<", p="<<p<<endl;//str和p不相等，所以str内部绝不会简单持有p指针。也就是，str = p发生了拷贝
    str = p;
    cout<<"str="<<str<<", p="<<p<<endl;

    delete[]p;
    p = nullptr;
}
int main_string(){
    teststring();
    testString2();
    testString3();
    return 0;
}