#ifndef __GAMEOBJECT__
#define __GAMEOBJECT__

#include <iostream>
// #include <string.h>

using namespace std;

class GameObject {
    protected:
        int id;
        string kode_huruf;
        string nama;
};

class TradeObject : GameObject {
    private:
        int price;
        string type;
    public:
        TradeObject(int p, string t){
            price = p;
            t = type;
        }
        void cetakBarang(){
            cout << " " << kode_huruf <<" |";
        }
};

class CultivatedObject : TradeObject {
    private:
        int cultivateWeight;
        int currentWeight;
    public:
        void incrementWeight(){
            cultivateWeight++;
        }
};

class ProductObject : TradeObject {
    private:
        string origin;
};

class Recipe : GameObject {
    private :
        string* listMaterial;
        int* materialQuantity;
};

#endif