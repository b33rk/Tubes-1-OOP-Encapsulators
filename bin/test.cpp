#include <iostream>
#include <string.h>

using namespace std;

class A {
    public:
        virtual void f(){}
};

class B : public A {
    public:
        void f(){cout << "uooo" << endl;}
};

int main() {
    A* alooo = new B;
    alooo->f();
}