#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/**
 * -----------
 * 总结:sprintf和sscanf两个方法足够
 * 基本类型转char*,用 sprintf
 * char*转基本类型用sscanf
 * 格式化输出用sprintf,还原格式化的字符串用sscanf
 * -----------
 */
/**
 * 整形转换为指定进制的字符串
 */
void int2String(){
    int size=123;
    //全局变量区默认初值为0。这里是局部变量，如果不写“ {} ”，则默认的初值为乱码（内存原来的数据）。
    //如果写“ {’a‘,'a'} ”给低几位赋值，则其他未赋值的数默认初值为0
    //因此这里不再需要调memset设置。并且sprintf实际上也会把前面的置为0。
    char fileSizeStr[20] = {0};
    sprintf(fileSizeStr,"%d",size);//size按照10进制写入fileSizeStr
    puts(fileSizeStr);//123
    sprintf(fileSizeStr,"%d", 4);//fileSizeStr值是4,注意不是1234，也不是124
    puts(fileSizeStr);

    sprintf(fileSizeStr,"%x",size);//16进制
    puts(fileSizeStr);//7b

    sprintf(fileSizeStr,"%X",size);//16进制,大写
    puts(fileSizeStr);//7B
}

/**
 * atoi方法,在stdlib.h中
 */
void string2int(){
    char *num2 = "71 72";
    int val1, val2;
    //注意传val的起始地址。"%02d %02x"告诉函数，num2的格式是“数字空格数字”，按照这个解析，取出数字
    sscanf(num2,"%02d %02x",&val1, &val2);//文本71按照10进制理解,表示数字71，放到val1；72按照16进制理解,表示数字114，放到val2
    printf("val1=%d, val2=%d\n", val1, val2);//val1=71, val2=114


    char *num = "45000";
    int n=atoi(num);//将'45000'按照10进制理解,转成int
    printf("%d\n",n);

    char *numf = "45.25";
    float f=atof(numf);
    printf("%f\n",f);
}


/**
 * 字符串转换为16进制保存到数组
 */
void charStr2HexStr() {
    char *src = "abcdefg";
    char fileSizeStr[20] = {0};
    for (int i = 0; i < strlen(src); i++) {
        //将src按照format的格式发送到字符串
        sprintf(fileSizeStr+strlen(fileSizeStr), "%02X:", (unsigned char)src[i]);//02表示对齐到两位,不足补0,X表示大写的16进制
    }
    puts(fileSizeStr);//61:62:63:64:65:66:67:
}

/**
 * 16进制的字符串转换为原来形式
 */
void hexStr2charStr() {
    char *src = "616263";
    char fileSizeStr[20] = {0};
    for (int i = 0; i < strlen(src)/2; i++) {
        //与sprintf相反,从字符串读取格式化输入
        sscanf(src + i*2,"%02X",fileSizeStr + i);
    }
    puts(fileSizeStr);//abc
}