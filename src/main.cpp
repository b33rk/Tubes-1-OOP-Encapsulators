#include "Exception/Exception.hpp"
#include "FieldObject/Field.hpp"
#include "GameMaster/GameMaster.hpp"
#include "GameObject/GameObject.hpp"
#include "Player/Farmers.hpp"
#include "Player/Petani.hpp"
#include "Player/Peternak.hpp"
#include "Player/Player.hpp"
#include "Player/Walikota.hpp"

int main() {
    Game main;
    main.muat_semua_config();
    try {
        // main.listPlayer[main.turn - 1]->bangunBangunan(main.recipeMap["SMH"]);
        CultivatedObject *hewan = new CultivatedObject(main.animalMap["COW"]);
        main.listPlayer[2]->ternak(hewan, 0,0);
        main.listPlayer[2]->cetakLadangLahan();
        main.listPlayer[2]->panen(0,0,0,0, &main.productMap["COM"]);
        // main.listPlayer[main.turn]->tanam(&main.plantMap["ORG"], 0,0);
        main.listPlayer[2]->cetakLadangLahan();
        main.listPlayer[2]->cetakPenyimpanan();
        
        main.nextTurn();
    } catch (invalidCommandException e) {
        cout << e.message();
    } catch (BarangKosongException e) {
        cout << e.message();
    }
    return 0;
}