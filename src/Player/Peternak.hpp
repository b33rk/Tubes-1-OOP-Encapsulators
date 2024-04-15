#ifndef PETERNAK_HPP
#define PETERNAK_HPP

#include "Player.hpp"
#include "../GameObject/GameObject.hpp"
#include "Farmers.hpp"

class Peternak : public Farmers
{
public:
    Peternak(string nama, int berat, int uang, int rowPenyimpanan, int colPenyimpanan, int rowLahan, int colLahan);
    void beriPangan(int rowPenyimpanan, int colPenyimpanan, int rowLahan, int colLahan);

    void ternak(CultivatedObject *hewan, int row, int col);

    void cetakLahan();
};

#endif