/**
* 演示using的几种用法
*/
#include <iostream>
#include <map>
//1. 使用名称空间
using namespace std;
//-----更多这方面用法见testnamespace.cpp

//2. (C++11)使用别名，using 类型别名=原类型
using uint=unsigned int;//语义上和typedef是等价的
uint aa = 2;//unsigned int aa=2;

//定义函数指针别名方面，using比typedef可读性更好
typedef void (*func_t_typedef)(int, int);
using func_t_using = void (*)(int, int);

//涉及到模板时，typedef有一定局限性
typedef std::map<std::string, int> map_int_t;
typedef std::map<std::string, std::string> map_str_t;
//其实我就是希望，map的key是std::string ，value可能是int，也可能是其它类型，但是我不得不为每个可能的value类型都用typedef说明一下

//为了解决，C++98/03 中往往不得不在外面包一层类：
template <typename Val>
struct str_map
{
    typedef std::map<std::string, Val> type;
};
str_map<int>::type map1;//map1即 std::map<std::string, int>
str_map<std::string>::type map2;//map2即 std::map<std::string, std::string>

//上面这样写很繁琐，C++11出现了可以重定义一个模板的语法：
template <typename Val>
using str_map_t = std::map<std::string, Val>;
str_map_t<int> map3;
str_map_t<std::string> map4;


/* C++98/03的传统写法，要在外面包一层*/
template <typename T>
struct func_t
{
    typedef void (*type)(T, T);
};
// 使用 func_t 模板
func_t<int>::type xx_1;
/* C++11 */
template <typename T>
using func_t2 = void (*)(T, T);
// 使用 func_t2 模板
func_t2<int> xx_2;
//----------------比 typedef 更简洁和清晰


//3.采用私有方式继承一个类，父类的public和protected成员在子类是不可见的，可以用using来重新声明，令其可见
//(注意)这种方法不能用来使父类的private成员可见。即，原本父类是public的，因为私有继承变得不可见，用这种方法使的个别成员重新可见。
class Basic{
public:
    int a;
    int b;
};
class Bulk : private Basic {
public:
    using Basic::a;
protected:
    using Basic::b;
};

//4. 当子类重载了父类的某个成员函数（注意说的是重载，不是重写），即,子类的某个函数，与父类的某个函数，同名，但参数不一样，那么父类的同名函数被隐藏
//子类要想包含这个函数，需要重写父类的所有重载版本。可以用一个using指令解决
class Father {
public:
    void test(){cout<<"father test"<<endl;}
    void test(std::string s){cout<<"father test "<<s<<endl;}
};
class Child : public Father {
public:
    //如果没有test(int)这个函数，父类的test函数就是可见的，但是子类有了test，且参数不一样，父类的test函数就不可见了。
    void test(int a){
        cout<<"test a="<<a<<endl;
    }
    //过去，需要将父类的test函数一起重写
    void test(){
        Father::test();//调用父类的test
    }
    void test(std::string s){
        Father::test(s);//调用父类的test
    }
    //把上面两个重写的父类的test函数注释掉，只需一个using
    using Father::test;
};

//5. 简化子类构造函数写法
class ATest {
public:
    ATest(int a,int b, int c){};
};
class BTest: ATest {
public:
    //BTest的构造函数并没有添加函数，只是调用父类。那么可以using直接导入A的构造函数
    BTest(int a,int b, int c): ATest(a, b, c){};
    //将上面一行注释，只使用下面的using即可
    using ATest::ATest;
};

void test_using(){
    Child cc;
    cc.test();
    cc.test(1);
    cc.test("ss");

    BTest(1,2,3);
}