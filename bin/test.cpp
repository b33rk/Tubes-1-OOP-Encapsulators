#include <iostream>
#include <string.h>
#include "../src/GameMaster/GameMaster.hpp"

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
    try{
        Game g;
        g.muat_semua_config();
        g.cetak_state();
    }catch(const unsigned long c){
        cout << c << endl;
    }catch(const char* c){
        cout << c << endl;
    }
}