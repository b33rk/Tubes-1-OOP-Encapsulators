#include "Farmers.hpp"

Farmers::Farmers(string nama, string tipe, int penguranganKKP, int berat, int uang, int rowPenyimpanan, int colPenyimpanan, int rowLahan, int colLahan, string tipeLahan) : lahan(rowLahan, colLahan, tipe), Player(nama, tipe, berat, uang, rowPenyimpanan, colPenyimpanan)
{

    this->penguranganKKP = penguranganKKP;
}

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

                // cout << barang[i][j]->getKodeHuruf() << endl;
                int price = barang[i][j]->getPrice();
                total += price;
            }
        }
    }
    // cout << "selesai llop 1" << endl;
    vector<vector<TradeObject *>> penyimpanan = this->penyimpanan.getStorage();

    for (int i = 0; i < this->penyimpanan.getRow(); i++)
    {
        for (int j = 0; j < this->penyimpanan.getCol(); j++)
        {

            if (penyimpanan[i][j]->getKodeHuruf() != "   ")
            {

                int price = penyimpanan[i][j]->getPrice();
                total += price;
            }
        }
    }
    total += this->uang;
    return total;
}

void Farmers::panen(int rowPenyimpanan, int colPenyimpanan, int rowLahan, int colLahan, ProductObject* product)
{
    this->penyimpanan.setBarang(rowPenyimpanan, colPenyimpanan, product);
    delete this->lahan.getBarang(rowLahan, colLahan);
    CultivatedObject *kosong = new CultivatedObject();
    this->setBarangLahan(rowLahan, colLahan, kosong);
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
    if (pajak > this->uang)
    {
        pajak = this->uang;
        this->setUang(0);
    }
    else
    {
        this->setUang(this->uang - pajak);
    }
    return pajak;
}

void Farmers::cetakLadangLahan() {
    this->lahan.cetak();
}

void Farmers ::setBarangFirstLahan(CultivatedObject *object)
{
    this->lahan.insertFirst(object);
}

void Farmers ::setBarangLahan(int row, int col, CultivatedObject *object)
{
    this->lahan.setBarang(row, col, object);
}

vector<pair<pair<int, int>, pair<string, int>>> Farmers::getAllPosisiNamaBerat()
{
    return this->lahan.getAllPosisiNamaBerat();
}