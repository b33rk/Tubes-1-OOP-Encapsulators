#include "Farmers.hpp"

class Petani : public Farmers
{
public:
    Petani(int id, string nama);
    void next();
    void panen(int rowPenyimpanan, int colPenyimpanan, int rowLahan, int colLahan, int prodId, string prodKode, string nama, int prodPrice, string prodType, string origin, int addedWeight);
    void tanam(CultivatedObject *tanaman, int row, int col);

    void cetakLadang();
};

// ask for get in fields