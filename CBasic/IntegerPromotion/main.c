#include <stdio.h>

void compareInt() {
    signed int a = -1;
    unsigned int b = a;
    printf("a=%d,b=%u  ;", a, b);

    if(a == b)
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
    printf("a=%d,b=%u  ;", a, b);

    if(a == b)
        printf("a==b");
    else if(a<b)
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
    else
        printf("a>b");
    printf("\n");
}
int main() {
    compareInt();//a==b
    compareChar();//a<b
    compareInt2();//a>b
    return 0;
}
