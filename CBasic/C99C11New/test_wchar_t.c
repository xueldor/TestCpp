#include <wchar.h>
#include <locale.h>
#include <stdio.h>

void test_wchar(){
    setlocale(LC_ALL, "C.UTF-8");
    wchar_t c = L'汗';
    char* cc = "汗";
    printf("%lc %s\n",c,cc);
}