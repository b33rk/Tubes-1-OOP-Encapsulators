#include "Walikota.hpp"


void Walikota :: pungutPajak(Game& game){
    int num_of_players = game.getJumlahPlayer();
    int pajak_temp;
    int total = 0;
    cout << "Cring cring cring...\n";
    cout << "Pajak sudah dipungut!\n\n";
    cout << "Berikut adalah detil dari pemungutan pajak:\n";
    
    for (int i = 0 ; i < num_of_players ; i++){
        if (this->nama != game.getPlayerNama(i)){
            pajak_temp = game.bayarPajakPlayer(i);
            cout << i + 1 << ". "<< game.getPlayerNama(i) << " - " <<  game.getPeranPlayer(i) << ": " << pajak_temp << " gulden\n";
            total += pajak_temp;
        }

    }
    cout << "\n";
    cout << "Negara mendapatkan pemasukan sebesar " << total << " gulden.\n";
    cout << "Gunakan dengan baik dan jangan dikorupsi ya!\n";


}

void Walikota :: bangunBangunan(Recipe recipe){
    // this->penyimpanan
}

void Walikota :: tambahPlayer(Game& game, int id, string nama, string peran ){
    if (peran == "Peternak"){
        Peternak* player = new Peternak(id,nama);
        game.tambahGamePlayer(player);
        
    }
    else if (peran == "Petani"){
        Petani* player = new Petani(id,nama);
        game.tambahGamePlayer(player);

    }
    else if (peran == "Walikota"){
        throw "Walikota hanya boleh ada 1\n";
    }
    else {
        throw "Peran tidak valid\n";
    }

}