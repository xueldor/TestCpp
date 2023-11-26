https://www.ibadboy.net/archives/2323.html

**目录**  
[线程管理](#线程管理)  
[互斥对象和函数](#互斥对象和函数)  
[条件变量](#条件变量)  
[初始化函数](#初始化函数)  
[线程专有数据(TSD)和线程局部数据 (TLS)](#线程专有数据tsd和线程局部数据-tls)  

threads.h是C11新增的多线程支持库，为什么命令用“thrd_create”这种奇怪的命名？可能是因为之前已经有很多类似“pthread_create”的命名，防止用新的编译器编译旧的代码出现命名冲突。

# 线程管理
```c
int thrd_create(thrd_t *thr,  thrd_start_t func,  void *arg);
```
thrd_create创建一个新线程，该线程的工作就是执行func(arg)调用，程序员需要为线程编写一个函数，函数签名为：thrd_start_t ，即int (*)(void*)类型的函数。新创建的线程的标识符存放在thr内。
```c
thrd_t thrd_current(void);
```
thrd_current函数返回调用线程的标识符。

```c
int thrd_detach(thrd_t thr);
```
thrd_detach会通知操作系统，当该线程结束时由操作系统负责回收该线程所占用的资源。

```c
int thrd_equal(thrd_t thr0, thrd_t thr1);
```
thrd_equal用于判断两个线程标识符是否相等（即标识同一线程），thrd_t是标准约定的类型，可能是一个基础类型，也可能会是结构体，开发人员应该使用thrd_equal来判断两者是否相等，不能直接使用==。即便==在某个平台下表现出来是正确的，但它不是标准的做法，也不可跨平台。

```c
void thrd_exit(int res)
```
thrd_exit函数提早结束当前线程，res为它的退出状态码。这与进程中的exit函数类似。

```c
int thrd_join(thrd_t thr, int *res)
```
thrd_join将阻塞当前线程，直到线程thr结束时才返回。如果res非空，那么res将保存thr线程的结束状态码。如果某一线程内没有调用thrd_detach函数将自己设置为detach状态，那么当它结束时必须由另外一个线程调用thrd_join函数将它留下的僵死状态变为结束，并回收它所占用的系统资源。

```c
void thrd_sleep(const xtime *xt)
```
thrd_sleep函数让当前线程中途休眠，直到由xt指定的时间过去后才醒过来。

void thrd_yield(void)
thrd_yield函数让出CPU给其它线程或进程。

# 互斥对象和函数
threads.h中提供了丰富的互斥对象，用户只需在mtx_init初始化时，指定该互斥对象的类型即可。

```c
int mtx_int(mtx_t  *mtx, int type);
```
mtx_init函数用于初始化互斥对象，type决定互斥对象的类型，一共有下面6种类型：

* mtx_plain –简单的，非递归互斥对象
* mtx_timed –非递归的，支持超时的互斥对象
* mtx_try –非递归的，支持锁检测的互斥对象
* mtx_plain | mtx_recursive –简单的，递归互斥对象
* mtx_timed | mtx_recursive –支持超时的递归互斥对象
* mtx_try | mtx_recursive –支持锁检测的递归互斥对象
```c
int mtx_lock(mtx_t *mtx)
int mtx_timedlock(mtx_t *mtx, const xtime *xt)
int mtx_trylock(mtx_t *mtx)
```
mtx_xxxlock函数对mtx互斥对象进行加锁 , 它们会阻塞，直到获取锁，或者xt指定的时间已过去。而trylock版本会进行锁检测，如果该锁已被其它线程占用，那么它马上返回thrd_busy。

```c
int mtx_unlock(mtx_t *mtx)
```
mtx_unlock对互斥对象mtx进行解锁。

# 条件变量
threads.h通过mtx对象和条件变量来实现wait-notify机制。
```c
int cnd_init(cnd_t *cond)
```
初始化条件变量，所有条件变量必须初始化后才能使用。
```c
int cnd_wait(cnd_t *cond, mtx_t *mtx)
int cnd_timedwait(cnd_t *cond, mtx_t *mtx, const xtime *xt)
```
cnd_wait函数自动对mtx互斥对象进行解锁操作，然后阻塞，直到条件变量cond被cnd_signal或cnd_broadcast调用唤醒，当前线程变为非阻塞时，它将在返回之前锁住mtx互斥对象。cnd_timedwait函数与cnd_wait类似，例外之处是当前线程在xt时间点上还未能被唤醒时，它将返回，此时返回值为thrd_timeout。cnd_wait和cnd_timedwait函数在被调用前，当前线程必须锁住mtx互斥对象。

```c
int cnd_signal(cnd_t *cond)
int cnd_broadcast(cnd_t *cond)
```
cnd_broadcast唤醒那些当前已经阻塞在cond条件变量上的所有线程，而cnd_signal只唤醒其中之一。

```c
void cnd_destroy(cnd_t *cond)
```
销毁条件变量。

# 初始化函数
试想一下，如何在一个多线程同时执行的环境下来初始化一个变量，即著名的延迟初始化单例模式。你可能会使用DCL技术。但在C11中，你可以直接使用call_once函来实现。
```c
void call_once(once_flag *flag, void (*func)(void))
```
call_once函数使用flag来保确func只被调用一次。第一个线程使用flag去调用call_once时，函数func会被调用，而接下来的使用相同flag来调用的call_once，func均不会再次被调用，以保正func在多线程环境只被调用一次。

# 线程专有数据(TSD)和线程局部数据 (TLS)
在多线程开发中，并不是所有的同步都需要加锁的，有时巧妙的数据分解也可减少锁的碰撞。每个线程都拥有自己私有数据，使用它可以减少线程间共享数据之间的同步开销。

如果要将一些遗留代码进行线程化，很多函数都使用了全局变量，而在多线程环下，最好的方法可能是将这些全局量变量换成线程私有的全局变量即可。

TSD和TLS就是专门用来处理线程私有数据的。 它的生存周期是整个线程的生存周期，但它在每个线程都有一份拷贝，每个线程只能read-write-update属于自己的那份。如果通过指针方式来read-write-update其它线程的备份，它的行为是未定义的。

TSD可认为线程私有内存下的void *组数，每个数据项的key对应于数组的下标，用于索引功能。当一个新线程创建时，线程的TSD区域将所有key关联的值设置为NULL。TSD是通过函数的方式来操作的。C11中TSD提供的标准函数如下：
```c
int tss_create(tss_t *key,  tss_dtor_t dtor)
void tss_delete(tss_t key)
void *tss_get(tss_t key)
int tss_set(tss_t key, void *val)
```
tss_create函数创建一个key，dtor为该key将要关联value的析构函数。当线程退出时，会调用dtor函数来释放该key关联的value所占用的资源，当然，如果退出时value值为NULL，dtor将不被调用。tss_delete函数删除一个key，tss_get/tss_set分别获得或设置该key所关联的value。

通过上述TSD来操作线程私有变量的方式，显得相对繁琐; C11提供了TLS方法，可以像一般变量的方式去访问线程私有变量。做法很简单，在声明和定义线程私变量时指定_Thread_local存储修饰符即可，关于_Thread_local，C11 有如下的描述：

1. 在声明式中，_Thread_local只能单独使用，或者跟static或extern一起使用。
2. 在某一区快中声明某一对象，如果声明存储修饰符有_Thread_local，那么必须同时有static或extern。
3. 如果_Thread_local出现在一对象的某个声明式中，那么此对象的其余各处声明式都应该有_Thread_local存储修饰符。
4. 如果某一对象的声明式中出现_Thread_local存储修饰符，那么它有线程储存期。该对象的生命周期为线程的整个执行周期，它在线程出生时创建，并在线程启动时初始化。每个线程均有一份该对象，使用声明时的名字即可引用正在执行当前表达式的线程所关联的那个对象。

TLS方式与传统的全局变量或static变量的使用方式完全一致，不同的是，TLS变量在不同的线程上均有各自的一份。线程访问TLS时不会产生data race，因为不需要任何加锁机制。TLS方式需要编译器的支持，对于任何_Thread_local变量，编译器要将之编译并生成放到各个线程的private memory区域，并且访问这些变量时，都要获得当前线程的信息，从而访问正确的物理对象，当然这一切都是在链接过程早已安排好的。

以下列出本文参考的资料，在此向原作者致敬。
* http://en.cppreference.com/w/c/thread/
* http://blog.csdn.net/linyt/article/details/5785311
* https://10hash.com/c-programming/threads/