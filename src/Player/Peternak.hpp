#include "Farmers.hpp"

class Peternak : public Farmers {
    public:

        Peternak(int id, string nama);
        void beriMakan(int rowPenyimpanan, int colPenyimpanan, int rowLahan, int colLahan, int addWeight);

        void ternak(CultivatedObject* hewan, int row, int col);

        void cetakLahan();
};

