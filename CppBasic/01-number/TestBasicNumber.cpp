//climits头文件（原 limits.h）定义了数值极限的常量，如：CHAR_BIT、CHAR_MIN、INT_MAX、LONG_MIN等
#include <climits>
#include <iostream>


using namespace std;

namespace BasicNumber {
    //不同数据类型，占用内存字节
    //这是机器相关的，不同机器上长度不一定一样。
    void sizeofType() {
        cout << "In this machine:" << endl;
        cout << "bool字节" << sizeof(bool) << endl;
        cout << "char字节" << sizeof(char) << endl;
        cout << "wchar_t字节" << sizeof(wchar_t) << endl;

        cout << "整形:" << endl;
        cout << "short int字节" << sizeof(short int) << ",same as short:" << sizeof(short) << endl;//short int简写为short
        cout << "int字节" << sizeof(int) << endl;
        cout << "unsigned字节" << sizeof(unsigned) << endl;//unsigned int简写为unsigned
        cout << "long int字节" << sizeof(long int) << ",same as long:" << sizeof(long) << endl;//long int简写为long
        cout << "long long int字节" << sizeof(long long int) << ",same as long long:" << sizeof(long long)
             << endl;//long long int简写为long long
        cout<<"总结：现代家用PC基本都是64位，int占4个字节，long也是4个字节，long long是8字节，short占2字节\n"<<endl;

        cout << "浮点型:" << endl;
        cout << "float字节" << sizeof(float) << endl;//C++要求float至少32位
        cout << "double字节" << sizeof(double) << endl;//double至少48位且不少于float
        cout << "long double字节" << sizeof(long double) << endl;
        // sizeof(void);不能用于void

        cout << "指针:" << endl;
        cout << "char*字节" << sizeof(char*) << endl;
        cout << "void*字节" << sizeof(void*) << endl;//前面说sizeof不能用于void，但是void*是指针
        const char* const str = "abcdefghijklmnopqrstuvwxyz";
        cout << "str类型是char*,字节" << sizeof(str) << endl;
        char str2[] = {'a','b','c','c','\0','e','f'};
        cout << "str2类型是char[]是数组,长度为："<< sizeof(str2) <<",字符串以'\\0'结束：str2="<<str2<<endl;
        cout << "abcd字节" << sizeof("abcd") << ",因为末尾有个\\0"<<endl;//

        char *pstr = new char[10];
        cout << "pstr size:" << sizeof(pstr) << endl;//8
        cout << "*pstr size即一个char的size:" << sizeof(*pstr) << endl;//1
        delete[] pstr;
    }

    //表示范围
    void rangeOfNumber() {
        cout << "Numbers in this machine:" << endl;
        cout << "char bit： " << CHAR_BIT << endl;//一个char占8位

        cout << "char范围" << CHAR_MIN << "~" << CHAR_MAX << endl;//int就是signed int，但是char比较奇怪，可能是signed也可能是unsigned，取决于编译器，可以通过CHAR_MIN判断
        cout << "unsigned char范围" << 0 << "~" << UCHAR_MAX << endl;
        cout << "signed char范围" << SCHAR_MIN << "~" << SCHAR_MAX << endl;

        cout << "整形:" << endl;
        cout << "int范围" << INT_MIN << "~" << INT_MAX << endl;
        cout << "short int范围" << SHRT_MIN << "~" << SHRT_MAX << endl;
        cout << "unsigned long long int范围" << 0 << "~" << ULLONG_MAX << endl;
    }

