#ifndef FARMERS_HPP
#define FARMERS_HPP

#include "Player.hpp"
#include <vector>

class Farmers : public Player
{
public:
    Field<CultivatedObject> lahan;
    int penguranganKKP;

public:
    Farmers(string nama, string tipe, int penguranganKKP, int berat, int uang, int rowPenyimpanan, int colPenyimpanan, int rowLahan, int colLahan, string tipeLahan);
    int hitungKekayaan();
    int bayarPajak();
    void panen(int, int, int, int, ProductObject *);
    void setBarangFirstLahan(CultivatedObject *) override;
    void setBarangLahan(int row, int col, CultivatedObject *) override;
    vector<pair<pair<int, int>, pair<string, int> > > getAllPosisiNamaBerat() override;
    Field<CultivatedObject> getLahan();
    virtual vector<TradeObject *> ambilUniqueValueLahan();
    void cetakLadangLahan();
};

#endif