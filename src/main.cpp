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

bool finishGame(vector<Player *> listPlayer, int goalUang, int goalBerat)
{
    for (int i = 0; i < listPlayer.size(); i++)
    {
        if (listPlayer[i]->getUang() >= goalUang && listPlayer[i]->getBerat() >= goalBerat)
        {
            return true;
        }
    }

    return false;
}

int main()
{
    // welcoming

    const string ENCAPSULATORS = "▄▄▄▄▄▄▄ ▄▄    ▄ ▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄ ▄▄   ▄▄ ▄▄▄     ▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄ ▄▄▄▄▄▄   ▄▄▄▄▄▄▄\n█       █  █  █ █       █       █       █       █  █ █  █   █   █       █       █       █   ▄  █ █       █\n█    ▄▄▄█   █▄█ █       █   ▄   █    ▄  █  ▄▄▄▄▄█  █ █  █   █   █   ▄   █▄     ▄█   ▄   █  █ █ █ █  ▄▄▄▄▄█\n█   █▄▄▄█       █     ▄▄█  █▄█  █   █▄█ █ █▄▄▄▄▄█  █▄█  █   █   █  █▄█  █ █   █ █  █ █  █   █▄▄█▄█ █▄▄▄▄▄ \n█    ▄▄▄█  ▄    █    █  █       █    ▄▄▄█▄▄▄▄▄  █       █   █▄▄▄█       █ █   █ █  █▄█  █    ▄▄  █▄▄▄▄▄  █\n█   █▄▄▄█ █ █   █    █▄▄█   ▄   █   █    ▄▄▄▄▄█ █       █       █   ▄   █ █   █ █       █   █  █ █▄▄▄▄▄█ █\n█▄▄▄▄▄▄▄█▄█  █▄▄█▄▄▄▄▄▄▄█▄▄█ █▄▄█▄▄▄█   █▄▄▄▄▄▄▄█▄▄▄▄▄▄▄█▄▄▄▄▄▄▄█▄▄█ █▄▄█ █▄▄▄█ █▄▄▄▄▄▄▄█▄▄▄█  █▄█▄▄▄▄▄▄▄█\n";
    cout << ENCAPSULATORS;

    // inisiasi game
    Game main;

    // memuat semua config
    try{
        main.muat_semua_config();
        main.muat_player_state();
    }
    catch (const char *e)
    {
        cout << e << endl;
    }
    // Command
    Command command(main.getCurrentPlayer());

    while (!finishGame(main.getListPlayer(), main.goalUang, main.goalBerat))
    {
        try
        {
            command.terimaCommand();
            // cout << "Ini command : " << command.getPerintah() << "\n";
            if (command.getPerintah() == "NEXT")
            {
                main.nextTurn();
            }
            else if (command.getPerintah() == "CETAK_PENYIMPANAN")
            {
            }
            else if (command.getPerintah() == "MAKAN")
            {
            }
            else if (command.getPerintah() == "BELI")
            {
            }
            else if (command.getPerintah() == "JUAL")
            {
            }
            else if (command.getPerintah() == "SIMPAN")
            {
            }
            else if (command.getPerintah() == "PUNGUT_PAJAK")
            {
            }
            else if (command.getPerintah() == "BANGUN")
            {
                main.bangun();
            }
            else if (command.getPerintah() == "TAMBAH_PEMAIN")
            {
            }
            else if (command.getPerintah() == "CETAK_LADANG")
            {
            }
            else if (command.getPerintah() == "CETAK_PETERNAKAN")
            {
            }
            else if (command.getPerintah() == "TANAM")
            {

                main.tanam();
            }
            else if (command.getPerintah() == "PANEN")
            {
            }
            else if (command.getPerintah() == "TERNAK")
            {
                main.ternak();
            }
            else if (command.getPerintah() == "KASIH_MAKAN")
            {
            }
        }
        catch (invalidCommandException e)
        {
            cout << e.message();
        }
    }

    return 0;
}