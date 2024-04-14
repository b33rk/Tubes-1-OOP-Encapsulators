#include "Farmers.hpp"

Farmers::Farmers(int id, string nama, string tipe, int penguranganKKP, int uang) : Player(id, nama, tipe, 0,uang) {}

int Farmers::hitungKekayaan()
{
    int total = 0;
    vector<vector<CultivatedObject *>> barang = this->lahan.getStorage();
    for (int i = 0; i < lahan.getRow(); i++)
    {
        for (int j = 0; j < lahan.getCol(); j++)
        {
            if (barang[i][j]->getKodeHuruf() != "  ")
            {
                int price = barang[i][j]->getPrice();
                total += price;
            }
        }
    }
    vector<vector<TradeObject *>> penyimpanan = this->penyimpanan.getStorage();
    for (int i = 0; i < this->penyimpanan.getRow(); i++)
    {
        for (int j = 0; j < this->penyimpanan.getCol(); j++)
        {
            if (barang[i][j]->getKodeHuruf() != "   ")
            {
                int price = barang[i][j]->getPrice();
                total += price;
            }
        }
    }
    total += this->kekayaan;
    return total;
}



void Farmers::panen(int rowPenyimpanan, int colPenyimpanan, int rowLahan, int colLahan, int prodId, string prodKode, string nama, int prodPrice, string prodType, string origin, int addedWeight)
{
    ProductObject *product = new ProductObject(prodId, prodKode, nama, prodPrice, prodType, origin, addedWeight);
    this->penyimpanan.setBarang(rowPenyimpanan, colPenyimpanan, product);
    delete this->lahan.getBarang(rowLahan, colLahan);
}

int Farmers::bayarPajak()
{
    int KKP = hitungKekayaan() - this->penguranganKKP;
    int pajak;
    if (KKP > 0)
    {
        float persentase = this->persentasePajak(KKP);
        pajak = KKP * persentase;
    }
    else
    {
        pajak = 0;
    }
    if (pajak > this->kekayaan)
    {
        pajak = this->kekayaan;
        this->setKekayaan(0);
    }
    else
    {
        this->setKekayaan(this->kekayaan - pajak);
    }
    return pajak;
}