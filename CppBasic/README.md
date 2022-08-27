# TestCpp
演示c++语言的基础特性，主要演示C++03, 也许有少量C++11或C++14才支持的语法，但这只是因为知识的关联性顺便带出来的。另开一个项目专门练习C++11&14的新特性。


项目简介
--------
01-number:演示基本的数据类型，用sizeof获取占用大小，可以表示的数据范围，字面量如何表示，有符号与无符号的转换，类型转换，表达式计算规律,位运算、字符处理库等

02-array：演示数组的创建、初始化、用char数组表示字符串、多维数组、指针数组、指向数组的指针等内容

03-function：函数的定义和使用、函数与指针、函数模板

04-namespace：演示定义以及使用命名空间、using关键字，演示变量的作用域、静态存储、外部链接性、生命周期、相关知识

05-point：演示指针和引用相关的知识


06-string：C++标准库的string类、与C风格字符串互转

07-struct：结构体、联合、枚举、位域

08-new：new和delete，通过重载operation new控制new的行为，和其它高级用法

09-classBasic： 类的基础，怎么声明和使用各种类型的成员（static的、const的、各种组合）。

10-extend： 类继承，多继承，可见性、virtual继承，纯虚函数等

11-classTemplate： 类模板。并给了一个模板元编程的例子。

12-operationOverloading： 运算符重载

13-copy： 研究数组的拷贝，类对象的拷贝，拷贝构造函数和重载赋值运算符


因为所有代码文件编码都用UTF-8 ，如果你在windows上用Clion Run出现乱码，按以下设置：  

File-Settings中搜索encoding,将三个选择框全部改成UTF-8;
然后使用快捷键：shift+ctrl+alt+/ ,选择第一个选项 Registry（注册表），找到蓝色的 run.processes.with.pty 将其 Value 的复选框去掉。  
Linux不会出现乱码。

2022/08/22 update
-----------------
考虑到c++14已经普及，也没人再用老旧的编译器，故set(CMAKE_CXX_STANDARD 98)改为set(CMAKE_CXX_STANDARD 14)，以保证代码适用现代编译器。  
使用g++版本11.2.0，CLion 2022.1.1，但不等于你一定要这个版本，支持c++14即可。  
原来所有的代码放在一起，现改成了分解成一个个小项目，每个项目演示一部分特性。  
只为演示清楚语法特性，没有遵循c++的编程风格，需周知。    

如果你没有CLion，任何支持CMakefile的IDE应该都可以。也可以用纯的命令行（Linux）：  
```shell
mkdir out
cd out
cmake ..
make
```
前提是你要装好cmake和make。


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
