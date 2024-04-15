#include "Player.hpp"
#include "../Exception/Exception.hpp"

Player::Player(string nama, string peran, int berat, int uang, int rowPenyimpanan, int colPenyimpanan)
{
    // this->id = id;
    Field<TradeObject> penyimpananTemp(rowPenyimpanan, colPenyimpanan);
    this->nama = nama;
    this->peran = peran;
    this->berat = berat;
    this->uang = uang;
    this->penyimpanan = penyimpananTemp;
}

string Player::getNama()
{
    return this->nama;
}

string Player::getPeran()
{
    return this->getPeran();
}

int Player::getUang()
{
    return this->uang;
}

void Player::setUang(int uang)
{
    this->uang = uang;
}
void Player::setKekayaan(int kekayaan)
{
    this->kekayaan = kekayaan;
}

void Player::cetakPenyimpanan()
{
    this->penyimpanan.cetak();
}

float Player::persentasePajak(int KKP)
{
    if (KKP <= 6)
    {
        return 0.5;
    }
    else if (KKP <= 25)
    {
        return 0.15;
    }
    else if (KKP <= 50)
    {
        return 0.25;
    }
    else if (KKP <= 500)
    {
        return 0.3;
    }
    else
    {
        return 0.35;
    }
}

void Player::setBarangFirstPenyimpanan(TradeObject *p)
{
    this->penyimpanan.insertFirst(p);
}

void Player::setBarangFirstLahan(CultivatedObject *p)
{
    throw invalidCommandException();
}
void Player::setBarangPenyimpanan(int row, int col, TradeObject *p)
{
    this->penyimpanan.setBarang(row, col, p);
}

void Player::setBarangLahan(int row, int col, CultivatedObject *c)
{
    throw invalidCommandException();
}

void Player::setBarangPenyimpanan(int row, int col, TradeObject *t)
{
}

void Player::setBarangLahan(int row, int col, CultivatedObject *c)
{
}

vector<string> Player::getAllNamaBarang()
{
    return this->penyimpanan.getAllNamaBarang();
}

void Player::makan(TradeObject *makanan)
{
    if (makanan->getType() != "PRODUCT_ANIMAL" || makanan->getType() != "PRODUCT_PLANT_FRUIT")
    {
        throw BukanMakananException();
    }
    else
    {
        int addedWeight = makanan->getAddedWeight();
        this->setBerat(this->getBerat() + addedWeight);
    }
}