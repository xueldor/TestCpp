#include <stdio.h>

/**
 * VLA即可变长数组。这个名字容易引起误解。不是说数组的长度会随时变化，而是数组的长度可以在运行时确定，一旦分配，在其生存期内的长度同样是固定的。
 * 过去我们认为，既然非动态分配的数组，其内存是在栈上，那么必须在编译期间明确其大小。
 * C99 通过一些技术，做到运行时才知道大小，而且内存仍然是在栈上。
 * 实现原理见README
 * @return
 */
void test_vla(){
    int len;
    scanf("%d", &len);
    printf("%d\n", len);
    int arr[len];
    printf("arr len= %d\n", sizeof(arr));
}