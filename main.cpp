// #include "src/FieldObject/Field.hpp"
// #include "src/GameMaster/GameMaster.hpp"
// #include "src/GameObject/GameObject.hpp"
// #include "src/Player/Player.hpp"

#include <iostream>

using namespace std;

bool finishGame() {

}

int main() {
    // welcoming
    const string ENCAPSULATORS = "▄▄▄▄▄▄▄ ▄▄    ▄ ▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄ ▄▄   ▄▄ ▄▄▄     ▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄ ▄▄▄▄▄▄   ▄▄▄▄▄▄▄\n█       █  █  █ █       █       █       █       █  █ █  █   █   █       █       █       █   ▄  █ █       █\n█    ▄▄▄█   █▄█ █       █   ▄   █    ▄  █  ▄▄▄▄▄█  █ █  █   █   █   ▄   █▄     ▄█   ▄   █  █ █ █ █  ▄▄▄▄▄█\n█   █▄▄▄█       █     ▄▄█  █▄█  █   █▄█ █ █▄▄▄▄▄█  █▄█  █   █   █  █▄█  █ █   █ █  █ █  █   █▄▄█▄█ █▄▄▄▄▄ \n█    ▄▄▄█  ▄    █    █  █       █    ▄▄▄█▄▄▄▄▄  █       █   █▄▄▄█       █ █   █ █  █▄█  █    ▄▄  █▄▄▄▄▄  █\n█   █▄▄▄█ █ █   █    █▄▄█   ▄   █   █    ▄▄▄▄▄█ █       █       █   ▄   █ █   █ █       █   █  █ █▄▄▄▄▄█ █\n█▄▄▄▄▄▄▄█▄█  █▄▄█▄▄▄▄▄▄▄█▄▄█ █▄▄█▄▄▄█   █▄▄▄▄▄▄▄█▄▄▄▄▄▄▄█▄▄▄▄▄▄▄█▄▄█ █▄▄█ █▄▄▄█ █▄▄▄▄▄▄▄█▄▄▄█  █▄█▄▄▄▄▄▄▄█\n";
    cout << ENCAPSULATORS;

    // inisiasi game
    Game game = new Game();

    // memuat semua config
    game.muat_semua_config();
    game.muat_player_state();

    while(!finishGame()) {
        
    }
}