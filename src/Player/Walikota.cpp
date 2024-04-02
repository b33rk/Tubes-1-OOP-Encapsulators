#include "Walikota.hpp"


void Walikota :: pungutPajak(Game& game){
    int num_of_players = game.getJumlahPlayer();
    int pajak_temp;
    cout << "Cring cring cring...\n";
    cout << "Pajak sudah dipungut!\n\n";
    cout << "Berikut adalah detil dari pemungutan pajak:\n";
    
    for (int i = 0 ; i < num_of_players ; i++){
        if (this->nama != game.getPlayerNama(i)){
            pajak_temp = game.bayarPajakPlayer(i);
            cout << i + 1 << ". "<< game.getPlayerNama(i) << " - " ;


        }

    }


}