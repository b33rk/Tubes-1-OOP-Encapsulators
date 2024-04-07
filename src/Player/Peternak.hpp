#include "Player.hpp"

class Petani : public Player {
    private:
        Field lahan;
    public:
        void beriMakan();
        void ternak();
        void bayarPajak();
        void cetakLahan(){
            lahan.cetak();
        }
};

