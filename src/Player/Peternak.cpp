#include "Peternak.hpp"

Peternak::Peternak(int id, string nama): Farmers(id,nama,"Peternak", 0){};

void Peternak::beriMakan(int rowPenyimpanan, int colPenyimpanan, int rowLahan, int colLahan, int weightTambah){
    TradeObject *kosong = new TradeObject();
    this->penyimpanan.setBarang(rowPenyimpanan, colPenyimpanan, kosong);
    this->lahan.getBarang(rowLahan, colLahan).addWeight(weightTambah);
}

void Peternak::ternak(CultivatedObject* hewan, int row, int col){
    this->lahan.setBarang(row,col,hewan);
}

void Peternak::cetakLahan(){
    lahan.cetak();
}