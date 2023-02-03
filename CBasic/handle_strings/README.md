## sprintf
printf是输出到终端，sprintf就是输出到string。  
比如`printf("%d",size)`把整形的size输出到控制台，这个过程中，会自动将整形int转成控制台的字符串编码类型。

同理，`sprintf(fileSizeStr,"%d",size)`，就是把size这个int数写到fileSizeStr这个string上面。同样自动完成转换。
也就是说，如果size==97，那么fileSizeStr就是"97"，而不是"a"。

* "%d": 转成10进制对应的文本
* "%x": 转成16进制对应的文本
* "%X": 转成16进制对应的文本,区别是ABCDEF采用大写

关于sprintf还有一点要声明的是，下面这个代码：
```c++
    //已知size=123,fileSizeStr是字符串
    sprintf(fileSizeStr,"%d",size);//size按照10进制写入fileSizeStr
    puts(fileSizeStr);//puts是打印字符串的值，并自动添加换行。这里是123
    //然后继续输出到fileSizeStr
    sprintf(fileSizeStr,"%d", 4);//fileSizeStr值是4,注意不是1234，也不是124
    puts(fileSizeStr);
```
注意一下第二次打印的fileSizeStr值，也就是说，sprintf**不是追加**，而是赋值，比strcpy更强大的赋值，实验可知不管原来fileSizeStr每位是什么字符，`sprintf(fileSizeStr,"%d",size)`后都变成size的值。 

如果要实现追加的效果，第二次调用sprintf时，地址做个偏移就行：  
```c++
sprintf(fileSizeStr+strlen(fileSizeStr), "%02X:", (unsigned char)src[i])
```

sprintf的返回值是字符数组中字符的个数，即字符串的长度，不用再调用strlen(s)求字符串的长度。
还可以这么写：
```c++
sprintf(fileSizeStr,"here:%d %X", 15, 15);
puts(fileSizeStr);
```
输出“here:15 F”。F是15的16进制表示。注意要确保char数组fileSizeStr的长度足够。

## sscanf
sscanf和sprintf相反。sscanf的输入源是字符串，根据格式化字符串解析出来，放到变量里。  
sscanf和scanf的区别是scanf的输入源是终端，读取终端的输入，赋给变量。


## atoi atof atol
atoi: ascii to integer, 把参数 str 所指向的字符串转换为一个int 型整数。
atof 和 atol类似，atof转成浮点数double(不是float)，atol转成long。
如果不能成功转换，返回0或0.0。

## memset memcpy memmove 
经常用memset来清空数组和char*,比自己循环赋值更高效简洁。
