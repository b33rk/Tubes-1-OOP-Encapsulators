#include "Peternak.hpp"
#include "../Exception/Exception.hpp"

Peternak::Peternak(int id, string nama, int uang) : Farmers(id, nama, "Peternak", 0, uang){};

void Peternak::beriPangan(int rowPenyimpanan, int colPenyimpanan, int rowLahan, int colLahan)
{
    TradeObject *makanan = this->penyimpanan.getBarang(rowPenyimpanan, colPenyimpanan);
    TradeObject *hewan = this->lahan.getBarang(rowLahan, colLahan);
    if ((makanan->getType() == "PRODUCT_FRUIT_PLANT" && ((hewan->getType() == "HERBIVORE") || (hewan->getType() == "OMNIVORE"))) || (makanan->getType() == "PRODUCT_ANIMAL" && (hewan->getType() == "CARNIVORE") || (hewan->getType() == "OMNIVORE")))
    {
        int weightTambah = makanan->getAddedWeight();
        (this->lahan.getBarang(rowLahan, colLahan))->addWeight(weightTambah);
        TradeObject *kosong = new TradeObject();
        this->penyimpanan.setBarang(rowPenyimpanan, colPenyimpanan, kosong);
    }
    else
    {
        
        throw MakananSalahException() ;
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