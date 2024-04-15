#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

class A {
    public:
        virtual void f(){cout << "a" << endl;}
};

class B : public A {
    public:
        void f(){cout << "uooo" << endl;}
};

class C {
    public:
        int size;
        A** X;

        C(int n) {
            size = n;
            X = new A*[size];
            for (int i = 0; i < size; ++i) {
                X[i] = nullptr;
            }
        }

        ~C() {
            for (int i = 0; i < size; ++i) {
                delete X[i];
            }
            delete[] X;
        }

        void addX(A* x){
            this->X[0] = x;
        }

        A* getMember(int i){
            return X[i];
        }
};

int main() {
    A* alooo = new B;
    C H(1);
    H.addX(alooo);
    H.getMember(0)->f();
}