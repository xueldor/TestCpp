## ANSI-C
我们所学习的 C 语言大多是 ANSI-C 标准，也就是后来被标准化的 C89 标准。1999 年发布的 C99 和 2011 年发布的 C11 标准在此之上，引入了许多新的特性，也解决了许多问题。因此，随着标准的发布，我们的 C 语言规范和写法也要发生相应的变化。

C 语言规范的最大的变化发生在 C99 规范之中。C11 虽然也有一些特性，但更多的算是为了于 C++ 同步而引入的新特性。

GCC 和 Clang 编译器默认都是支持 C11 规范，如果需要显式指定，在编译时加入 `-std=c99` 或者 `-std=c11` 即可。

## 新的基本数据类型规范
### 数值类型
原先的 int，long 等变量基本类型在不同架构的机器上，会有不同的长度，往往会导致不可预期的问题。

在 C99 中，引入了新的头文件 <stdint.h> 在这个头文件中，同一规范了不同长度数据类型的定义：
* int8_t, int16_t, int32_t, int64_t 分别代表 8, 16, 32, 64 位的整型
* uint8_t, uint16_t, uint32_t, uint64_t 分别代表 8, 16, 32, 64 位的无符号整数

因此，推荐使用这些固定长度的数据类型，来代替传统的 int, short, long 等。

### 字符类型，宽字节和多字节
传统 C89 标准只支持 ascii 码，在 C99 中引入了 <wchar.h> 和 <wctype.h> 两个头文件，用于处理宽字节。  
`wchar_t` 类型是 32 位或 16 位，可以容纳所有的 Unicode 字符。

但是，虽然汉字不能放到一个char里，但是可以用`char*`或`char[]`存储汉字，printf啥的都完全没问题，唯一的问题在于 sizeof 获取的长度并不是真正的字数，所以wchar_t不常用。只在用于字符统计等需求时，才需要使用到宽字符类型。
```c
    setlocale(LC_ALL, "C.UTF-8");
    wchar_t c = L'汗';
    char* cc = "汗";
    printf("%lc %s",c,cc);
//输出： 汗 汗
```
你看，要正确输出wchar_t，必须正确设置setlocale。char*不需要。可见并不方便，只有必须要用时，才使用。

在 C11 中 <uchar.h> 头文件对字符集的 Unicode 支持进一步扩充。支持定义如下字符串:
```c
char s1[] = "你好";       // 标准支持
char s2[] = u8"你好";     // utf-8 编码
char16_t s3[] = u"你好";  // 16 位宽字符
char32_t s4[] = U"你好";  // 32 位宽字符
wchar_t s5[] = L"你好";   // 根据本机架构决定宽字符长度
```

### 布尔类型
C语言没有布尔类型，C99 规范中定义了头文件 <stdbool.h> ，实现了一个宏定义bool，取值为 true 和 false 。
```c
#include <stdbool.h>
bool found = true;
bool empty = false;
bool is_foo();
```
### 复数类型
C99 中引入了复数类型，可以直接表示复数或者平面中的一个点。
其声明在 <complex.h> 头文件中。分别有三种类型的复数类型：
* double complex
* float complex
* long double complex 

宏 _Complex_I 或者 I 来声明一个复数。此外还有一些常用的复数函数，例如： 
* ccos, csin, ccos, csinh 等三角函数和双曲函数
* cexp, clog, cabs, cpow, csqrt 等数学函数
* carg, cimag, creal 获取象限角、虚数部分、实数部分等函数

下面是一个简单的例子：
```c
double complex a = 1.0 + 2.0 * I;
double complex b = 5.0 + 4.0 * I;
a *= b;
a = csin(b);
a = creal(b);
```
## 数组和结构体
### 可变长数组（VLA）
在 C99 之前，如果数组的长度在编译时无法确定，遇到这种情况，我们通常只有两种做法：一是申请一个足够长度数组（需要对长度进行估计，否则很可能会溢出），一个是使用 malloc 在堆中分配数组(但是需要维护，需要释放等)。

在 C99 之后，引入了可变长数组（VLA）的概念，可以实现数组的长度在编译时不一定需要确定。这样可以实现在运行时确定数组长度，而作用于结束后自动释放。

比如:
```c
int len;
scanf("%d", &len);//从键盘输入数组的长度
printf("%d\n", len);

int arr[len];
printf("arr len= %d", sizeof(arr));
```
但是这种用法也有一些限制，比如：
* n 和 array 必须位于同一个文件作用域
* 不可以用于 typedef
* 不可使用在结构体中
* 不可以申明为 static 变量,必须是自动存储类型,也就是要放到函数里面（放到外面就是全局变量了）
* 不可以申明为 extern 变量或 extern 变量的指针
* 不能对数组进行初始化，因为它的长度在运行时才能确定

