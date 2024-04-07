#include "Player.hpp"
#include "../GameMaster/GameMaster.hpp"

class Petani : public Player {
    private:
        Field ladang;
    public:
        void next(){
            for (int i = 0; i < ladang.getJumlahIsi(); i++){
                tanaman[i].incrementWeight();
            }
            nextTurn();
        }
        void panen(int, int) {
            // a;
            // product b(nama)
        }
        void tanam();
        void bayarPajak();
        void cetakLadang(){
            ladang.cetak();
        }
};