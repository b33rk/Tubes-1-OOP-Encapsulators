#include "Player.hpp"
#include <vector>

class Farmers : public Player
{
protected:
    Field<CultivatedObject> lahan;
    int penguranganKKP;

public:
    Farmers(int id, string nama, string tipe, int penguranganKKP);
    int hitungKekayaan();
    int bayarPajak();
};