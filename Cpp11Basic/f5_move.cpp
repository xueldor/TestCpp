#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

namespace f5 {

    class Test
    {
    public:
        Test(){
            p_arr = new int[10];
            std::cout << "Constructor" << std::endl;
        };
        Test(const Test &test) //拷贝构造函数
        {
            std::cout << "copy Constructor" << std::endl;
            p_arr = new int[10];
            memcpy(p_arr, test.p_arr, 10*sizeof(int));
        }
        Test(Test &&test) //移动构造函数
        {
            std::cout << "Move Constructor" << std::endl;
            p_arr=test.p_arr;
            test.p_arr = nullptr; //修改参数的资源
        }
        ~Test(){
            if(p_arr != NULL){
                delete [] p_arr;
            }
        }
        Test &operator=(Test &&test) //移动赋值操作符
        {
            std::cout << "Move Assignment operator" << std::endl;
            if (this != &test)
            {
                p_arr = test.p_arr;
                test.p_arr= nullptr; //修改参数资源
            }
            return *this;
        }
        Test &operator=(const Test &test) //拷贝赋值操作符
        {
            std::cout << "Assignment operator" << std::endl;
            if (this != &test)
            {
                if(p_arr == NULL) {
                    p_arr = new int[10];
                }
                memcpy(p_arr, test.p_arr, 10 * sizeof(int));
            }
            return *this;
        }

    private:
        int *p_arr;
    };

    void test(int& i){
        cout<<"左值引用"<<endl;
    }
    void test(const int& i){
        cout<<"左值引用,const"<<endl;
    }
    void test(int&& i){
        cout<<"右值引用"<<endl;
    }
    void test(const int&& i){
        cout<<"右值引用,const"<<endl;
    }

    void addToList(Test&& t){
        cout<<"addToList, move "<<&t<<endl;
    }
    void addToList(Test& t){
        cout<<"addToList, copy "<<&t<<endl;
    }

    void main() {
        Test t1;
        Test t2((Test()));//加一个括号，防止被编译器理解为函数声明
        Test t3 = Test();
        cout<<"---以上调用的是无参构造函数，而不是拷贝或移动构造。也许是编译器做了手脚"<<endl;

        t2 = t1;//赋值
        t2 = Test();//移动赋值
        addToList(t1);//拷贝的方式添加到数组里
        addToList(std::move(t1));//移动的方式添加到数组里,当然addToList里面还需要正确的实现，否则还是会可能会发生拷贝
        addToList(Test());//移动的方式添加到数组里

        std::vector<Test> vec;
        vec.push_back(t1);
        vec.push_back(std::move(t2));//后面不得再使用t2
    }
}