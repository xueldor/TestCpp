#include <stdio.h>

/**
 * 测试隐式转换
 */
void compareInt() {
    signed int a = -1;
    unsigned int b = a; // -1转无符号为4294967295
    printf("a=%d,b=%u  ;", a, b);

    if(a == b) // 无符号数与有符号数比较时，隐含将有符号数转化为无符号数,故相当
        printf("a==b");
    else if(a<b)
        printf("a<b");
    else
        printf("a>b");
    printf("\n");
}
void compareChar() {
    signed char a = -1;
    unsigned char b = a;
    printf("a=%d,b=%u  ;", a, b);//a=-1,b=255

    if(a == b)
        printf("a==b");
    else if(a<b) //signed char和unsigned char提升为int类型,a=-1,b=255,故a<b
        printf("a<b");
    else
        printf("a>b");
    printf("\n");
}
void compareInt2() {
    signed int a = -1;
    unsigned int b = 1;
    printf("a=%d,b=%u  ;", a, b);

    if(a == b)
        printf("a==b");
    else if(a<b)
        printf("a<b");
    else // -1转无符号为4294967295, 显然a>b
        printf("a>b");
    printf("\n");
}
int main() {
    compareInt();//a==b
    compareChar();//a<b
    compareInt2();//a>b
    return 0;
}
