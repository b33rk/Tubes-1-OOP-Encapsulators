#ifndef __GAMEOBJECT__
#define __GAMEOBJECT__

#include <iostream>
#include <vector>

// #include <string.h>

using namespace std;

// TODO : Buat copy constructor buat smw kelas

class GameObject {
    protected:
        int id;
        string kode_huruf;
        string nama;
    public:
        GameObject(){
            id = 0;
            kode_huruf = "null";
            nama = "null";
        }
        GameObject(const GameObject& other){
            this->id = other.id;
            this->kode_huruf = other.kode_huruf;
            this->nama = other.nama;
        }
        GameObject(int id, string kode, string name){
            this->id = id;
            kode_huruf = kode;
            nama = name;
        }
};

class TradeObject : public GameObject {
    protected:
        int price;
        string type;
    public:
        TradeObject() : GameObject(){
            price = 0;
            type = "null";
        }
        TradeObject(int p, string t) : GameObject(){
            price = p;
            t = type;
        }
        TradeObject(const TradeObject& other) : GameObject(other){
            this->price = other.price;
            this->type = other.type;
        }
        TradeObject(int id, string kode, string name, int p, string t) : GameObject(id, kode, name){
            price = p;
            type = t;
        }
        void cetakBarang(){
            cout << " " << kode_huruf <<" |";
        }
        void setNama(string newNama) {
            nama = newNama;
        }
        void setKode(string newKode) {
            kode_huruf = newKode;
        }
        string getKode() {
            return kode_huruf;
        }
        string getNama() {
            return nama;
        }
};

class CultivatedObject : public TradeObject {
    private:
        int cultivateWeight;
        int currentWeight;
    public:
        CultivatedObject() : TradeObject(){
            cultivateWeight = 0;
            currentWeight = 0;
        }
        CultivatedObject(const CultivatedObject& other) : TradeObject(other){
            this->cultivateWeight = other.cultivateWeight;
            this->currentWeight = other.currentWeight;
        }
        CultivatedObject(int id, string kode, string name, string type, int dur, int price) : TradeObject(id, kode, name, price, type){
            this->cultivateWeight = dur;
            this->currentWeight = 0;
        }
        void incrementWeight(){
            cultivateWeight++;
        }
        void cetak(){
            cout << id << " " << kode_huruf << " " << nama << " " << type << " " << cultivateWeight << " " << price;
        }
};

class ProductObject : TradeObject {
    private:
        string origin;
        int added_weight;
    public:
        ProductObject() : TradeObject(){
            origin = "null";
        }
        ProductObject(const ProductObject& other) : TradeObject(other){
            this->origin = other.origin;
        }
        ProductObject(int id, string kode, string name, string type, string origin, int added_weight, int price) : TradeObject(id, kode, name, price, type){
            this->origin = origin;
            this->added_weight = added_weight;
        }
        void cetak(){
            cout << id << " " << kode_huruf << " " << nama << " " << type << " " << origin << " " << added_weight << " " << price ;
        }
};

class Recipe : TradeObject {
    private :
        vector<string> listMaterial;
        vector<int> materialQuantity;
    public:
        Recipe() : TradeObject(){
            listMaterial.clear();
            materialQuantity.clear();
        }
        Recipe(const Recipe& other) : TradeObject(other){
            for(auto &material: other.listMaterial){
                listMaterial.push_back(material);
            }
            for(auto &quantity: other.materialQuantity){
                materialQuantity.push_back(quantity);
            }
        }
        Recipe(int id, string kode, string name, int p, vector<string> listMaterial, vector<int> materialQuantity, string t = "recipe") : TradeObject(id, kode, name, p, t){
            for(auto &material: listMaterial){
                this->listMaterial.push_back(material);
            }
            for(auto &quantity: materialQuantity){
                this->materialQuantity.push_back(quantity);
            }
        }
        void cetak(){
            cout << id << " " << kode_huruf << " " << nama << " " << price << " ";
            for(int i = 0; i < listMaterial.size(); ++i){
                cout << listMaterial[i] << " " << materialQuantity[i] << " ";
            }
        }
};

#endif