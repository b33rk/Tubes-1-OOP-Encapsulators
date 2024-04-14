#ifndef WALIKOTA_HPP
#define WALIKOTA_HPP

#include "Player.hpp"
#include "../GameMaster/GameMaster.hpp"
#include "Petani.hpp"
#include "Peternak.hpp"
#include "../Exception/Exception.hpp"
#include <iostream>
using namespace std;

class Walikota : public Player {
    public:
        Walikota(int id, string nama, int berat, int uang) ;
        void pungutPajak(Player** listPlayer, int num_of_players){
        }
        void bangunBangunan(Recipe recipe);
        void tambahPlayer(string peran ) {
        }
        int bayarPajak() override;
};

#endif