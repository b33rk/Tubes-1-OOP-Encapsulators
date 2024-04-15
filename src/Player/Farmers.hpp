#include "Player.hpp"
#include <vector>

class Farmers : public Player
{
protected:
    Field<CultivatedObject> lahan;
    int penguranganKKP;

public:
    Farmers(string nama, string tipe, int penguranganKKP, int berat, int uang, int rowPenyimpanan, int colPenyimpanan, int rowLahan, int colLahan);
    int hitungKekayaan();
    int bayarPajak();
    void panen(int rowPenyimpanan, int colPenyimpanan, int rowLahan, int colLahan, int prodId, string prodKode, string nama, int prodPrice, string prodType, string origin, int addedWeight);
    void setBarangFirstLahan(CultivatedObject *) override;
    void setBarangLahan(int row, int col, CultivatedObject *) override;
    vector<pair<pair<int, int>, pair<string, int>>> getAllPosisiNamaBerat();
};