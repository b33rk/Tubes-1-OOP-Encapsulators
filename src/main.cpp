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
    try
    {
        // // main.listPlayer[main.turn - 1]->bangunBangunan(main.recipeMap["SMH"]);
        CultivatedObject *hewan = new CultivatedObject(main.animalMap["COW"]);
        main.listPlayer[2]->ternak(hewan, 0, 0);
        main.listPlayer[2]->cetakPenyimpanan();

        // main.listPlayer[2]->ternak(hewan, 1, 0);
        main.listPlayer[2]->cetakLadangLahan();
        // main.listPlayer[2]->penyimpanan.getBarang(0, 0)->cetakBarang();
        main.listPlayer[2]->panen(0, 0, 0, 0, &main.productMap["COM"]);
        // // main.listPlayer[main.turn]->tanam(&main.plantMap["ORG"], 0,0);
        main.listPlayer[2]->cetakLadangLahan();
        main.listPlayer[2]->cetakPenyimpanan();

        main.listPlayer[2]->cetakLadangLahan();
        cout << "POINTER STORAGE 0,0 " << main.listPlayer[2]->getLahan().storage[0][0] << endl;
        CultivatedObject *hewan2 = new CultivatedObject(main.animalMap["SNK"]);
        cout << "POINTER HEWAN 2  " << hewan2 << endl;
        CultivatedObject *hewan3 = new CultivatedObject(main.animalMap["CHK"]);
        cout << "POINTER HEWAN 3  " << hewan2 << endl;
        main.listPlayer[2]->cetakLadangLahan();
        cout << "POINTER STORAGE 0,0 " << main.listPlayer[2]->getLahan().storage[0][0] << endl;
        main.listPlayer[2]->ternak(hewan2, 1, 1);
        main.listPlayer[2]->cetakLadangLahan();

        // main.nextTurn();

        // cout << main.listPlayer[main.turn]->penyimpanan.getRow() << endl;
        // cout << main.listPlayer[main.turn]->penyimpanan.getCol() << endl;
    }
    catch (invalidCommandException e)
    {
        cout << e.message();
    }
    catch (BarangKosongException e)
    {
        cout << e.message();
    }
    return 0;
}