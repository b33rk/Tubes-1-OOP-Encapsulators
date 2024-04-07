#include "Player.hpp"
#include "../GameMaster/GameMaster.hpp"

class Walikota : public Player {
    public:
        void pungutPajak();
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