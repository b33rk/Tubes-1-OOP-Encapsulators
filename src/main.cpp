#include "Exception/Exception.hpp"
#include "FieldObject/Field.hpp"
#include "GameMaster/GameMaster.hpp"
#include "GameObject/GameObject.hpp"
#include "Player/Farmers.hpp"
#include "Player/Petani.hpp"
#include "Player/Peternak.hpp"
#include "Player/Player.hpp"
#include "Player/Walikota.hpp"

int main()
{
    Game main;
    main.muat_semua_config();
    main.muat_player_state();
    string command;
    bool is = true;
    while(is) {
        try
        {
            // main.listPlayer[main.turn - 1]->bangunBangunan(main.recipeMap["SMH"]);
            cin >> command;
            if (command  == "cetakLahan") {
                main.cetakLahanLadang();
            }
            else if (command  == "cetakPen")
            {
                main.listPlayer[main.turn-1]->cetakPenyimpanan();
            }
            else if (command == "ternak")
            {
                CultivatedObject *hewan = new CultivatedObject(main.animalMap["COW"]);
                main.listPlayer[main.turn-1]->ternak(hewan, 0, 0);
            }
            else if (command  == "next")
            {
                main.nextTurn();
            }
            else if (command  == "panen")
            {
                main.panen();
            }
            else if (command  == "beriPakan")
            {
                main.listPlayer[main.turn-1]->beriPangan(0,0,0,0);
            }
            else if (command  == "tanam")
            {
                CultivatedObject *tumbuhan = new CultivatedObject(main.plantMap["ORG"]);
                main.listPlayer[main.turn-1]->tanam(tumbuhan,0,0);
            }
        }
        catch (const exception& e)
        {
            cout << e.what();
        }
    }
}