    //字面量
    void literals() {
        cout<<"\n字面量\n";
        cout << "sizeof 'a'=" << sizeof 'a' << endl;//输出1。据说在C语言中字符型变量被看成是int型，这里会输出4
        //不加任何后缀一般编译器当做int，但是下面这个数太大，无法用int表示，所以实际存储为long long
        cout << 4294967297 << "占用" << sizeof 4294967297 << "字节" << endl;
        cout << 2147483648 << "占用" << sizeof(2147483648) << "字节" << endl;//int无法表示，实际是unsigned int

        //所有加号前后都是无符号int，故结果也是，发生溢出截取尾32位，结果还是无符号int
        cout << (2147483648 + 2147483649 + 2147483649) << "占用" << sizeof(2147483648 + 2147483649 + 2147483649)
             << "字节,结果是" << (2147483648 + 2147483649 + 2147483649) << endl;
        //-8是负数，内存中是 11111111111111111111111111111000，但是加后缀U表示无符号，所以编译时输出一个警告，然后转为无符号数，将输出4,294,967,288，即2^32-8
        cout << "后缀U或u表示unsigned：" << -8U << endl;

        //后缀ULL，明确指明类型为unsigned long long int
        cout << "0ULL" << "占用" << sizeof 0ULL << endl;

        cout << hex << "16进制表示10：" << 10 << ",8进制表示10：" << oct << 10 << dec << ",10进制表示10:" << 10 << endl;

        cout << "前缀L表示宽字符： sizeof(L'a')=" << sizeof(L'a') << endl;
        wchar_t tt = L'我';//wchar_t不能和unsigned和signed搭配
        cout << "我" << tt << endl;//cin和cout将输入输出看作char流，所以wchar_t不能用cout。
        wcout << L'我' << endl;//宽字符存在编码问题，可能这里无法正常输出‘我’，需要配置std::locale

        cout << "sizeof 1.0f: " << sizeof 1.0f << endl;//float
        cout << "sizeof 1.0: " << sizeof 1.0 << endl;//double
        cout << "sizeof 2.3E5F: " << sizeof 2.3E5F << ",val:" << 2.3E5F << endl;//float,2.3*10^5

    }

    //类型转换
    void typeCast() {
        cout << "\n非0整数转bool再转回整形一定是1: " << (int) ((bool) -1) << endl;

        //------有符号无符号互转
        unsigned int aa = UINT_MAX;//内存中是111111...11111111
        int ab = aa;//对于ab，内存中还是111111...11111111，只是识别为signed int
        cout << aa << "  " << ab << endl;

        aa = INT_MAX + 1;//溢出,编译器给出警告
        ab = aa;
        cout << aa << "  " << ab << endl;
        //------有符号无符号互转END

        //位数较长的类型强转为位数较短的类型
        long long ba = LLONG_MAX;
        int bb = int(ba);//或者(int)ba
        cout << ba << "  " << bb << endl;
        cout << "----总结类型转换的规律，是保持内存中的数据不变，用对应的类型来解释，位数不够则截取低位数" << endl;

        //bool,char,unsigned char,signed char,short总是先转成int再计算，哪怕表达式中没有int
        short ca = 1, cb = 2;
        bool cc = true;//表达式中值为1
        short cd = (ca + cb + cc);//再将结果int转成short
        cout << cd << endl;//


        //有符号数与无符号数相加
        int i = -42;
        unsigned u = 10;
        cout << i + u << endl;//有符号数先变成无符号数再相加，输出4294967264

        //两个无符号数相减
        unsigned u1 = 10, u2 = 42;
        cout << u1 - u2
             << endl;//输出4294967264,结合内存模型，很容易理解。先减10变成0000....00000，再减一位变成1111111.....1111111,也就是4,294,967,295，再减31就是4294967264



    }

    void testexpression() {
        int x = 10;
        //C++不能保证x在每个子表达式计算后递增还是整个表达式计算完毕后递增两次，所以应该避免这样写
        //可能输出20也可能输出21，取决于编译器
        cout << (x++) + (x++) << " " << x << endl;

        char word[] = "hello";
        cout << (word == "hello") << endl;//数组名是地址，字符串常量也是地址，这里比较的是地址是否相同，输出0。应该使用strcmp比较C风格的字符串是否相等
    }
    /**
     * 判断大小端模式
     */
    void testBigEndian() {
        cout<<"testBigEndian"<<endl;
        int a = 0x12345678;
        char *c = (char*)&a;
        if(c[0] == 0x78){
            cout<<"小端模式"<<endl;
        }else if(c[0]== 0x12){
            cout<<"大端模式"<<endl;
        }
    }


    int main() {
        sizeofType();
        cout << endl;
        rangeOfNumber();
        literals();
        typeCast();

        testexpression();

        testBigEndian();

        return 0;
    }
}