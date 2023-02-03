
#include <stdio.h>
#include <errno.h>
#include <string.h>
/**
 * "w" 模式打开一个文件。只能写
 */
void write_file(){
    //如果文件不存在，会自动创建
    //如果文件已存在，原来的数据会清掉
    FILE * f = fopen("../testwrite1.txt", "w");
    if(f == NULL) {
        //linux将testwrite1.txt的权限组设为000，执行打印error: 13 Permission denied
        printf("error: %d %s\n", errno, strerror(errno));//strerror获取errno对应的描述
    } else {
        //因为是“w”模式，不能读
        int onechar = fgetc(f);
        printf("first char:%c\n", onechar);//无法读取文件内容，打印是乱码

        //写
        const char str[] = "123456789012";
        fwrite(str, 1, strlen(str), f);
        fflush(f);//这时文件内容是"123456789012"

        //光标重置到文件开头,然后再后移一位
        fseek(f, 1, SEEK_SET);
        fwrite("a", 1, 1, f);
        fclose(f);
        //然后打开文件看，内容变成了1a3456789012,原来的 2 ——> a。
        //为什么不不是插入，而是替换了2？因为数据连续存在存储介质上，插入意味着后面的要往后移一位。fwrite只是在当前位置写。
    }
}

/**
 * "a" 模式打开一个文件。只能写
 */
void append_file(){
    //如果文件不存在，会自动创建
    //如果文件已存在，文件末尾追加
    //文件指针无效
    FILE * f = fopen("../testwrite2.txt", "a");
    if(f == NULL) {
        printf("error: %d %s\n", errno, strerror(errno));//strerror获取errno对应的描述
    } else {
        //因为是“a”模式，不能读
        int onechar = fgetc(f);
        printf("first char:%c\n", onechar);//无法读取文件内容，打印是乱码

        //写
        const char str[] = "123456789012";
        fwrite(str, 1, strlen(str), f);
        fflush(f);//这时文件内容是"123456789012"

        //试图前移光标。发现无效，仍然是在文件末尾追加
        fseek(f, -10, SEEK_CUR);
        fwrite("ab", 1, 2, f);

        //fseek无效
        fseek(f, -1, SEEK_END);
        fwrite("x", 1, 1, f);

        fclose(f);
        //然后打开文件看，内容变成了1a3456789012,原来的 2 ——> a。
        //为什么不不是插入，而是替换了2？因为数据连续存在存储介质上，插入意味着后面的要往后移一位。fwrite只是在当前位置写。
    }
}

void test_writefile() {
    write_file();
    printf("-----\n");
    append_file();
}