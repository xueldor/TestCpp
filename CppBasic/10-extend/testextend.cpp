#include <iostream>
using namespace std;

namespace TestExtend {
    class A {
    public :
        void show() { cout << "A show" << endl; }

        virtual ~A() {}
    };

    class B : public A {
    public :
        virtual void show() { cout << "B show" << endl; }
    };

    class C : public B {
    public:
        void show() { cout << "C show" << endl; }
    };

    class D : public C {
    public:
        void show() { cout << "D show" << endl; }
    };

    int main_extend() {
        A *a = new B;
        a->show();//A show
        B* b = static_cast<B*>(a);
        b->show();//B show

        A* aa = new C;
        aa->show();//A show
        B* bb = static_cast<B*>(aa);
        bb->show();//C show
        C* cc = static_cast<C*>(aa);
        cc->show();//C show

        C* ccc = new D;
        ccc->show();//D show
        return 0;

    }
}