#ifndef WALIKOTA_HPP
#define WALIKOTA_HPP

#include "Player.hpp"
#include "../GameMaster/GameMaster.hpp"
#include "Petani.hpp"
#include "Peternak.hpp"
#include <iostream>
using namespace std;

class Walikota : public Player {
    public:
        void pungutPajak(Game& game){
        }
        void bangunBangunan(Recipe recipe);
        void tambahPlayer(Game& game, int id, string nama, string peran ) {
        }
};

#endif