#ifndef WALIKOTA_HPP
#define WALIKOTA_HPP

#include "Player.hpp"
#include "Petani.hpp"
#include "Peternak.hpp"
#include "../Exception/Exception.hpp"
#include <iostream>
using namespace std;

class Walikota : public Player {
    public:
        Walikota(string nama, int berat, int uang, int rowPenyimpanan, int colPenyimpanan);
        void pungutPajak(vector<Player*> listPlayer, int num_of_players);
        void bangunBangunan(Recipe recipe);
        void tambahPlayer(string peran ) override;
        int bayarPajak() override;
};

#endif