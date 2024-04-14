#include "Petani.hpp"

Petani::Petani(int id, string nama) : Farmers(id,nama,"Petani"){}

void Petani::next(){
    vector<vector<CultivatedObject*>> barang= this->lahan.getBarang();
    for(int i = 0; i < this->lahan.getRow(); i++){
        for(int j = 0; j< this->lahan.getCol() ; j++){
            barang[i][j]->incrementWeight();
        }
    }
}

ProductObject Petani::panen(int row, int col){
    delete this->getBarang(row, col);
}

void Petani::tanam(CultivatedObject* tanaman, int row, int col){
    this->lahan.setBarang(row,col,tanaman);         
}

void Petani:: cetakLadang(){
    this->lahan.cetak();
}

