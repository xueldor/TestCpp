#include <stdio.h>
#include <stdbool.h>

void test_wchar();
void test_vla();
void test_init();
void test_alignof();

int test_thread(void);


int main() {
    test_wchar();
    //test_vla();
    test_init();
    test_alignof();
#ifdef TEST_THREAD
    test_thread();
#endif
    return 0;
}
