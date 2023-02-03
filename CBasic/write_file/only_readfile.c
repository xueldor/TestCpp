
#include <stdio.h>
#include <errno.h>
#include <string.h>


/**
 * "r" 模式打开一个不存在的文件。返回NULL， 系统将errno设置为2
 */
void read_not_exit_file(){
    FILE * f = fopen("testread1", "r");
    if(f == NULL) {
        //error: 2 No such file or directory
        printf("error: %d %s\n", errno, strerror(errno));//strerror获取errno对应的描述
    } else {
        fclose(f);
    }
}
/**
 * "r" 模式打开一个文件。只读
 */
void read_file(){
    FILE * f = fopen("../testread2.txt", "r");
    if(f == NULL) {
        //error: 2 No such file or directory
        printf("error: %d %s\n", errno, strerror(errno));//strerror获取errno对应的描述
    } else {
        int onechar = fgetc(f);//读一个字节，然后当前光标后移一位
        printf("first char:%c\n", onechar);

        //fgets是读一行字符串的函数。当读取到 (n-1) 个字符、读取到换行符时，或者到达文件末尾时，它会停止，具体视情况而定。
        //光标接着前面的位置，读n-1位，再添加\0变成n位，然后光标位置后移
        char str[200];
        fgets(str, 3, f);//读取3-1=2个字节，并自动添加\0
        printf("%s\n", str);
        //读一行，注意fgets会连换行符一起放到数组里。
        fgets(str, 50, f);
        printf("%s", str);

        memset(str, 0, sizeof(str));
        long int num;
        fscanf(f, "%ld", &num);//读一个数字。
        printf("%d\n", num);
        int currentChar = fgetc(f);//"%ld"读数字后，下一个字符是换行符
        printf("current char:%c\n", currentChar);

        fscanf(f, "%ld\n", &num);//读一个数字,及后面的换行。
        printf("%d\n", num);
        currentChar = fgetc(f);//前面连换行符一起读了，所以光标在下一行开头
        printf("current char:%c\n", currentChar);

        //size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
        //fread是读字节，而不是字符，所以不认换行。一直往下读，直到末尾或达到size*nmemb
        //size: 每个元素的大小
        //nmemb: 需要读几个元素
        //返回值： 实际读取了几个元素
        //一般把size设为1，这样返回的是到底读取了多少个字节
        size_t size = fread(str, 1, 200, f);
        printf("%d %s\n", size, str);

        //光标从当前位置往回移20个字节
        fseek(f, -20, SEEK_CUR);
        memset(str, 0, sizeof(str));
        fscanf(f, "%s", str);//读一行
        printf("%s\n", str);
        fclose(f);
    }
}

void test_readfile() {
    read_not_exit_file();
    read_file();
}