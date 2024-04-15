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
        // cout << main.listPlayer[main.turn - 1]->getPeran() << endl;
        // main.listPlayer[main.turn - 1]->pungutPajak(main.getListPlayer(), 3);
        // main.listPlayer[main.turn - 1]->bangunBangunan(main.recipeMap["SMH"]);

        // cout << main.listPlayer[main.turn]->penyimpanan.getRow() << endl;
        // cout << main.listPlayer[main.turn]->penyimpanan.getCol() << endl;
        main.listPlayer[main.turn]->cetakPenyimpanan();
    }
    catch (invalidCommandException e)
    {
        cout << e.message();
    }
    return 0;
}