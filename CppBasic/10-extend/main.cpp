#include <iostream>

namespace TestExtend{
    int main_extend();
}
namespace TestMutiExtend {
    int main();
}
using TestExtend::main_extend;
int main_extend2();
int main() {
    main_extend();
    std::cout<<"---------------main_extend2"<<std::endl;
    main_extend2();
    std::cout<<"--------------TestMutiExtend-"<<std::endl;
    TestMutiExtend::main();
    return 0;
}
