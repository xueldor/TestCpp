#include <iostream>
//cctype是字符处理库
#include <cctype>
using namespace std;
namespace TestChar {
    void testFunc() {
        char ch = 'A';
        cout << "is 'A' Alphabet : " << isalpha(ch) << endl;//是不是字母

        cout << "is '5' Alphabet : " << isalpha('5') << endl;//返回0，即false
        cout << "is '5' digit : " << isdigit('5') << endl;//是不是数字

        cout << "is '5' punctuation : " << ispunct('5') << endl;//是不是标点符号
        cout << "is '.' punctuation : " << ispunct('.') << endl;//是不是标点符号

        cout << "'A' to lower " << (char) tolower('A') << endl;//转小写
    }

    int main() {
        testFunc();

        return 0;
    }
}