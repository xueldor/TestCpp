#include <stdio.h>

void testPrintf1() {
    // \n: 新行
    printf("a\nb\n");
    // \r: 回车换行
    printf("c\rd\n");
    // \t: 水平制表符
    printf("e\tf\n");

    // \NNN: 一个包含一个到三个数字，使用八进制值表示的特殊字节
    printf("abc\0def");// \0是空字符，C语言用作字符串的结尾标志。后面的def不输出。
    printf("\n");
    printf("hij\11klm\n");// \11,八进制的11等于9，表示tab符号，即‘\t’。
    printf("\141\n");// \141, 八进制141等于十进制97，对应字母'a'

    // \xhh，hh表示1到2位16进制代表的数
    printf("\x61\n");// 十六进制61等于十进制97，表示字母'a'

    //当printf的内容太长时
    printf("GOGOGOGOGOGOGOGOOGOGOG"
           "OGOGOGOGOGOGOGOGOGOGOGOGO....\n");//放心中间不会产生空格
}
//各种类型的输出
void testPrintf2() {
    //%c 一个字符
    char c='A';
    printf("%c\n",c);

    int a=12;
    //%d 有符号十进制整数
    printf("%d\n",a);
    printf("%i\n",a);//%i same as %d
    //%o 有符号八进制整数
    printf("0%o\n",a);//014, 12==014
    //%x 无符号十六进制整数
    //%X 同%x,只是转成string后ABCDEF等数字采用大写
    printf("hex A is %x %X %x\n",0XA, 10, a);//hex A is a A c
    //%u 无符号十进制整数
    printf("%u sizeof(int)=%d\n",-1, sizeof(int));//4294967295,把-1补码表示，然后翻译成无符号整数。其实就是FFFFFFFF。注意当前机器int是4字节。
    //"%ld" l表示long，d表示按照十进制有符号整数的方式转换;同理，有”%lx“ ”%lo“，把后面的long类型数字，转换成十六进制或八进制
    printf("%x %lx\n", 0x1234FFFFFF, 0x1234FFFFFF);//34ffffff 1234ffffff,可以看出，%x只能输出long int的低4位，%lx才能完整输出
    //"%lu" unsigned long int
    printf("%lu %lu %lu sizeof(long)=%d\n",-1, (long)-1, -1L, sizeof(long));//4294967295 18446744073709551615 18446744073709551615 sizeof(long)=8
    //ll 和整数转换说明符一起使用，表示一个long long;示例："%llu" "%lld"
    printf("%llu %llu %llu sizeof(long long)=%d\n",-1, (long long)-1, -1L, sizeof(long long));//4294967295 18446744073709551615 18446744073709551615 sizeof(long long)=8


    //%f 浮点数、十进制记数法
    float b=31.415;
    printf("%f\n",b);//31.415001,发现末尾会多个001。因为浮点数无法精确的表示31.415。因此转string时需要指定长度和精度
    printf("%7.2f\n",b);//"  31.42",7.2表示，总长度是7（包括小数点），小数点后2位。因为31.42只有5位，前面补两个空格。
    printf("%07.2f\n",b);//0031.42,前面补0。注意只能补0，不好补其它字符
    printf("%.30f\n",b);//31.415000915527343750000000000000,后面加0凑足30个小数位
    printf("%0.2f %1.2f %.2f\n", b, b, b);//31.42 31.42 31.42。可知不会截断前面的整数部分
    //double用lf表示
    //----所以如果没有前面补0的需求，直接写%.nf即可

    //%p 指针
    printf("%p %p\n", a, &a);//0xc 0x7ffee5c4b6e0。打印指针指向的地址值，其实就是0x十六进制格式打印长整形
    //%s 字符串
    printf("%s\n", "hahahaha");
    char* ss = "hehehe\0hehe";
    printf("%s\n", ss);
    //遗留一个问题是，如果需要输出%本身，怎么办
    printf("%%\n");//标准的方法是%%。也许其它不正规方式也能输出%，比如\%,"%\n",\x25等，但是要么古怪，要么不受控制，总之不这么写


    //%e %E 浮点数、e-记数法,即科学计数法
    printf("%e\n",31.4);//3.140000e+01
    printf("%E\n",31.4);//3.140000E+01
    //%g(%G) 根据数值不同自动选择%f或%e(%E)。%e格式在指数小于-4或者大于精度时使用
    printf("%G\n",3.1415926);


    //以下几乎用不到，不需要了解
    //%a %A 浮点数、十六进制数字和p-计数法（c99）
    //意思就是，把一个浮点数以一个十六进制的数如0x1.C0000p+1类似的样子输出一个浮点数
    printf("%a\n",31.4);//0x1.f666666666666p+4
    printf("%A\n",31.4);//0X1.F666666666666P+4
    //----------%a据说依赖编译器和OS。反正平时用不到，不关心

   // getchar();
}
//组合，格式控制
void testPrintf3(){
    //可变宽度，即有程序在运行时指定宽度。用一个星号表示
    printf("%*d\n",4,9);//多出一个参数用来传宽度。输出   9。前面补空格
    printf("%0*d\n",4,9);//输出0009，补0

    //%和d中间加一个空格。正数显示空格+数字，负数则原样显示。
    //比如数字正10，打印” 10“，负数10打印”-10“
    printf("value % d % d\n", 10, -10);//value  10 -10
    //如果是正数，前面显示+号
    printf("value %+d %+d\n", 10, -10);//value +10 -10
    //%-20s意思是宽度20，在后面（而不是前面）补空格
    printf("%-4dtest\n", 5);//5   test,宽度4，空格补后面。这种情况只能补空格，不能补0。因为0补后面会造成误解
    printf("%-20stest\n", "abcd");//abcd                test
    printf("%20stest\n", "abcd");//                abcdtest,默认是前面补空格
}
int main() {
    testPrintf1();
    printf("--------------\n");
    testPrintf2();
    printf("--------------\n");
    testPrintf3();
    return 0;
}
