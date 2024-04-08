#ifndef __GAMEOBJECT__
#define __GAMEOBJECT__

#include <iostream>
#include <string>
// #include <string.h>

using namespace std;

class GameObject {
    protected:
        int id;
        string kode_huruf;
        string nama;
    
    public:

        // constructors
        GameObject(int id, string kode_huruf, string nama){
            this->id = id;
            this->kode_huruf = kode_huruf;
            this->nama = nama;
        }
        GameObject() : GameObject(0,"   ","   "){}
        
        int getId(){
            return this->id;
        }
        string getKodeHuruf(){
            return this->kode_huruf;
        }

        string getNamaGameObject(){
            return this->nama;
        }
        virtual void incrementWeight(){};
        
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
        void incrementWeight() override{
            cultivateWeight++;
        }
};

class ProductObject : public TradeObject {
    private:
        string origin;
};


// recipe seharusnya bukan tradeobject, gabisa di trade soalnya
class Recipe : public GameObject {
    private :
        int price;
        vector<string> listMaterial;
        vector<int> materialQuantity;
    public:
        Recipe() : GameObject(){
            this->price = 0;
        }
        Recipe(int id, string kode_huruf, string nama, int price, vector<string>listMaterials, vector<int> materialQuantity) : GameObject(id,kode_huruf,nama){
            for (int i = 0; i < listMaterial.size() ; i++){
                this->listMaterial.push_back(listMaterials[i]);
                this->materialQuantity.push_back(materialQuantity[i]);
        
            }
        }
        int getPrice(){
            return this->price;
        }
};

#endif