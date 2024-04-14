#include "Farmers.hpp"

class Petani : public Farmers {
    public:
        Petani(int id, string nama);
        void next();
        ProductObject panen(int row, int col) {
            // a;
            // product b(nama)
        }
        void tanam(CultivatedObject* tanaman, int row, int col);


        void cetakLadang();
};


// ask for get in fields