#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../GameObject/GameObject.hpp"
#include "../FieldObject/Field.hpp"

// id gak ada!!!
class Player{
    protected:
        int kekayaan;
        int berat;
        string nama;
        string peran;
        Field<TradeObject> penyimpanan;
    public:
        Player(string nama, string peran){
            this->nama = nama;
            this->peran = peran;
            this->berat = 0;
            this->kekayaan = 0;
        }
        ~Player() {
        }
        void virtual next(){}
        void virtual muat();
        void virtual jual(int, int);
        void virtual beli(TradeObject*, int);
        void virtual makan();
        void virtual tambahPlayer(){
            throw "not exist";
        }
        // throw utk yg lain selain walikota
        void virtual cetakPenyimpanan(){
            penyimpanan.cetak();
        }

        virtual int bayarPajak();
        void virtual cetakLahan();
        string getNama(){
            return this->nama;
        }
        string getPeran(){
            return this->getPeran();
        }
        void setKekayaan(int kekayaan){
            this->kekayaan = kekayaan;
        }
        int getBerat(){
            return this->berat;
        }
        void setBerat(int beratBaru){
            this->berat = beratBaru;
        }
        void masukkanPenyimpanan(TradeObject* t){
            vector<vector<TradeObject*>> barangSendiri = penyimpanan.getBarang();
            for(int i = 0; i < penyimpanan.getRow(); ++i){
                for(int j = 0; j < penyimpanan.getCol(); ++j){
                    if(barangSendiri[i][j]->notExist()){
                        penyimpanan.setBarang(i, j, t);
                        return;
                    }
                }
            }
            throw "masukkanPenyimpanan: penyimpanan penuh!";
        }
};

#endif