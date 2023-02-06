#include <stdio.h>
#include <time.h>

/**
 * 获取系统当前时间
 * time_t实际就是long long或long int，存放时间戳,单位是秒
 * 自纪元 Epoch（1970-01-01 00:00:00 UTC）起经过的时间
 *
 * struct tm是定义了年月时分秒的结构体，可以与time_t互相转换
 */
void getCurrentTime() {
    time_t tt = time(0);
    printf("current time %ld\n", tt);

    //如果参数不是NULL，那么时间也同时写入参数指针指向的time_t变量。
    time_t tt2, tt3;
    tt3 = time(&tt2);
    printf("current time %ld, %ld\n", tt2, tt3);//输出current time 1675666619, 1675666619，运行本程序的时间。
    int year = tt2/365/24/3600 + 1970;//除以1年的秒数（虽然1年的秒数不是固定的，但是不影响）
    printf("year: %d\n", year);//2023

    //time_t转struct tm,用本地时区
    struct tm *pst = localtime(&tt);//传地址
    printf("The year is %d. \n", pst->tm_year + 1900);//struct tm中的year是自 1900 年起的年数
    printf("The month is %d. \n", (pst->tm_mon + 1));//month月份从从 0 到 11，加一后才是大众习惯的
    printf("The day of month is %d. \n", pst->tm_mday);//这个月的几号
    printf("The day of year is %d. \n", pst->tm_yday);//这一年的第几天。0~365，要不要加1看需求。
    printf("The hour is %d. \n", pst->tm_hour);//0 到 23

    //struct tm转time_t
    time_t tt4 = mktime(pst);
    printf("timestamp: %ld\n", tt4);

    //time_t转struct tm, 用协调世界时（UTC）也被称为格林尼治标准时间（GMT）表示
    pst = gmtime(&tt);
    printf("gmtime-------\n");
    printf("The year is %d. \n", pst->tm_year + 1900);//struct tm中的year是自 1900 年起的年数
    printf("The month is %d. \n", (pst->tm_mon + 1));//month月份从从 0 到 11，加一后才是大众习惯的
    printf("The day of month is %d. \n", pst->tm_mday);//这个月的几号
    printf("The day of year is %d. \n", pst->tm_yday);//这一年的第几天。0~365，要不要加1看需求。
    printf("The hour is %d. \n", pst->tm_hour);//因为中国是东8区，所以相比前面localtime函数，这里hour数值小8。比如本地时间15点，则这里tm_hours是7。
    printf("伦敦 %02d. 中国 %02d \n", pst->tm_hour + 1, pst->tm_hour + 8);//因为中国是东8区，所以相比前面localtime函数，这里hour数值小8。比如本地时间15点，则这里tm_hours是7。

    //mktime依据本地时区的 struct tm 转，所以这里得到的time_t差了八个小时。也就是说这样用是错的
    time_t tt5 = mktime(pst);
    printf("diff hours: %ld\n", (tt-tt5)/3600);//东8区输出8
}

void getClock() {
    //CLOCKS_PER_SEC是标准c的time.h头函数中宏定义的一个常数，表示一秒钟内CPU运行的时钟周期数
    //程序执行起（一般为程序的开头），处理器时钟所使用的时钟周期数。为了获取 CPU 所使用的秒数，您需要除以 CLOCKS_PER_SEC。
    //该函数大约每 72 分钟会返回相同的值。
    clock_t ct = clock();
    printf("%ld %ld %lf\n", ct, CLOCKS_PER_SEC, (double)ct/CLOCKS_PER_SEC);
}

void format() {
    time_t tt = time(0);
    char* date = ctime(&tt);//因为指针也是整形，time_t也是整形，所以要注意传地址，编译器不会提示。
    printf("date is:%s" , date);
    time_t tt2 = tt + 100;
    //ctime这个函数很奇怪，返回一个字符串，那么它的内存在哪？我们知道如果是在ctime内部开辟的内存(即char数组局部变量)，那么返回后内存即释放，是不能返回char*的；
    //如果是动态分配，那么就需要free。但实际不需要。
    //所以结论是使用的全局变量或静态变量。那么每次调用应该都是共享的一块内存。下面验证
    char* date2 = ctime(&tt2);
    printf("date2 is: %s" , date2);
    printf("date is: %s" , date);//date的打印变成了和date2一样的值，证明了date和date2同是一块内存。

    struct tm *pst = localtime(&tt2);
    char* str = asctime(pst);
    printf("date2 is: %s" , str);


    //使用strftime控制格式
    char dateStr[50];
    strftime(dateStr, 50, "%Y-%m-%d %H:%M:%S", pst);
    printf("dateStr：%s\n", dateStr);
}

int main() {
    getCurrentTime();
    getClock();
    format();
    return 0;
}
