#include "Walikota.hpp"
#include <vector>
#include <utility>
#include "Player.hpp"

Walikota ::Walikota(string nama, int berat, int uang, int rowPenyimpanan, int colPenyimpanan) : Player(nama, "Walikota", berat, uang, rowPenyimpanan, colPenyimpanan) {}

int Walikota ::bayarPajak()
{
    throw invalidCommandException();
}

void Walikota ::pungutPajak(vector<Player *> listPlayer, int num_of_players)
{

    int pajak_temp;
    int total = 0;
    cout << "Cring cring cring...\n";
    cout << "Pajak sudah dipungut!\n\n";
    cout << "Berikut adalah detil dari pemungutan pajak:\n";
    int j = 1;
    for (int i = 0; i < num_of_players; i++)
    {
        if (listPlayer[i]->getPeran() != "Walikota")
        {
            pajak_temp = listPlayer[i]->bayarPajak();
            cout << j << ". " << listPlayer[i]->getNama() << " - " << listPlayer[i]->getPeran() << ": " << pajak_temp << " gulden\n";
            total += pajak_temp;
            j++;
        }
    }
    cout << "\n";
    cout << "Negara mendapatkan pemasukan sebesar " << total << " gulden.\n";
    cout << "Gunakan dengan baik dan jangan dikorupsi ya!\n";
    total += this->getUang();
    this->setUang(total);
}

void Walikota ::bangunBangunan(Recipe recipe)
{
    // Anggap building adalah tradeobject dengan id yang sama dengan recipe, dan atribut yang sama dengan recipe
    vector<pair<int, int>> location;
    vector<string> materials = recipe.getListMaterial();
    vector<int> materialQuantity = recipe.getMaterialQuantity();
    bool complete = true;
    bool allComplete = true;
    bool found = false;
    for (int i = 0; i < materials.size(); i++)
    {
        complete = false;
        for (int r = 0; r < this->penyimpanan.getRow() && !complete; r++)
        {
            for (int c = 0; c < this->penyimpanan.getCol() && !complete; c++)
            {
                if (this->penyimpanan.getBarang(r, c)->getNama() == materials[i])
                {
                    materialQuantity[i] -= 1;
                    location.push_back(make_pair(r, c));
                    if (materialQuantity[i] == 0)
                    {
                        complete = true;
                    }
                }
            }
        }
        allComplete = allComplete && complete;
    }

    if (!allComplete)
    {

        throw KurangMaterialException(materials, materialQuantity);
    }

    for (auto &pair : location)
    {
        this->penyimpanan.setKosong(pair.first, pair.second);
    }

    TradeObject *T = new TradeObject(recipe.getId(), recipe.getKodeHuruf(), recipe.getNamaGameObject(), recipe.getPrice(), "BANGUNAN");
    vector<vector<TradeObject *>> temp_penyimpanan = this->penyimpanan.getStorage();
    this->penyimpanan.insertFirst(T);
}

Field<CultivatedObject> Walikota ::getLahan()
{
    throw invalidCommandException();
}

void Walikota ::tambahPlayer(string peran)
{
    if (this->getUang() < 50)
    {
        throw uangTidakCukupException();
    }
    if (peran != "Peternak" && peran != "Petani")
    {
        throw tambahPlayerInvalidException();
    }
    this->setUang(this->getUang() - 50);
}