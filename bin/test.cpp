#include <iostream>
#include <string.h>
#include <fstream>
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
    /*
    ofstream file("/bin/tes/uwu.txt");
    file << "kekekekkeke";
    file.close();*/
    
    try{
        Game g;
        g.muat_semua_config();
        g.cetak_state();
        g.muat_player_state();
        cout << "PLAYER NOW: " << endl;
        for(auto &x: g.listPlayer){
            cout << x->getNama() << endl;
        }
        
        g.simpan();
    }catch(const unsigned long c){
        cout << c << endl;
    }catch(const char* c){
        cout << c << endl;
    }
}