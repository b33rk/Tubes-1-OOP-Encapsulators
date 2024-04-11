#include "Farmers.hpp"

Farmers::Farmers(int id, string nama, string tipe, int penguranganKKP) : Player(id, nama, tipe, 0){}

int Farmers:: hitungKekayaan(){
    int total = 0;
    vector<vector<CultivatedObject*>> barang = this->lahan.getBarang();
    for (int i = 0; i < lahan.getRow(); i++){
        for(int j = 0; j<lahan.getCol() ; j++){
            if (barang[i][j]->getKodeHuruf() != "  "){
                int price = barang[i][j]->getPrice();
                total += price;
            }
        }
    }
    vector<vector<TradeObject*>> penyimpanan = this->penyimpanan.getBarang();
    for (int i = 0; i < this->penyimpanan.getRow(); i++){
        for(int j = 0; j<this->penyimpanan.getCol() ; j++){
            if (barang[i][j]->getKodeHuruf() != "   "){
                int price = barang[i][j]->getPrice();
                total += price;
            } 
        }
    }
    total += this->kekayaan;
    return total;
}

int Farmers::bayarPajak(){
    int KKP = hitungKekayaan() - this->penguranganKKP;
    int pajak;
    if(KKP > 0){
        float persentase = this->persentasePajak(KKP);
        pajak = KKP*persentase;
    }else{
        pajak = 0;
    }
    if(pajak > this->kekayaan){
        pajak = this->kekayaan;
        this->setKekayaan(0);
    }else{
        this->setKekayaan(this->kekayaan - pajak);
    }
    return pajak;
}