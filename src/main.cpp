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

pair<bool, string> finishGame(vector<Player *> listPlayer, int goalUang, int goalBerat)
{
    pair<bool, string> ans = {false, ""};
    for (int i = 0; i < listPlayer.size(); i++)
    {
        if (listPlayer[i]->getUang() >= goalUang && listPlayer[i]->getBerat() >= goalBerat)
        {
            ans.first = true;
            ans.second = listPlayer[i]->getNama();
        }
    }

    return ans;
}

int main()
{
    // welcoming

    const string ENCAPSULATORS = "\n▄▄▄▄▄▄▄ ▄▄    ▄ ▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄ ▄▄   ▄▄ ▄▄▄     ▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄ ▄▄▄▄▄▄   ▄▄▄▄▄▄▄\n█       █  █  █ █       █       █       █       █  █ █  █   █   █       █       █       █   ▄  █ █       █\n█    ▄▄▄█   █▄█ █       █   ▄   █    ▄  █  ▄▄▄▄▄█  █ █  █   █   █   ▄   █▄     ▄█   ▄   █  █ █ █ █  ▄▄▄▄▄█\n█   █▄▄▄█       █     ▄▄█  █▄█  █   █▄█ █ █▄▄▄▄▄█  █▄█  █   █   █  █▄█  █ █   █ █  █ █  █   █▄▄█▄█ █▄▄▄▄▄ \n█    ▄▄▄█  ▄    █    █  █       █    ▄▄▄█▄▄▄▄▄  █       █   █▄▄▄█       █ █   █ █  █▄█  █    ▄▄  █▄▄▄▄▄  █\n█   █▄▄▄█ █ █   █    █▄▄█   ▄   █   █    ▄▄▄▄▄█ █       █       █   ▄   █ █   █ █       █   █  █ █▄▄▄▄▄█ █\n█▄▄▄▄▄▄▄█▄█  █▄▄█▄▄▄▄▄▄▄█▄▄█ █▄▄█▄▄▄█   █▄▄▄▄▄▄▄█▄▄▄▄▄▄▄█▄▄▄▄▄▄▄█▄▄█ █▄▄█ █▄▄▄█ █▄▄▄▄▄▄▄█▄▄▄█  █▄█▄▄▄▄▄▄▄█\n\n";
    cout << ENCAPSULATORS;

    // inisiasi game
    Game main;

    try
    {
        main.muat_semua_config();
        main.muat_player_state();
    }
    catch (const char *e)
    {
        cout << e << endl;
    }

    // Command
    Command command(main.getCurrentPlayer());

    cout << "Jumlah player : " << main.getJumlahPlayer() << "\n";
    cout << "\nUrutan giliran : \n";
    for (int i = 0; i < main.getListPlayer().size(); i++)
    {
        cout << i + 1 << ".     " << main.getNamaPlayerGame(i) << "\n";
    }

    cout << "\nSELAMAT BERMAIN!!!\n";

    pair<bool, string>  terminateGame = finishGame(main.getListPlayer(), main.getGoalUang(), main.getGoalBerat());
    
    while (!terminateGame.first)
    {
        try
        {
            // set toko dan command
            command.setPeran(main.getCurrentPlayer()->getPeran());
            main.setPelakuShop();

            cout << "\n\nGiliran saat ini : ";
            cout << main.getCurrentPlayer()->getNama() << "\n";
            cout << "Peran : ";
            cout << main.getCurrentPlayer()->getPeran() << "\n";
            command.displayAvailableCommand();
            cout << endl;
            command.terimaCommand();

            if (command.getPerintah() == "NEXT")
            {
                main.next();
            }
            else if (command.getPerintah() == "CETAK_PENYIMPANAN")
            {
                main.cetakPenyimpanan();
            }
            else if (command.getPerintah() == "MAKAN")
            {
                main.makan();
            }
            else if (command.getPerintah() == "BELI")
            {
                main.beli();
            }
            else if (command.getPerintah() == "JUAL")
            {
                main.jual();
            }
            else if (command.getPerintah() == "SIMPAN")
            {
                main.simpan();
            }
            else if (command.getPerintah() == "PUNGUT_PAJAK")
            {
                main.pungutPajak();
            }
            else if (command.getPerintah() == "BANGUN")
            {
                main.bangun();
            }
            else if (command.getPerintah() == "TAMBAH_PEMAIN")
            {
                main.tambahPlayer();
            }
            else if (command.getPerintah() == "CETAK_LADANG")
            {
                main.cetakLahanLadang();
            }
            else if (command.getPerintah() == "CETAK_PETERNAKAN")
            {
                main.cetakLahanLadang();
            }
            else if (command.getPerintah() == "TANAM")
            {
                main.tanam();
            }
            else if (command.getPerintah() == "PANEN")
            {
                main.panen();
            }
            else if (command.getPerintah() == "TERNAK")
            {
                main.ternak();
            }
            else if (command.getPerintah() == "KASIH_MAKAN")
            {
                main.kasihMakan();
            }
        }
        catch (const exception &e)
        {
            const char *red = "\033[1;91m";
            const char *reset = "\033[0m";
            cout << red << e.what() << reset;
        }catch(const char* e){
            const char *red = "\033[1;91m";
            const char *reset = "\033[0m";
            cout << red << e << reset;
        }

        terminateGame = finishGame(main.getListPlayer(), main.getGoalUang(), main.getGoalBerat());
    }

    cout << terminateGame.second << " adalah pemenangnya!\n";

    cout << "Terima kasih telah bermain!\n\n";

    return 0;
}