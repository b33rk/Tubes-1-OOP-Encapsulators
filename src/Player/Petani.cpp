#include "Farmers.hpp"
#include "Petani.hpp"

Petani::Petani(string nama, int berat, int uang) : Farmers(nama, "Petani", 13, berat, uang) {}

void Petani::next()
{
    vector<vector<CultivatedObject *>> barang = this->lahan.getStorage();
    for (int i = 0; i < this->lahan.getRow(); i++)
    {
        for (int j = 0; j < this->lahan.getCol(); j++)
        {
            barang[i][j]->incrementWeight();
        }
    }
}

void Petani::tanam(CultivatedObject *tanaman, int row, int col)
{
    this->lahan.setBarang(row, col, tanaman);
}

void Petani::cetakLadang()
{
    this->lahan.cetak();
}
