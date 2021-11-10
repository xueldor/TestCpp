#include <iostream>
using namespace std;

namespace TestBit {
//位操作符有六个：<<,>>,~,&,|,^
    void testbit() {
        int aa = 1;
        cout << (aa << 2) << endl;//舍弃高位，低位补0

        int bb = -256;
        cout << (bb >> 2) << endl;//对于有符号数，低位舍弃，高位补符号位，称为算数右移

        unsigned cc = 0xFFFFFFFF;
        cout << (cc >> 2) << "   " << hex << (cc >> 2) << dec << endl;//对于无符号数，低位舍弃，高位补0，称为逻辑右移

        int dd = 1;
        cout << "按位取反 " << (~dd) << endl;//按位取反
        cout << "逻辑非 " << (!!dd) << endl;//非操作符将true转成false，false转成true

        cout << (aa & bb) << endl;//位与
        cout << (aa | bb) << endl;//位或
        cout << (aa ^ bb) << endl;//异或
    }


/**
 * 循环左移byte
 */
    unsigned char rolByte(unsigned char val, int size) {
        unsigned char res = val << size;
        res |= val >> (sizeof(val) * 8 - size);
        return res;
    }

/*循环右移字节*/
    unsigned char rorByte(unsigned char val, int size) {
        unsigned char res = val >> size;
        res |= val << (sizeof(val) * 8 - size);
        return res;
    }


/**
 * 循环左移int
 */
    int rolInt(int val, int size) {
        int res = val << size;
        res |= ((unsigned) val) >> (sizeof(val) * 8 - size);
        return res;
    }

/*循环右移int*/
    int rorInt(int val, int size) {
        int res = ((unsigned) val) >> size;
        res |= val << (sizeof(val) * 8 - size);
        return res;
    }


    int main() {
        testbit();

        cout << "一字节循环左移 " << (int) rolByte((char) 129, 1) << endl;//10000001->00000011,输出3
        cout << "一字节循环右移 " << (int) rorByte((char) 129, 1) << endl;//10000001->11000000,输出192
        cout << "int循环右移 " << (int) rorInt(0x80000000, 1)
             << endl;//10000000000000000000000000000000->01000000000000000000000000000000,输出1,073,741,824
        cout << "int循环左移 " << (int) rolInt(0x80000001, 1)
             << endl;//如果此机器int是32位，10000000000000000000000000000001->00000000000000000000000000000011,输出3

        return 0;
    }
}