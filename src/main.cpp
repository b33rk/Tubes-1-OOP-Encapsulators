#include "Exception/Exception.hpp"
#include "FieldObject/Field.hpp"
#include "GameMaster/GameMaster.hpp"
#include "GameObject/GameObject.hpp"
#include "Player/Farmers.hpp"
#include "Player/Petani.hpp"
#include "Player/Peternak.hpp"
#include "Player/Player.hpp"
#include "Player/Walikota.hpp"

// bool finishGame(vector<Player*> listPlayer;, int goalUang, int goalBerat) {

// }

int main() {
    // welcoming
    const string ENCAPSULATORS = "▄▄▄▄▄▄▄ ▄▄    ▄ ▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄ ▄▄   ▄▄ ▄▄▄     ▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄ ▄▄▄▄▄▄   ▄▄▄▄▄▄▄\n█       █  █  █ █       █       █       █       █  █ █  █   █   █       █       █       █   ▄  █ █       █\n█    ▄▄▄█   █▄█ █       █   ▄   █    ▄  █  ▄▄▄▄▄█  █ █  █   █   █   ▄   █▄     ▄█   ▄   █  █ █ █ █  ▄▄▄▄▄█\n█   █▄▄▄█       █     ▄▄█  █▄█  █   █▄█ █ █▄▄▄▄▄█  █▄█  █   █   █  █▄█  █ █   █ █  █ █  █   █▄▄█▄█ █▄▄▄▄▄ \n█    ▄▄▄█  ▄    █    █  █       █    ▄▄▄█▄▄▄▄▄  █       █   █▄▄▄█       █ █   █ █  █▄█  █    ▄▄  █▄▄▄▄▄  █\n█   █▄▄▄█ █ █   █    █▄▄█   ▄   █   █    ▄▄▄▄▄█ █       █       █   ▄   █ █   █ █       █   █  █ █▄▄▄▄▄█ █\n█▄▄▄▄▄▄▄█▄█  █▄▄█▄▄▄▄▄▄▄█▄▄█ █▄▄█▄▄▄█   █▄▄▄▄▄▄▄█▄▄▄▄▄▄▄█▄▄▄▄▄▄▄█▄▄█ █▄▄█ █▄▄▄█ █▄▄▄▄▄▄▄█▄▄▄█  █▄█▄▄▄▄▄▄▄█\n";
    cout << ENCAPSULATORS;

    // // inisiasi game
    // Game main;

    // // memuat semua config
    // main.muat_semua_config();
    // main.muat_player_state();

    // while(!finishGame(main.getListPlayer(), game.goalUang, game.goalBerat)) {
        
    // }


    // return 0;

    Game main;
    main.muat_semua_config();
    try {
        cout << main.listPlayer[main.turn - 1]->getPeran() << endl;
        main.listPlayer[main.turn - 1]->pungutPajak(main.getListPlayer(), 3);
        main.listPlayer[main.turn - 1]->bangunBangunan(main.recipeMap["SMH"]);
    } catch (invalidCommandException e) {
        cout << e.message();
    }
    return 0;
}