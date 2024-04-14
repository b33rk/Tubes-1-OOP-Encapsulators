#include "Farmers.hpp"

class Peternak : public Farmers
{
public:
    Peternak(int id, string nama, int uang);
    void beriPangan(int rowPenyimpanan, int colPenyimpanan, int rowLahan, int colLahan);

    void ternak(CultivatedObject *hewan, int row, int col);

    void cetakLahan();
};
