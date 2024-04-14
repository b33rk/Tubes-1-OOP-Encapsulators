#include "Player.hpp"

Player::Player(int id, string nama, string peran, int berat)
{
    this->id = id;
    this->nama = nama;
    this->peran = peran;
    this->berat = berat;
}

string Player::getNama()
{
    return this->nama;
}

string Player::getPeran()
{
    return this->getPeran();
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