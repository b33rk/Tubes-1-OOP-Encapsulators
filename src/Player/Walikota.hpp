#ifndef WALIKOTA_HPP
#define WALIKOTA_HPP

#include "Player.hpp"
#include "../GameMaster/GameMaster.hpp"
#include <iostream>
using namespace std;

class Walikota : public Player {
    public:
        void pungutPajak(Game& game){


        }
        void bangun();
        void tambahPlayer(Game& a, string jenis, string nama) {
            // if (jenis == "peternak") {
            //     Peternak *A = new peternak(nama, jenis);
            //     a.tambah(A);
            // } else {
            //     Petani A;
            //     a.tambah(A);
            // }
        }
};

#endif