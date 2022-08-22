#include <iostream>

namespace TestFunction{
    int main();
}
namespace TestFunTemplate{
    int main();
}
int main() {
    TestFunction::main();
    TestFunTemplate::main();
    return 0;
}
