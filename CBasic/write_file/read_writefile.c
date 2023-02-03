
#include <stdio.h>
#include <errno.h>
#include <string.h>
/**
 * C语言fopen并没有"rw" 模式。实测发现可读不可写。相当于“r”
 * （然而有资料说，有些编译器上，rw相当于r+。wr相当于w+。ar相当于a+。我没遇到过）
 */
void try_read_write_file(){
    //rw模式，如果文件不存在，不会自动创建（类似“r”模式）;
    //如果文件已存在，也不会清空原来的数据（不同于“w”模式）
    FILE * f = fopen("../testreadwrite1.txt", "rw");
    if(f == NULL) {
        printf("error: %d %s\n", errno, strerror(errno));//strerror获取errno对应的描述
    } else {
        int onechar = fgetc(f);
        printf("first char:%c\n", onechar);//可读

        //写
        const char str[] = "123456789012";
        fwrite(str, 1, strlen(str), f);
        fflush(f);//写无效

        fclose(f);
    }
}

/**
 * 带有“+”表示即可读又可写。“r+”特性近似“r”,要求文件必须存在
 * 读和写是一个指针
 */
void read_write_file(){
    //r+模式
    FILE * f = fopen("../testreadwrite2.txt", "r+");
    if(f == NULL) {
        printf("error: %d %s\n", errno, strerror(errno));//strerror获取errno对应的描述
    } else {
        int onechar = fgetc(f);
        printf("first char:%c\n", onechar);//可读

        //写
        const char str[] = "123456789012";
        fwrite(str, 1, strlen(str), f);
        //光标重置到文件开头
        fseek(f, 0, SEEK_SET);
        onechar = fgetc(f);
        printf("now char:%c\n", onechar);//可读
        fwrite("x", 1, 1, f);

        fclose(f);
    }
}

/**
 * 带有“+”表示即可读又可写。“w+”特性近似“w”,
 * 如果文件不存在，会自动创建（类似w）；
 * 会清空原来的内容（类似w）；
 * 读和写是一个指针
 */
void read_write_file2(){
    //r+模式
    printf("read_write_file2\n");
    FILE * f = fopen("../testreadwrite3.txt", "w+");
    if(f == NULL) {
        printf("error: %d %s\n", errno, strerror(errno));//strerror获取errno对应的描述
    } else {
        int onechar = fgetc(f);
        printf("first char:%c\n", onechar);//因为清空了文件，所以读不到内容，指针位置也依然在文件开头。打印乱码

        //写
        const char str[] = "123456789012";
        fwrite(str, 1, strlen(str), f);
        //光标重置到文件开头
        fseek(f, 0, SEEK_SET);
        onechar = fgetc(f);
        printf("now char:%c\n", onechar);//可读
        fwrite("x", 1, 1, f);

        fclose(f);
    }
}

/**
 * 带有“+”表示即可读又可写。“a+”特性近似“a”,
 * 如果文件不存在，会自动创建（类似a）；
 * 因为a模式文件指针无效，只能在末尾追加，所以，“a+”的指针只对读有效。
 * 即：
 * 1. 刚打开时，读的位置是在文件开头；
 * 2. 任何时候，调用fseek，读的位置到fseek的位置
 * 3. 写的位置一定是在文件末尾。也就是，写操作会把指针移到文件末尾，接下来的读文件操作也是在末尾进行（当然读不出内容）。要读前面的内容，必须重新fseek。
 * 不要认为读有一个指针，写有一个指针。FILE里面就一个指针。
 */
void read_write_file3(){
    //r+模式
    FILE * f = fopen("../testreadwrite4.txt", "a+");
    if(f == NULL) {
        printf("error: %d %s\n", errno, strerror(errno));//strerror获取errno对应的描述
    } else {
        int onechar = fgetc(f);
        printf("first char:%c\n", onechar);//读文件开头第一个字符

        //而写是追加到文件末尾
        const char str[] = "123456789012";
        fwrite(str, 1, strlen(str), f);
        //光标重置到文件开头，只对读取操作有效。不影响写。
        fseek(f, 0, SEEK_SET);
        onechar = fgetc(f);//读开头字符
        printf("now char:%c\n", onechar);
        fwrite("x", 1, 1, f);//写到末尾

        onechar = fgetc(f);//读字符，发现指针到了末尾，读不出，打印乱码
        printf("now char:%c\n", onechar);

        fclose(f);
    }
}

void test_read_writefile() {
    try_read_write_file();
    read_write_file();
    printf("-----\n");
    read_write_file2();
    printf("-----\n");
    read_write_file3();
}