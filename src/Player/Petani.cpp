#include "Farmers.hpp"
#include "Petani.hpp"

Petani::Petani(int id, string nama) : Farmers(id, nama, "Petani", 13) {}

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

void Petani::panen(int rowPenyimpanan, int colPenyimpanan, int rowLahan, int colLahan, int prodId, string prodKode, string nama, int prodPrice, string prodType, string origin, int addedWeight)
{
    TradeObject *tumbuhan = this->lahan.getBarang(rowLahan, colLahan);
    ProductObject *product = new ProductObject(prodId, prodKode, nama, prodPrice, prodType, origin, addedWeight);
    this->penyimpanan.setBarang(rowPenyimpanan, colPenyimpanan, product);
    delete this->lahan.getBarang(rowLahan, colLahan);
}

void Petani::tanam(CultivatedObject *tanaman, int row, int col)
{
    this->lahan.setBarang(row, col, tanaman);
}

void Petani::cetakLadang()
{
    this->lahan.cetak();
}
