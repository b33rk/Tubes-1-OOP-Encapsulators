#include "Exception/Exception.hpp"
#include "FieldObject/Field.hpp"
#include "GameMaster/GameMaster.hpp"
#include "GameObject/GameObject.hpp"
#include "Player/Farmers.hpp"
#include "Player/Petani.hpp"
#include "Player/Peternak.hpp"
#include "Player/Player.hpp"
#include "Player/Walikota.hpp"
#include "Command/Command.hpp"
// #include "Shop/Shop.hpp"

bool finishGame(vector<Player*> listPlayer, int goalUang, int goalBerat) {
    for(int i = 0; i < listPlayer.size(); i++) {
        if(listPlayer[i]->getUang() >= goalUang && listPlayer[i]->getBerat() >= goalBerat) {
            return true;
        }
    }

    return false;
}


int main() {
    // welcoming
    
    const string ENCAPSULATORS = "▄▄▄▄▄▄▄ ▄▄    ▄ ▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄ ▄▄   ▄▄ ▄▄▄     ▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄ ▄▄▄▄▄▄   ▄▄▄▄▄▄▄\n█       █  █  █ █       █       █       █       █  █ █  █   █   █       █       █       █   ▄  █ █       █\n█    ▄▄▄█   █▄█ █       █   ▄   █    ▄  █  ▄▄▄▄▄█  █ █  █   █   █   ▄   █▄     ▄█   ▄   █  █ █ █ █  ▄▄▄▄▄█\n█   █▄▄▄█       █     ▄▄█  █▄█  █   █▄█ █ █▄▄▄▄▄█  █▄█  █   █   █  █▄█  █ █   █ █  █ █  █   █▄▄█▄█ █▄▄▄▄▄ \n█    ▄▄▄█  ▄    █    █  █       █    ▄▄▄█▄▄▄▄▄  █       █   █▄▄▄█       █ █   █ █  █▄█  █    ▄▄  █▄▄▄▄▄  █\n█   █▄▄▄█ █ █   █    █▄▄█   ▄   █   █    ▄▄▄▄▄█ █       █       █   ▄   █ █   █ █       █   █  █ █▄▄▄▄▄█ █\n█▄▄▄▄▄▄▄█▄█  █▄▄█▄▄▄▄▄▄▄█▄▄█ █▄▄█▄▄▄█   █▄▄▄▄▄▄▄█▄▄▄▄▄▄▄█▄▄▄▄▄▄▄█▄▄█ █▄▄█ █▄▄▄█ █▄▄▄▄▄▄▄█▄▄▄█  █▄█▄▄▄▄▄▄▄█\n";
    cout << ENCAPSULATORS;

    // inisiasi game
    Game main;

    // memuat semua config
    cout << "DIATAS CONFIG" << endl;
    try{
        main.muat_semua_config();
        main.muat_player_state();

    }catch(const char* e){
        cout << e << endl;
    }

    cout << "DIBAWAH CONFIG" << endl;

    // Command
    Command command(main.getCurrentPlayer());

    while(!finishGame(main.getListPlayer(), main.goalUang, main.goalBerat)) {
        try {
            command.terimaCommand();
            // cout << "Ini command : " << command.getPerintah() << "\n";
            if(command.getPerintah() == "NEXT") {
                main.nextTurn();
            } else if(command.getPerintah() == "CETAK_PENYIMPANAN") {
                main.cetak_penyimpanan();
            } else if(command.getPerintah() == "MAKAN") {

            } else if(command.getPerintah() == "BELI") {

            } else if(command.getPerintah() == "JUAL") {

            } else if(command.getPerintah() == "SIMPAN") {

            } else if(command.getPerintah() == "PUNGUT_PAJAK") {
                main.pungutPajak();
            } else if(command.getPerintah() == "BANGUN") {

            } else if(command.getPerintah() == "TAMBAH_PEMAIN") {
                main.tambahPlayer();
            } else if(command.getPerintah() == "CETAK_LADANG") {
                main.cetak_ladang();
            } else if(command.getPerintah() == "CETAK_PETERNAKAN") {
                main.cetak_lahan();
            } else if(command.getPerintah() == "TANAM") {
                main.tanam();
            } else if(command.getPerintah() == "PANEN") {
                main.panen();
            } else if(command.getPerintah() == "TERNAK") {

            } else if(command.getPerintah() == "KASIH_MAKAN") {
                main.beriPangan();
            }
        } catch (invalidCommandException e) {
            cout << e.message();
        }
    }

    // cari pemenang
    // Player pemenang;
    // for(int i = 0; i < main.listPlayer.size(); i++) {
    //     if(main.listPlayer[i]->getUang() >= main.goalUang && main.listPlayer[i]->getBerat() >= main.goalBerat) {
    //         pemenang = main.listPlayer[i];
    //     }
    // }

    return 0;
}