另外，C++的标准中无论是C++90还是C++99还是C++11都不支持VLA的这种写法。
#### VLA的实现原理
碰到变长数组的情形，编译器可以按一个指针的大小为其预留一个slot，然后到运行的时候esp-eax分配了空间以后，把当前esp，即数组的首地址放入到这个slot中。以后对数组的引用，就要进行两次访存，一次取到数组的首地址，一次访问真正的数组元素。有点类似于指针的下标访问了。  
变长数组的存储分配是在运行时，并且访问也需要两次访存，比原来的数组访问开销要大，但它与动态分配malloc还是有区别的。由于变长数组分配在栈中，只需要改变esp的值就能达到分配的目的，而malloc分配则需要runtime system来进行heap management,也就是说分配的时候需要一定的search operation来得到一块连续的存储，而释放的时候也要执行相应的代码来使得这块存储。

##  alignof
在 C11 标准中，头文件 <stdalign.h> 定义了新的 alignof 运算符，和 sizeof 相对应。

sizeof返回对象或类型的大小。而alignof返回 `类型名` 所指名的类型的对齐要求。若 `类型名` 为数组类型，则结果为数组元素的对齐要求。

内置的基础类型，比如char、int、float、double，在内存布局上都是按照其 sizeof 大小进行对齐（alignment），即`alignof(char)`的值就是`sizeof(char)`。

但是对复合类型如结构体，就比较复杂了。
* 结构体中的元素是按照定义的顺序逐个放到内存中去的，第一个元素就在结构体偏移量为0的地址处。  
  但元素并不是紧密排列的，中间有缝隙。从结构体存储的首地址开始，首地址按0计算，每一个元素放置到内存中时，放置的位置一定会在自己所占空间大小的整数倍上。  
  比如： 
    ```c
    struct A{
        int avg;
        double data;
    };
    ```
  int长度是4，double是8，但是sizeof(A)是16。我们分析一下，avg放在A对象的起始处没问题。data因为长度是8，只能放在 `起始位置+8的整数倍` 处。因此avg和data中间有4个字节的空隙。  
  
  ```
  |  avg  |  空隙  |     data           | 
  ```  
  alignof(A)是结构体内所有变量的对齐值，最大的那个，对于struct A，就是double。
* 结构体总大小为：最大对齐数（所有变量类型最大者与默认对齐参数取最小）的整数倍。
    ```c
    struct B{
        int avg;
        double data;
        char c;
    };
    ```
  最后一个char，虽然只占一个字节，但是sizeof(B)是24。因为按照内存分布，char c要放在偏移16的位置，也就是B大小至少是17，按照8的整数倍，应该是24。
  然后下面这个结构体size仍然是24,avg2从位置20开始。
  ```c
    struct B{
        int avg;
        double data;
        char c;
        int avg2;
    };
    ```
* 如果一个结构体里嵌套一个结构体，则结构体成员要从嵌套的结构体内部最大元素大小的整数倍地址开始存储。


结合test_alignof.c的实例理解。

## 宏定义和预编译
C99 在宏定义部分有一些新的变化，最常用的就是 Pragma 运算符和可变宏的引入。
### Pragma 运算符
C99 中引入。主要有 _Pragma 运算符和 #pragma 宏。是用于指定编译时的行为，比如：
```c
# 编译时显示消息
#pragma message(“_X86 macro activated!”)
# 注释
#pragma comment(…)
```

此外，#pragma once 使用的非常多，这是一个非标准但是被普遍实现的特性(Clang, GCC, Visual C 等主流编译器均支持)。用于指出该头文件只引入一次。和下面语句等效:
```c
#ifndef xxx
#def xxx

#endif
```
### 可变长宏
定义宏的时候可以引入不定长度的输入参数，具体用法不在列出。

## 堆的分配
在《how to c in 2016》中指出，应当尽可能使用 calloc 函数代替 malloc 函数，因为其分配空间时会自动初始化为 0，比 malloc 分配后再使用 memset 高效。
   
此外也建议不再使用 memset 函数。
   
函数原型是： calloc(object count, size per object)

## C11 线程
在 C11 中，引入了轻量级线程的标准实现,头文件<threads.h>。在此之前C语言实现多线程，使用系统API，对于Linux，就是pthread.h。
threads.h在语法上和pthread.h非常相似。
1. GCC的发布并不包含stdio这样的C标准库，而是依赖于系统提供的运行环境。Ubuntu 18.04.1 使用的是 glibc 2.27,没实现threads.h。需要在Ubuntu20上运行
2. 内部许多实现就是对pthread.h 做了简单封装，因此要导入pthread库：
```cmake
set(CMAKE_C_FLAGS -pthread)
```
否则编译会报：undefined reference to thrd_create

示例程序中使用到的库函数及宏：
*  thrd_t //此宏定义用于存放线程标识符的数据类型
*  thrd_create //此函数用于创建线程
*  thrd_detach //此函数用于通知操作系统，当线程结束时由操作系统负责释放资源
*  thrd_exit //此函数用于结束当前线程

