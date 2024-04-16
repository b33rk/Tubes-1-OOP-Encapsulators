#include "Peternak.hpp"
#include "../Exception/Exception.hpp"
#include "../GameObject/GameObject.hpp"

Peternak::Peternak(string nama, int berat, int uang, int rowPenyimpanan, int colPenyimpanan, int rowLahan, int colLahan) : Farmers(nama, "Peternak", 11, berat, uang, rowPenyimpanan, colPenyimpanan, rowLahan, colLahan, "Peternakan"){};

void Peternak::beriPangan(int rowPenyimpanan, int colPenyimpanan, int rowLahan, int colLahan)
{
    TradeObject *makanan = this->penyimpanan.getBarang(rowPenyimpanan, colPenyimpanan);
    CultivatedObject *hewan = this->lahan.getBarang(rowLahan, colLahan);
    if ((makanan->getType() == "PRODUCT_FRUIT_PLANT" && ((hewan->getType() == "HERBIVORE") || (hewan->getType() == "OMNIVORE"))) || (makanan->getType() == "PRODUCT_ANIMAL" && (hewan->getType() == "CARNIVORE") || (hewan->getType() == "OMNIVORE")))
    {
        int weightTambah = makanan->getAddedWeight();
        (this->lahan.getBarang(rowLahan, colLahan))->addWeight(weightTambah);
        //TradeObject *kosong = new TradeObject();
        this->penyimpanan.setKosong(rowPenyimpanan, colPenyimpanan);
    }
    else
    {

        throw MakananSalahException();
    }
}

void Peternak::ternak(CultivatedObject *hewan, int row, int col)
{
    this->lahan.setBarang(row, col, hewan);
}

void Peternak::cetakLahan()
{
    lahan.cetak();
}

vector<TradeObject *> Farmers::ambilUniqueValueLahan(){
    return this->lahan.getUniqueValue();
}