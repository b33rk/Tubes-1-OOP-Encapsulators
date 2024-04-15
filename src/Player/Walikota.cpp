#include "Walikota.hpp"
#include "../GameObject/GameObject.hpp"

void Walikota::pungutPajak(vector<Player*> players){
    int num_of_players = players.size();
    int pajak_temp;
    int total = 0;
    cout << "Cring cring cring...\n";
    cout << "Pajak sudah dipungut!\n\n";
    cout << "Berikut adalah detil dari pemungutan pajak:\n";
    
    for (int i = 0 ; i < num_of_players ; i++){
        if (this->nama != players[i]->getNama()){
            pajak_temp = players[i]->bayarPajak();
            cout << i + 1 << ". "<< players[i]->getNama() << " - " <<  players[i]->getPeran() << ": " << pajak_temp << " gulden\n";
            total += pajak_temp;
        }

    }
    cout << "\n";
    cout << "Negara mendapatkan pemasukan sebesar " << total << " gulden.\n";
    cout << "Gunakan dengan baik dan jangan dikorupsi ya!\n";


}

void Walikota :: bangunBangunan(Recipe recipe){
    // Anggap building adalah tradeobject dengan id yang sama dengan recipe, dan atribut yang sama dengan recipe
    TradeObject* T = new TradeObject(recipe.getPrice(),recipe.getNamaGameObject());
    vector<vector<TradeObject*>> temp_penyimpanan = this->penyimpanan.getBarang();
    for (int row = 0 ; row <  this->penyimpanan.getRow() ; row++){
        for (int col = 0 ; col <  this->penyimpanan.getCol() ; col++){
            if (temp_penyimpanan[row][col]->getKodeHuruf() == "   "){
                this->penyimpanan.setBarang(row,col, T); // Membuat fungsi untuk set barang pada peyimpanan pada row col 
                this->penyimpanan.incrementJumlahIsi(); // membuat fungsi untuk increment jumlahIsi
            }
        }
    }
}

void Walikota :: tambahPlayer(){
    /*
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
    }*/

}