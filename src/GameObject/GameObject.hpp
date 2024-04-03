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
    
    public:
        int getId(){
            return this->id;
        }
        string getKodeHuruf(){
            return this->kode_huruf;
        }

        string getNamaGameObject(){
            return this->nama;
        }
        
};

class TradeObject : public GameObject {
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

        int getPrice(){
            return this->price;
        }
        string getType(){
            return this->type;
        }
};

class CultivatedObject : public TradeObject {
    private:
        int cultivateWeight;
        int currentWeight;
    public:
        void incrementWeight(){
            cultivateWeight++;
        }
};

class ProductObject : public TradeObject {
    private:
        string origin;
};

class Recipe : public TradeObject {
    private :
        string* listMaterial;
        int* materialQuantity;
};

#endif