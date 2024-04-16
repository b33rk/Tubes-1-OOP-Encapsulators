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
        // TradeObject* first = new TradeObject(1, "TWD","TEAK_WOOD",10,"MATERIAL");
        // TradeObject* second = new TradeObject(1,"SW","SANDAL_WOOD",10,"MATERIAL");
        // main.listPlayer[main.turn - 1]->setBarangFirstPenyimpanan(first);
        // main.listPlayer[main.turn - 1]->setBarangFirstPenyimpanan(second);
        main.listPlayer[main.turn - 1]->cetakPenyimpanan();
        main.listPlayer[main.turn - 1]->bangunBangunan(main.recipeMap["SMH"]);
        main.listPlayer[main.turn - 1]->cetakPenyimpanan();
        int row = 0 ;
        int col = 0 ;
        TradeObject* p = new TradeObject();
        main.listPlayer[main.turn - 1]->setBarangPenyimpanan(row,col,p);
        main.listPlayer[main.turn - 1]->cetakPenyimpanan();
        


        
        // main.listPlayer[main.turn - 1]->cetakPenyimpanan();
        // cout << "SUP";
        // CultivatedObject *hewan = new CultivatedObject(main.animalMap["COW"]);
        // main.listPlayer[2]->ternak(hewan, 0,0);
        // main.listPlayer[2]->cetakLadangLahan();
        // main.listPlayer[2]->panen(0,0,0,0, &main.productMap["COM"]);
        // // main.listPlayer[main.turn]->tanam(&main.plantMap["ORG"], 0,0);
        // main.listPlayer[2]->cetakLadangLahan();
        // main.listPlayer[2]->cetakPenyimpanan();
        
        // main.nextTurn();

    } catch (invalidCommandException e) {
        cout << e.message(); 
    } catch (KurangMaterialException e){
        cout << e.message();
    }
    // } catch (BarangKosongException e) {
    //     cout << e.message();
    // } catch (KurangMaterialException e){
    //     cout << e.what() ;
    // }
    return 0;
}