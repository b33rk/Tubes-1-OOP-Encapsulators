#include "Player.hpp"
#include <vector>

class Farmers : public Player
{
protected:
    Field<CultivatedObject> lahan;
    int penguranganKKP;

public:
    Farmers(int id, string nama, string tipe, int penguranganKKP, int uang);
    int hitungKekayaan();
    int bayarPajak();
    void panen(int rowPenyimpanan, int colPenyimpanan, int rowLahan, int colLahan, int prodId, string prodKode, string nama, int prodPrice, string prodType, string origin, int addedWeight);
};