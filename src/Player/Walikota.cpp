#include "Walikota.hpp"
#include <vector>
#include <utility>
#include "Player.hpp"


Walikota :: Walikota(string nama, int berat, int uang, int rowPenyimpanan, int colPenyimpanan) : Player(nama, "Walikota",berat,uang, rowPenyimpanan,colPenyimpanan){}

int Walikota :: bayarPajak(){
    throw invalidCommandException();
    
}

void Walikota :: pungutPajak(vector<Player*> listPlayer, int num_of_players){

    int pajak_temp;
    int total = this->getUang();
    cout << "Cring cring cring...\n";
    cout << "Pajak sudah dipungut!\n\n";
    cout << "Berikut adalah detil dari pemungutan pajak:\n";
    
    for (int i = 0 ; i < num_of_players ; i++){
        if (listPlayer[i]->getPeran() != "Walikota"){
            pajak_temp = listPlayer[i]->bayarPajak();
            cout << i + 1 << ". "<< listPlayer[i]->getNama() << " - " <<  listPlayer[i]->getPeran() << ": " << pajak_temp << " gulden\n";
            total += pajak_temp;
        }

    }
    cout << "\n";
    cout << "Negara mendapatkan pemasukan sebesar " << total << " gulden.\n";
    cout << "Gunakan dengan baik dan jangan dikorupsi ya!\n";
    this->setUang(total);
}

void Walikota :: bangunBangunan(Recipe recipe){
    // Anggap building adalah tradeobject dengan id yang sama dengan recipe, dan atribut yang sama dengan recipe
    vector<pair<int,int>> location;
    vector<string> materials = recipe.getListMaterial();
    vector<int> materialQuantity = recipe.getMaterialQuantity();
    bool complete = true;
    bool allComplete = true;
    for (int i = 0 ; i < materials.size() ; i++){
        complete = false;
        for (int r = 0 ; r < this->penyimpanan.getRow() && !complete ; r++){
            for (int c = 0 ; c < this->penyimpanan.getCol()  && !complete; c++){
                if (this->penyimpanan.getBarang(r,c)->getNama() == materials[i]){
                    materialQuantity[i] -= 1;
                    location.push_back(make_pair(r,c));
                    if (materialQuantity[i] == 0){
                        complete = true;
                    }
                }
            }
        }
        allComplete = allComplete && complete;
        
    }

    if (!allComplete){
        throw KurangMaterialException(materials,materialQuantity) ;
    }

    for (auto &pair : location){
        this->penyimpanan.setKosong(pair.first,pair.second);
    }

    TradeObject* T = new TradeObject(recipe.getId(),recipe.getKodeHuruf(),recipe.getNamaGameObject(),recipe.getPrice(),"BANGUNAN");
    vector<vector<TradeObject*>> temp_penyimpanan = this->penyimpanan.getStorage();
    for (int row = 0 ; row <  this->penyimpanan.getRow() ; row++){
        for (int col = 0 ; col <  this->penyimpanan.getCol() ; col++){
            if (temp_penyimpanan[row][col]->getKodeHuruf() == "   "){
                this->penyimpanan.setBarang(row,col, T); // Membuat fungsi untuk set barang pada peyimpanan pada row col 
                this->penyimpanan.incrementJumlahIsi(); // membuat fungsi untuk increment jumlahIsi
            }
        }
    }
}

void Walikota :: tambahPlayer(string peran ){
    // if (peran == "Peternak"){
    //     Peternak* player = new Peternak(id,nama);
    //     game.tambahGamePlayer(player);
        
    // }
    // else if (peran == "Petani"){
    //     Petani* player = new Petani(id,nama);
    //     game.tambahGamePlayer(player);

    // }
    // else if (peran == "Walikota"){
    //     throw "Walikota hanya boleh ada 1\n";
    // }
    // else {
    //     throw "Peran tidak valid\n";
    // }

    if (this->getUang() < 50){
        throw uangTidakCukupException();
    }
    if (peran != "Peternak" && peran != "Petani"){
        throw tambahPlayerInvalidException();
    }


}