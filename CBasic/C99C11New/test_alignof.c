#include <stdio.h>
#include <stdalign.h>

struct Empty{};
struct A{
    int avg;
    double data;
};
struct A0{
    int avg;
    int avg2;
    double data;
};
struct A1{
    char c;
    int avg;
    int avg2;
    double data;
};
struct A2{
    char c;
    char cc;
    char ccc;
    char cccc;
    char ccccc;
    char cccccc;
    char ccccccc;
    char cccccccc;
    int avg;
    int avg2;
    double data;
};

struct B{
    int avg;
    double data;
    char c;
    int avg2;
};

void test_alignof() {
    printf("sizeof(char):%d\n", sizeof(char));
    printf("alignof(char):%d\n", alignof(char));
    printf("sizeof(int):%d\n", sizeof(int));
    printf("alignof(int):%d\n", alignof(int));
    printf("sizeof(double):%d\n", sizeof(double));
    printf("alignof(double):%d\n", alignof(double));

    struct Empty empty;
    printf("sizeof(Empty):%d,  sizeof empty:%d\n", sizeof(struct Empty), sizeof empty);
    printf("alignof(Empty):%d\n", alignof(struct Empty));

    //sizeof(A):16
    printf("sizeof(A):%d\n", sizeof(struct A));
    //alignof(A):8
    printf("alignof(A):%d\n", alignof(struct A));

    printf("sizeof(A0):%d\n", sizeof(struct A0));
    printf("alignof(A0):%d\n", alignof(struct A0));

    printf("sizeof(A1):%d\n", sizeof(struct A1));
    printf("alignof(A1):%d\n", alignof(struct A1));
    printf("sizeof(A2):%d\n", sizeof(struct A2));
    printf("alignof(A2):%d\n", alignof(struct A2));

    printf("sizeof(B):%d\n", sizeof(struct B));
    printf("alignof(B):%d\n", alignof(struct B));
}