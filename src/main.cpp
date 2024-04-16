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
    cout << main.jumlahPlayer << endl;
    for(int i = 0; i < main.listPlayer.size(); ++i){
        cout << main.listPlayer[i]->getNama() << endl;
    }
    CultivatedObject *hewan = new CultivatedObject(main.animalMap["COW"]);
    main.listPlayer[1]->ternak(hewan, 0, 1);
    CultivatedObject *snk = new CultivatedObject(main.animalMap["SNK"]);
    main.listPlayer[1]->ternak(snk, 0, 2);
    TradeObject *prod = new ProductObject(main.productMap["ORP"]);
    TradeObject *prodMeat = new ProductObject(main.productMap["SHM"]);
    TradeObject *prodMeat2 = new ProductObject(main.productMap["SHM"]);
    TradeObject *prodMeat3 = new ProductObject(main.productMap["SHM"]);
    main.listPlayer[1]->setBarangFirstPenyimpanan(prod);
    main.listPlayer[1]->setBarangFirstPenyimpanan(prodMeat);
    main.listPlayer[1]->setBarangFirstPenyimpanan(prodMeat2);
    main.listPlayer[1]->setBarangFirstPenyimpanan(prodMeat3);
    main.listPlayer[1]->cetakLadangLahan();
    main.listPlayer[1]->cetakPenyimpanan();
    main.turn++;
    while(is) {
        try
        {
            // main.listPlayer[main.turn - 1]->bangunBangunan(main.recipeMap["SMH"]);
            cin >> command;
            if (command  == "kasih_makan") {
                main.kasihMakan();
            }
            else if (command  == "cetakPen")
            {
                main.listPlayer[main.turn-1]->cetakPenyimpanan();
            }else if(command == "cetak_lahan"){
                main.listPlayer[main.turn - 1]->cetakLadangLahan();
            }
            /*
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
                ProductObject *prod = new ProductObject(main.productMap["ORP"]);
                main.listPlayer[main.turn-1]->panen(0, 0, 0, 0, prod);
            }
            else if (command  == "beriPakan")
            {
                main.listPlayer[main.turn-1]->beriPangan(0,0,0,0);
            }
            else if (command  == "tanam")
            {
                CultivatedObject *tumbuhan = new CultivatedObject(main.plantMap["ORG"]);
                main.listPlayer[main.turn-1]->tanam(tumbuhan,0,0);
            }*/
        }
        catch (invalidCommandException e)
        {
            cout << e.message();
        }
        catch (BarangKosongException e)
        {
            cout << e.message();
        }
        catch (petakTidakKosongException e)
        {
            cout << e.message();
        }
        catch (MakananSalahException e)
        {
            cout << e.message();
        }
    }
}