# TestCpp
演示c++语言的基础特性，不包括c++11新特性。故CMakeLists里面指定set(CMAKE_CXX_STANDARD 98)。（重要，因为代码里有一些C++ 11不支持的写法）  
为了演示清楚语法特性，代码有许多不常规、不推荐的写法，所以编译有不少警告，需周知。


2021/11/01 update
-----------------
* 项目环境从vs2008改用Clion;
* 编译器mingw64 winlibs-x86_64-posix-seh-gcc-11.2.0-mingw-w64ucrt-9.0.0-r2
* 修复一些原来在vs2008下编译通过，新编译器编译不通过的错误
* 将所有代码文件编码改成UTF-8  

因为Windows cmd默认用GBK编码，因此这样改会带来乱码问题。解决方法如下：  
方法一： cmd里面先执行 chcp 65001，然后运行可执行文件。  
方法二：用git bash执行可执行程序，可正常显示中文。

Clion中Run大概率也是乱码，按以下设置：
File-Settings中搜索encoding,将三个选择框全部改成UTF-8;
然后使用快捷键：shift+ctrl+alt+/ ,选择第一个选项 Registry（注册表），找到蓝色的 run.processes.with.pty 将其 Value 的复选框去掉

项目个别地方用中文作为变量名(不推荐)，这是符合语言规范的，visual studio里面也没问题，但是用mingw64，编译错误，提示“error stray ‘\xxx’ in program”。原因是gcc 从 gcc-10.0.0 版本开始，才支持定义中文（utf-8）的变量名、函数名、类名。
而https://sourceforge.net/projects/mingw-w64/files/ 这个网站下载的mingw64最高版本只有8.1。因此我从https://github.com/brechtsanders/winlibs_mingw 下载最新版本11.2，然后ＯＫ。

此程序演示C++语言的一些简单特性。
由于项目中有且仅能有一个main方法，故运行某个cpp中的demo时，请将该文件中的main方法放开

项目简介
--------
TestBasicNumber.cpp:演示基本的数据类型，用sizeof获取占用大小，可以表示的数据范围，字面量如何表示，有符号与无符号的转换，类型转换，表达式计算规律等

TestArray.cpp：演示数组的创建、初始化、用char数组表示字符串、多维数组、指针数组、指向数组的指针等内容

testbit.cpp： 演示C++中的位运算。给出循环移位的实现方法。

testchar.cpp：演示标准库<cctype>中的方法.cctype是字符处理库。

testFunction.cpp：函数的定义和使用、函数与指针、函数模板

testnamespace.cpp、testnamespace.h、testScope2.cpp：演示定义以及使用命名空间

testPoint.cpp：演示指针和引用相关的知识

testScope.cpp、testScope2.cpp： 演示变量的作用域、静态存储、外部链接性、生命周期、在指定的内存上构造对象

teststring.cpp：C++标准库的string类、与C风格字符串互转

teststruct.cpp：结构体、联合、枚举、位域

test_new.cpp

testextend.cpp

test_multi_extend.cpp

operOverloading.cpp

testClassTemplate.cpp

