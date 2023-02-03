#include <stdio.h>
#include <stdint.h>

void test_init(){
    uint32_t a1[64] = {0}; // 全部填充 0
    uint32_t a2[64] = {1, 2, [5]=6, [6]=7}; // 前两个元素填充1和2，a2[5]和a2[6]填6和7，其它全0
    printf("%d %d %d\n",a2[0], a2[5], a2[60]);

    struct thing {
        uint64_t index;
        char* name;
        uint32_t counter;
    };
    struct thing t1 = {0}; // 填充 0
    //结构体部分位置赋值
    struct thing t2 = {
            .index = 3,
            .counter = 4
    };
    // 也可以使用类似 Python 的形式
    struct thing t3 = {
            counter: 0,
            name: "cat"
    };
    printf("t2.index=%d, t3.name=%s\n", t2.index, t3.name);
}