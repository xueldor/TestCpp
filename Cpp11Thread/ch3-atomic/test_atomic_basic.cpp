#include <iostream>
#include <thread>
#include <atomic>
#include <time.h>
#include <mutex>

using namespace std;


int main() {
    std::atomic<bool> ready (false);
    ready.store(true);
    bool val = ready.load();
    cout<<"1. "<<val<<endl;

    bool val2 = ready.exchange(false);
    cout<<"2. "<<val2<<"   "<<ready<<endl;

    std::atomic<int> atint(3);
    int val3 = atint.exchange(5);
    cout<<val3<<"  "<<atint<<endl;
    bool successExchange = atint.compare_exchange_strong(val3, 6);
    cout<<val3<<"  "<<atint<<"  exchanged:"<<successExchange<<endl;
    return 0;
}
