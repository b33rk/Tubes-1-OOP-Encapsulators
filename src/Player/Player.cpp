#include "Player.hpp"
#include "../Exception/Exception.hpp"

Player::Player() : penyimpanan()
{
    berat = 0;
    uang = 0;
    nama = "   ";
    peran = "   ";
}

Player::Player(string nama, string peran, int berat, int uang, int rowPenyimpanan, int colPenyimpanan) : penyimpanan(rowPenyimpanan, colPenyimpanan, "Penyimpanan")
{
    this->nama = nama;
    this->peran = peran;
    this->berat = berat;
    this->uang = uang;
}

string Player::getNama()
{
    return this->nama;
}

string Player::getPeran()
{
    return this->peran;
    return this->peran;
}

int Player::getUang()
{
    return this->uang;
}

void Player::setUang(int uang)
{
    this->uang = uang;
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

vector<string> Player::getAllNamaBarang()
{
    return this->penyimpanan.getAllNamaBarang();
}

int Player::getBerat()
{
    return berat;
}

void Player::setBerat(int x)
{
    this->berat = x;
}

vector<pair<pair<int, int>, pair<string, int>>> Player::getAllPosisiNamaBerat()
{
    throw invalidCommandException();
    return {};
}

void Player::makan(int row, int col)
{   
    TradeObject* makanan = this->getPenyimpanan()[row][col];
    if (makanan->getType() == "   "){
        throw MakananKosongException();
    }
    if (makanan->getType() != "PRODUCT_ANIMAL" && makanan->getType() != "PRODUCT_FRUIT_PLANT")
    {
        throw BukanMakananException();
    }
    else
    {
        int addedWeight = makanan->getAddedWeight();
        this->setBerat(this->getBerat() + addedWeight);
        this->setBarangPenyimpananKosong(row, col);
    }
}

int Player::bayarPajak()
{
    throw invalidCommandException();
}

void Player::pungutPajak(vector<Player *> l, int x)
{
    throw invalidCommandException();
}

void Player::bangunBangunan(Recipe recipe)
{
    throw invalidCommandException();
}

void Player::tambahPlayer(string peran)
{
    throw invalidCommandException();
}

void Player::cetakLadangLahan()
{
    throw invalidCommandException();
}

void Player::tanam(CultivatedObject *tanaman, int row, int col)
{
    throw invalidCommandException();
}

void Player::ternak(CultivatedObject *hewan, int row, int col)
{
    throw invalidCommandException();
}

void Player::panen(int rowPenyimpanan, int colPenyimpanan, int rowLahan, int colLahan, ProductObject *product)
{
    throw invalidCommandException();
}

Field<CultivatedObject> Player::getLahan()
{
    throw invalidCommandException();
}

vector<vector<TradeObject *>> Player::getPenyimpanan()
{
    return this->penyimpanan.getStorage();
}

void Player::beriPangan(int, int, int, int)
{
    throw invalidCommandException();
}
void Player::setBarangPenyimpananKosong(int row, int col)
{
    this->penyimpanan.setKosong(row, col);
}

int Player::getBarangPenyimpananPrice(int row, int col)
{
    return this->penyimpanan.getStorage()[row][col]->getPrice();
}

Field<TradeObject> Player::getPenyimpananField()
{
    return this->penyimpanan;
}
