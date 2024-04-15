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
            kode_huruf = "   ";
            nama = "   ";
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
        int getId(){
            return this->id;
        }

        string getKodeHuruf(){
            return this->kode_huruf;
        }

        string getNamaGameObject(){
            return this->nama;
        }

        bool notExist(){
            return this->kode_huruf == "   ";
        }
        
        virtual void incrementWeight(){};
};

class TradeObject : public GameObject {
    private:
        int price;
        string type;
        //vector<string> ngasilin; // KODE HURUF PRODUCT OBJECT NYA 
    public:
        TradeObject() : GameObject(){
            price = 0;
            type = "   ";
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
        //string type; // string "hewan" / "tumbuhan"
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
        
        void incrementWeight() override{
            cultivateWeight++;
        }

        virtual void addWeight(ProductObject* p = nullptr){
            throw "BaseClass: addWeight";
        }

        void cetak(){
            cout << id << " " << kode_huruf << " " << nama << " " << getType() << " " << cultivateWeight << " " << getPrice();
        }
};

class Tumbuhan : public CultivatedObject{
public:
    void addWeight(ProductObject* p = nullptr) override{}
};

class Hewan : public CultivatedObject{
public:
    void addWeight(ProductObject* p = nullptr) override{}
};

// TradeObject -> ProductObject

class ProductObject : public TradeObject {
    private:
        string origin;
        int added_weight; // APP -> herbivor, COM -> cow meat karnivor 
    public:
        ProductObject() : TradeObject(){
            origin = "   ";
        }
        ProductObject(const ProductObject& other) : TradeObject(other){
            this->origin = other.origin;
        }
        ProductObject(int id, string kode, string name, string type, string origin, int added_weight, int price) : TradeObject(id, kode, name, price, type){
            this->origin = origin;
            this->added_weight = added_weight;
        }
        void cetak(){
            cout << id << " " << kode_huruf << " " << nama << " " << getType() << " " << origin << " " << added_weight << " " << getPrice() ;
        }
};

class Recipe : public GameObject {
    private :
        int price;
        vector<string> listMaterial;
        vector<int> materialQuantity;
    public:
        Recipe() : GameObject(){
            listMaterial.clear();
            materialQuantity.clear();
        }
        Recipe(const Recipe& other) : GameObject(other){
            for(auto &material: other.listMaterial){
                listMaterial.push_back(material);
            }
            for(auto &quantity: other.materialQuantity){
                materialQuantity.push_back(quantity);
            }
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
        void cetak(){
            cout << id << " " << kode_huruf << " " << nama << " " << price << " ";
            for(int i = 0; i < listMaterial.size(); ++i){
                cout << listMaterial[i] << " " << materialQuantity[i] << " ";
            }
        }
};

#endif