#ifndef GAMEMASTER_HPP
#define GAMEMASTER_HPP

#include "../Player/Player.hpp"
#include "../Player/Petani.hpp"
#include "../Player/Peternak.hpp"
#include "../Player/Walikota.hpp"
#include "../GameObject/GameObject.hpp"
#include "../Shop/Shop.hpp"
#include "../Command/Command.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string.h>

#include <vector>
#include <algorithm>
#include <map>

using namespace std;

string const pathConfig = "./config";

const char *spaces = " \n\r\t";

class Game
{
protected:
    int goalUang;
    int goalBerat;
    int rowPenyimpanan;
    int colPenyimpanan;
    int rowLadang;
    int colLadang;
    int rowLahan;
    int colLahan;
    int jumlahPlayer;
    int turn;
    vector<Player *> listPlayer;
    map<string, CultivatedObject> plantMap;
    map<string, CultivatedObject> animalMap;
    map<string, ProductObject> productMap;
    map<string, Recipe> recipeMap;
    Player *currentPlayer;
    Shop shop;
    /*
    vector<TradeObject> tradeObjMemory;
    vector<CultivatedObject> cultObjMemory;
    vector<ProductObject> prodObjMemory;
    vector<Recipe> recObjMemory;
    vector<Petani> petaniMemory;
    vector<Peternak> peternakMemory;
    vector<Walikota> walkotMemory;
    */
public:
    Game() {}

    string getNamaPlayerGame(int i){
        return this->listPlayer[i]->getNama();
    }

    int getGoalUang(){
        return this->goalUang;
    }

    int getGoalBerat(){
        return this->goalBerat;
    }
    void nextTurn()
    {
        if (turn == jumlahPlayer)
        {
            turn = 1;
        }
        else
        {
            turn++;
        }
        currentPlayer = listPlayer[turn - 1];
        currentPlayer = listPlayer[turn - 1];
    }

    Player *getCurrentPlayer()
    {
        return this->listPlayer[turn - 1];
    }

    vector<Player *> getListPlayer()
    {
        return this->listPlayer;
    }

    // return pair p, p.first = row, p.second = col
    pair<int, int> stringToCoord(string s)
    {
        if (s.size() != 3)
        {
            return make_pair(-1, -1);
        }
        char col = s[0];
        char row = 10 * (s[1] - '0') + (s[2] - '0');
        int colNum = col - 'A';
        int rowNum = row - 1;
        return make_pair(rowNum, colNum);
    }

    string coordToString(int row, int col)
    {
        char colChar = col + 'A';
        row++;
        char fi = '0' + (row / 10);
        char se = '0' + (row % 10);
        string ans = "";
        ans += colChar;
        ans += fi;
        ans += se;
        return ans;
    }

    void readPlant(vector<string> tokens)
    {
        if (tokens.size() != 6)
            throw "readPlant: panjang token != 6";
        CultivatedObject plant(stoi(tokens[0]), tokens[1], tokens[2], tokens[3], stoi(tokens[4]), stoi(tokens[5]));
        plantMap[tokens[1]] = plant;
    }

    void readAnimal(vector<string> tokens)
    {
        if (tokens.size() != 6)
            throw "readAnimal: panjang token != 6";
        CultivatedObject animal(stoi(tokens[0]), tokens[1], tokens[2], tokens[3], stoi(tokens[4]), stoi(tokens[5]));
        animalMap[tokens[1]] = animal;
    }

    void readProduct(vector<string> tokens)
    {
        if (tokens.size() != 7)
            throw "readProduct: panjang token != 7";
        ProductObject product(stoi(tokens[0]), tokens[1], tokens[2], stoi(tokens[6]), tokens[3], tokens[4], stoi(tokens[5]));
        productMap[tokens[1]] = product;
    }

    void readRecipe(vector<string> tokens)
    {
        if (tokens.size() < 4 || tokens.size() % 2 == 1)
            throw "readRecipe: panjang token < 4 atau panjang token ganjil";
        vector<string> materials;
        vector<int> materialQuantity;
        for (int i = 4; i < tokens.size(); i += 2)
        {
            materials.push_back(tokens[i]);
            materialQuantity.push_back(stoi(tokens[i + 1]));
        }
        Recipe recipe(stoi(tokens[0]), tokens[1], tokens[2], stoi(tokens[3]), materials, materialQuantity);
        recipeMap[tokens[1]] = recipe;
    }

    void initialMisc()
    {
        ifstream MiscFile(pathConfig + "/" + "misc" + ".txt");
        if (!MiscFile)
            throw strerror(errno);
        string allText = "";
        string currentText;
        while (getline(MiscFile, currentText))
        {
            allText += currentText + '\n';
        }
        allText.erase(allText.find_last_not_of(spaces) + 1);
        vector<string> splitted = split(allText, '\n');
        for (int i = 0; i < 5; ++i)
        {
            string splitString = splitted[i];
            splitString.erase(splitString.find_last_not_of(spaces) + 1);

            switch (i)
            {
            case 0:
                goalUang = stoi(splitString);
                break;
            case 1:
                goalBerat = stoi(splitString);
                break;
            default: // INI SEMUA BISA KEBALIK AWIKWOK
                vector<string> splittedSpace = split(splitString, ' ');
                switch (i)
                {
                case 2:
                    rowPenyimpanan = stoi(splittedSpace[0]); // GAK YAKIN, BISA JADI KEBALIK SAMA YANG BAWAH
                    colPenyimpanan = stoi(splittedSpace[1]); // GAK TAU MANA ROW MANA COL // UPD: BENER
                    break;
                case 3:
                    rowLahan = stoi(splittedSpace[0]);
                    colLahan = stoi(splittedSpace[1]);
                    break;
                case 4:
                    rowLadang = stoi(splittedSpace[0]); // peternakan = ladang
                    colLadang = stoi(splittedSpace[1]);
                    break;
                default:
                    throw "initialMisc: gak masuk switch case manapun (how)";
                }
                break;
            }
        }
        this->turn = 1;
        this->jumlahPlayer = listPlayer.size();
    }

    vector<string> split(const string &s, char delim)
    {
        vector<string> result;
        stringstream ss(s);
        string item;
        while (getline(ss, item, delim))
        {
            result.push_back(item);
        }
        return result;
    }

    void muat_general(string namaFile, void (Game::*func)(vector<string>))
    {
        ifstream currentFile(pathConfig + "/" + namaFile + ".txt");
        if (!currentFile)
            throw strerror(errno);
        string allText = "";
        string currentText;
        while (getline(currentFile, currentText))
        {
            allText += currentText + '\n';
        }
        allText.erase(allText.find_last_not_of(spaces) + 1);
        vector<string> splitted = split(allText, '\n');
        for (auto &splitString : splitted)
        {
            splitString.erase(splitString.find_last_not_of(spaces) + 1);
            vector<string> splittedSpace = split(splitString, ' ');
            (this->*func)(splittedSpace);
        }
    }

    void muat_semua_config()
    {
        // muat_general dengan argumen function pointer milik Game
        muat_general("plant", &Game::readPlant);
        muat_general("animal", &Game::readAnimal);
        muat_general("product", &Game::readProduct);
        muat_general("recipe", &Game::readRecipe);
        initialMisc();
    }

    void cetak_state()
    {
        for (auto &p : plantMap)
        {
            p.second.cetak();
            cout << endl;
        }
        cout << endl;
        for (auto &p : animalMap)
        {
            p.second.cetak();
            cout << endl;
        }
        for (auto &p : productMap)
        {
            p.second.cetakBarang();
            cout << endl;
        }
        cout << endl;
        for (auto &p : recipeMap)
        {

            p.second.cetak();
            cout << endl;
        }
        cout << endl;
        cout << goalUang << " " << goalBerat << " " << rowPenyimpanan << " " << colPenyimpanan << " " << rowLahan << " " << colLahan << " " << rowLadang << " " << colLadang << endl;
    }

    void muat_player_state()
    {
        bool player_loaded = false;
        bool valid_input = false;
        string filePath;
        // loading player
        do
        {
            string input;
            do
            {
                cout << "Apakah anda ingin memuat state? (y/n)";
                cin >> input;
                cout << endl;
                input.erase(input.find_last_not_of(spaces) + 1);
            } while (input != "y" && input != "n");

            if (input == "n")
            {
                Player *new_petani = new Petani("Petani1", 40, 50, rowPenyimpanan, colPenyimpanan, rowLahan, colLahan);
                Player *new_peternak1 = new Peternak("Peternak1", 40, 50, rowPenyimpanan, colPenyimpanan, rowLadang, colLadang);
                Player *new_walikota1 = new Walikota("Walikota1", 40, 50, rowPenyimpanan, colPenyimpanan);
                // petaniMemory.push_back(new_petani1);
                // peternakMemory.push_back(new_peternak1);
                // walkotMemory.push_back(new_walikota1);
                listPlayer.push_back(new_petani);
                listPlayer.push_back(new_peternak1);
                listPlayer.push_back(new_walikota1);
                sort(listPlayer.begin(), listPlayer.end(), [](Player *p1, Player *p2)
                     { return p1->getNama() < p2->getNama(); });
                turn = 1;
                jumlahPlayer = listPlayer.size();
                currentPlayer = listPlayer[0];
                player_loaded = true;
                valid_input = true;
                vector<pair<TradeObject, int>> inisialisasiToko;

                for (auto it = productMap.begin(); it != productMap.end(); it++)
                {
                    TradeObject copy_temp(it->second);
                    inisialisasiToko.push_back(make_pair(copy_temp, 0));
                }
                for (auto it = recipeMap.begin(); it != recipeMap.end(); it++)
                {
                    Recipe copyRecipe(it->second);
                    TradeObject copy_temp(copyRecipe.getId(), copyRecipe.getKodeHuruf(), copyRecipe.getNamaGameObject(), copyRecipe.getPrice(), "BANGUNAN");
                    inisialisasiToko.push_back(make_pair(copy_temp, 0));
                }
                for (auto it = plantMap.begin(); it != plantMap.end(); it++)
                {
                    TradeObject copy_temp(it->second);
                    inisialisasiToko.push_back(make_pair(copy_temp, -1));
                }
                for (auto it = animalMap.begin(); it != animalMap.end(); it++)
                {
                    TradeObject copy_temp(it->second);
                    inisialisasiToko.push_back(make_pair(copy_temp, -1));
                }
                shop.initToko(inisialisasiToko);
            }
            else
            {
                cout << "Masukkan lokasi berkas state (b utk back): ";
                cin >> filePath;
                cout << endl;
                filePath.erase(filePath.find_last_not_of(spaces) + 1);
                if (filePath != "b")
                {
                    ifstream playerFile(filePath);
                    if (playerFile)
                    {
                        valid_input = true;
                    }
                    else
                    {
                        cout << "File reading failed!" << endl;
                    }
                }
            }
        } while (!valid_input);

        if (player_loaded)
            return;

        ifstream currentFile(filePath);

        if (!currentFile)
            throw strerror(errno);

        string allText = "";
        string currentText;

        // baca N
        string NText;
        getline(currentFile, NText);
        NText.erase(NText.find_last_not_of(spaces) + 1);
        int N = stoi(NText);
        /*
        while(getline(currentFile, currentText)){
            allText += currentText + '\n';
        }*/
        // allText.erase(allText.find_last_not_of(spaces) + 1);
        // vector<string> splitted = split(allText, '\n');
        // int pVector = 0;
        for (int i = 0; i < N; ++i)
        {
            string playerName;
            getline(currentFile, playerName);
            playerName.erase(playerName.find_last_not_of(spaces) + 1);
            // splitted[i].erase(splitted[pVector].find_last_not_of(spaces) + 1);
            vector<string> playerInfo = split(playerName, ' ');
            int kodePlayer; // 0 bwt petani & peternak, 1 bwt walikota
            Player *new_player;
            if (playerInfo[1] == "Petani")
            {
                new_player = new Petani(playerInfo[0], stoi(playerInfo[2]), stoi(playerInfo[3]), rowPenyimpanan, colPenyimpanan, rowLahan, colLahan);
                // petaniMemory.push_back(new_petani);
                // new_player = &petaniMemory.back();
                kodePlayer = 0;
            }
            else if (playerInfo[1] == "Peternak")
            {
                new_player = new Peternak(playerInfo[0], stoi(playerInfo[2]), stoi(playerInfo[3]), rowPenyimpanan, colPenyimpanan, rowLadang, colLadang);
                // peternakMemory.push_back(new_peternak);
                // new_player = &peternakMemory.back();
                kodePlayer = 0;
            }
            else if (playerInfo[1] == "Walikota")
            {
                new_player = new Walikota(playerInfo[0], stoi(playerInfo[2]), stoi(playerInfo[3]), rowPenyimpanan, colPenyimpanan);
                // walkotMemory.push_back(new_walkot);
                // new_player = &walkotMemory.back();
                kodePlayer = 1;
            }
            else
            {
                throw "muat_player_state(): tipe player tidak diketahui";
            }
            string numberM;
            getline(currentFile, numberM);
            numberM.erase(numberM.find_last_not_of(spaces) + 1);
            int M = stoi(numberM);
            for (int j = 0; j < M; ++j)
            {
                string inventoryString;
                getline(currentFile, inventoryString);
                inventoryString.erase(inventoryString.find_last_not_of(spaces) + 1);
                bool notFound = 1;
                TradeObject *objInInv;
                for (auto it = plantMap.begin(); it != plantMap.end() && notFound; it++)
                {
                    if (it->second.getNama() == inventoryString)
                    {
                        // CultivatedObject copyPlantMap(it->second);
                        // cultObjMemory.push_back(copyPlantMap);
                        objInInv = new CultivatedObject(it->second);
                        notFound = 0;
                    }
                }
                for (auto it = animalMap.begin(); it != animalMap.end() && notFound; it++)
                {
                    if (it->second.getNama() == inventoryString)
                    {
                        // CultivatedObject copyAnimalMap(it->second);
                        // cultObjMemory.push_back(copyAnimalMap);
                        objInInv = new CultivatedObject(it->second);
                        notFound = 0;
                    }
                }
                for (auto it = productMap.begin(); it != productMap.end() && notFound; it++)
                {
                    if (it->second.getNama() == inventoryString)
                    {
                        // ProductObject copyProductMap(it->second);
                        // prodObjMemory.push_back(copyProductMap);
                        objInInv = new ProductObject(it->second);
                        notFound = 0;
                    }
                }
                for (auto it = recipeMap.begin(); it != recipeMap.end() && notFound; it++)
                {
                    if (it->second.getNamaGameObject() == inventoryString)
                    {
                        Recipe copyRecipe(it->second);
                        // cout << "MAKING NEW OBJ" << endl;
                        // TradeObject newTradeObj(copyRecipe.getId(),copyRecipe.getKodeHuruf(),copyRecipe.getNamaGameObject(),copyRecipe.getPrice(),"BANGUNAN");
                        // tradeObjMemory.push_back(newTradeObj);
                        objInInv = new TradeObject(copyRecipe.getId(), copyRecipe.getKodeHuruf(), copyRecipe.getNamaGameObject(), copyRecipe.getPrice(), "BANGUNAN");
                        // cout << "DONE MAKING NEW OBJ" << endl;
                        notFound = 0;
                    }
                }
                if (notFound)
                {
                    // cout << inventoryString << endl;
                    throw "muat_player_state(): notFound";
                }
                new_player->setBarangFirstPenyimpanan(objInInv);
                // cout << j << endl;
            }
            // cout << "SELESAI AMBIL PENYIMPANAN " << i << endl;
            if (!kodePlayer)
            {
                // cout << "SING" << endl;
                string numberK;
                getline(currentFile, numberK);
                numberK.erase(numberK.find_last_not_of(spaces) + 1);
                int K = stoi(numberK);
                for (int k = 0; k < K; ++k)
                {
                    // cout << "K: HERE" << k << endl;
                    string lokasi_nama_berat;
                    getline(currentFile, lokasi_nama_berat);
                    lokasi_nama_berat.erase(lokasi_nama_berat.find_last_not_of(spaces) + 1);
                    vector<string> barangInfo = split(lokasi_nama_berat, ' ');
                    pair<int, int> pairCoord = this->stringToCoord(barangInfo[0]);
                    CultivatedObject *cultObject;
                    for (auto it = animalMap.begin(); it != animalMap.end(); it++)
                    {
                        if (it->second.getNama() == barangInfo[1])
                        {
                            // CultivatedObject copyCultObject(it->second);
                            // cultObjMemory.push_back(copyCultObject);
                            cultObject = new CultivatedObject(it->second);
                        }
                    }
                    for (auto it = plantMap.begin(); it != plantMap.end(); it++)
                    {
                        if (it->second.getNama() == barangInfo[1])
                        {
                            // CultivatedObject copyCultObject(it->second);
                            // cultObjMemory.push_back(copyCultObject);
                            cultObject = new CultivatedObject(it->second);
                        }
                    }
                    cultObject->setWeight(stoi(barangInfo[2]));
                    // cout << pairCoord.first << " " << pairCoord.second << endl;
                    new_player->setBarangLahan(pairCoord.first, pairCoord.second, cultObject);
                }
            }
            listPlayer.push_back(new_player);
        }
        sort(listPlayer.begin(), listPlayer.end(), [](Player *p1, Player *p2)
             { return p1->getNama() < p2->getNama(); });
        // cout << "HERE" << endl;
        string numberItemTokoM;
        getline(currentFile, numberItemTokoM);
        numberItemTokoM.erase(numberItemTokoM.find_last_not_of(spaces) + 1);
        int numberItemM = stoi(numberItemTokoM);
        vector<pair<TradeObject, int>> inisialisasiToko;
        for (int m = 0; m < numberItemM; ++m)
        {
            string itemDanJumlah;
            getline(currentFile, itemDanJumlah);
            itemDanJumlah.erase(itemDanJumlah.find_last_not_of(spaces) + 1);
            vector<string> itemJumlah = split(itemDanJumlah, ' ');

            bool notFound = 1;
            TradeObject *objInInv;
            for (auto it = plantMap.begin(); it != plantMap.end() && notFound; it++)
            {
                if (it->second.getNama() == itemJumlah[0])
                {
                    objInInv = new CultivatedObject(it->second);
                    notFound = 0;
                }
            }
            for (auto it = animalMap.begin(); it != animalMap.end() && notFound; it++)
            {
                if (it->second.getNama() == itemJumlah[0])
                {
                    objInInv = new CultivatedObject(it->second);
                    notFound = 0;
                }
            }
            for (auto it = productMap.begin(); it != productMap.end() && notFound; it++)
            {
                if (it->second.getNama() == itemJumlah[0])
                {
                    objInInv = new ProductObject(it->second);
                    notFound = 0;
                }
            }
            for (auto it = recipeMap.begin(); it != recipeMap.end() && notFound; it++)
            {
                if (it->second.getNamaGameObject() == itemJumlah[0])
                {
                    Recipe copyRecipe(it->second);
                    objInInv = new TradeObject(copyRecipe.getId(), copyRecipe.getKodeHuruf(), copyRecipe.getNamaGameObject(), copyRecipe.getPrice(), "BANGUNAN");
                    notFound = 0;
                }
            }

            TradeObject final_object(*objInInv);
            delete objInInv;

            inisialisasiToko.push_back(make_pair(final_object, stoi(itemJumlah[1])));
        }
        for (auto it = productMap.begin(); it != productMap.end(); it++)
        {
            bool found = 0;
            for (auto &obj : inisialisasiToko)
            {
                if (obj.first.getKodeHuruf() == it->second.getKodeHuruf())
                    found = 1;
            }
            if (!found)
            {
                TradeObject copy_temp(it->second);
                inisialisasiToko.push_back(make_pair(copy_temp, 0));
            }
        }
        for (auto it = recipeMap.begin(); it != recipeMap.end(); it++)
        {
            bool found = 0;
            for (auto &obj : inisialisasiToko)
            {
                if (obj.first.getKodeHuruf() == it->second.getKodeHuruf())
                    found = 1;
            }
            if (!found)
            {
                Recipe copyRecipe(it->second);
                TradeObject copy_temp(copyRecipe.getId(), copyRecipe.getKodeHuruf(), copyRecipe.getNamaGameObject(), copyRecipe.getPrice(), "BANGUNAN");
                inisialisasiToko.push_back(make_pair(copy_temp, 0));
            }
        }
        for (auto it = plantMap.begin(); it != plantMap.end(); it++)
        {
            TradeObject copy_temp(it->second);
            inisialisasiToko.push_back(make_pair(copy_temp, -1));
        }
        for (auto it = animalMap.begin(); it != animalMap.end(); it++)
        {
            TradeObject copy_temp(it->second);
            inisialisasiToko.push_back(make_pair(copy_temp, -1));
        }
        turn = 1;
        jumlahPlayer = listPlayer.size();
        currentPlayer = listPlayer[0];
        shop.initToko(inisialisasiToko);
    }

    void simpan()
    {
        string lokasi = "";

        cout << "Masukkan lokasi berkas state: ";
        cin >> lokasi;
        cout << endl;

        ofstream file(lokasi);

        if (!file.good())
        {
            cout << "Lokasi berkas tidak valid" << endl;
        }
        else
        {
            int jumlahPlayer = listPlayer.size();
            file << jumlahPlayer << endl;
            for (int i = 0; i < listPlayer.size(); ++i)
            {
                // cout << i << endl;
                string usrnm = listPlayer[i]->getNama();
                // cout << "i" << endl;
                string tipe = listPlayer[i]->getPeran();
                // cout << "10" << endl;
                int berat_badan = listPlayer[i]->getBerat();
                // cout << "4" << endl;
                int uang = listPlayer[i]->getUang();
                // cout << i << endl;
                file << usrnm << " " << tipe << " " << berat_badan << " " << uang << endl;
                vector<string> allNamaBarang = listPlayer[i]->getAllNamaBarang();
                file << allNamaBarang.size() << endl;
                for (auto &x : allNamaBarang)
                {
                    file << x << endl;
                }
                // cout << i << " " << i << endl;
                if (listPlayer[i]->getPeran() == "Peternak" || listPlayer[i]->getPeran() == "Petani")
                {
                    vector<pair<pair<int, int>, pair<string, int>>> allPosisiNamaBerat = listPlayer[i]->getAllPosisiNamaBerat();
                    file << allPosisiNamaBerat.size() << endl;
                    // cout << "PENYIMPANAN" << i << endl;
                    for (auto &x : allPosisiNamaBerat)
                    {
                        file << coordToString(x.first.first, x.first.second) << " " << x.second.first << " " << x.second.second << endl;
                    }
                }
            }
            // TODO: TULIS TOKO ABIS INI
            file.close();
        }
    }

    int getJumlahPlayer()
    {
        return this->jumlahPlayer;
    }

    string getPlayerNama(int i)
    {
        return this->listPlayer[i]->getNama();
    }

    int bayarPajakPlayer(int i)
    {
        return this->listPlayer[i]->bayarPajak();
    }
    string getPeranPlayer(int i)
    {
        return this->listPlayer[i]->getPeran();
    }

    void cetakLahanLadang()
    {
        currentPlayer->cetakLadangLahan();
        vector<TradeObject *> listUnik = currentPlayer->getLahan().getUniqueValue();
        cout << endl;
        for (TradeObject *elmt : listUnik)
        {
            cout << " - " << elmt->getKodeHuruf() << ": " << elmt->getNama() << endl;
        }
    }

    void cetakPenyimpanan()
    {
        currentPlayer->cetakPenyimpanan();
        // cout << "Total slot kosong: " << currentPlayer->lahan.getRow() * getCol() - getJumlahIsi() << endl;
    }

    void panen()
    {
        cetakLahanLadang();
        cout << endl
             << endl;

        map<string, int> mapPanenJumlah;
        vector<string> kodeHurufSiapPanen;
        vector<string> KoorPanen;
        string tipe;
        int noTanaman = 0;
        int jumlahPanen = 0;
        pair<int, int> koordinat;
        string kodeKoordinat;
        int banyakHasil = 0;

        if (currentPlayer->getPeran() == "Petani")
        {
            tipe = "tanaman";
        }
        else
        {
            tipe = "Hewan";
        }

        for (auto &listObjek : currentPlayer->getLahan().getStorage())
        {
            for (auto &objek : listObjek)
            {
                if (objek->getKodeHuruf() != "   " & objek->getCurrentBerat() >= objek->getCultivateWeight())
                {
                    mapPanenJumlah[objek->getKodeHuruf()]++;
                }
            }
        }

        if (mapPanenJumlah.size() == 0)
        {
            throw PanenKosongException();
        }

        cout << "Pilih " << tipe << " siap panen yang kamu miliki" << endl;
        int noPanen = 1;
        for (auto &objek : mapPanenJumlah)
        {
            cout << "   " << noPanen << ". " << objek.first << "(" << objek.second << " petak siap dipanen)" << endl;
            kodeHurufSiapPanen.push_back(objek.first);
            noPanen++;
        }

        while (noTanaman < 1 || noTanaman > mapPanenJumlah.size())
        {
            cout << "Nomor " << tipe << " yang ingin dipanen: ";
            string temp;
            cin >> temp;
            try
            {
                int tempNoTanaman = stoi(temp);
                noTanaman = tempNoTanaman;
            }
            catch (...)
            {
                cout << "Masukkan Anda tidak valid!" << endl;
            }
        }

        string kode_dipilih = kodeHurufSiapPanen[noTanaman - 1];

        string nama_dipilih = "";

        for (auto &it : animalMap)
        {
            if (it.second.getKodeHuruf() == kode_dipilih)
            {
                nama_dipilih = it.second.getNama();
                break;
            }
        }

        for (auto &it : plantMap)
        {
            if (it.second.getKodeHuruf() == kode_dipilih)
            {
                nama_dipilih = it.second.getNama();
                break;
            }
        }

        vector<ProductObject> productResult;

        vector<vector<TradeObject *>> penyimpananPlayer = currentPlayer->getPenyimpanan();

        for (auto it = productMap.begin(); it != productMap.end(); it++)
        {
            if (it->second.getOrigin() == nama_dipilih)
            {
                ProductObject temp_prod_obj(it->second);
                productResult.push_back(temp_prod_obj);
            }
        }

        int kosong = 0;

        for (auto &row_penyimpanan : penyimpananPlayer)
        {
            for (auto &elemen_penyimpanan : row_penyimpanan)
            {
                if (elemen_penyimpanan->getKodeHuruf() == "   ")
                {
                    kosong++;
                }
            }
        }

        if (kosong < productResult.size())
        {
            cout << "Penyimpanan tidak cukup untuk mengambil product itu!" << endl;
            return;
        }

        while (jumlahPanen < 1 || jumlahPanen > mapPanenJumlah[kodeHurufSiapPanen[noTanaman - 1]] || (int)(jumlahPanen * productResult.size()) > kosong)
        {

            cout << "Berapa petak yang ingin dipanen:: ";
            string temp;
            cin >> temp;
            try
            {
                int tempNoTanaman = stoi(temp);
                jumlahPanen = tempNoTanaman;
            }
            catch (...)
            {
                cout << "Masukkan Anda tidak valid!" << endl;
            }
        }

        if (currentPlayer->getLahan().isFull())
        {
            throw penyimpananPenuhException();
        }

        cout << "Pilih petak yang ingin dipanen:" << endl;
        for (int i = 0; i < jumlahPanen; i++)
        {
            bool notValid = 0;
            do
            {
                try
                {
                    cout << "Petak ke-" << i + 1 << ": ";
                    cin >> kodeKoordinat;
                    koordinat = stringToCoord(kodeKoordinat);
                    notValid = 0;
                }
                catch (const exception &e)
                {
                    cout << "Masukan anda tidak valid!" << endl;
                    notValid = 1;
                }
            } while (
                notValid || (currentPlayer->getLahan().getBarang(koordinat.first, koordinat.second)->getKodeHuruf() != kodeHurufSiapPanen[noTanaman - 1] ||
                             currentPlayer->getLahan().getBarang(koordinat.first, koordinat.second)->getCurrentBerat() < currentPlayer->getLahan().getBarang(koordinat.first, koordinat.second)->getCultivateWeight()));
            KoorPanen.push_back(kodeKoordinat);
        }
        cout << jumlahPanen << " petak " << tipe << " " << kodeHurufSiapPanen[noTanaman - 1] << " pada cetak ";
        for (int i = 0; i < KoorPanen.size(); i++)
        {
            cout << KoorPanen[i];

            vector<vector<TradeObject *>> tempPenyimpananPlayer = currentPlayer->getPenyimpanan();

            int row_peny_kosong = -1, col_peny_kosong = -1;
            for (int i = 0; i < tempPenyimpananPlayer.size(); ++i)
            {
                for (int j = 0; j < tempPenyimpananPlayer[i].size(); ++j)
                {
                    if (tempPenyimpananPlayer[i][j]->getKodeHuruf() == "   ")
                    {
                        row_peny_kosong = i;
                        col_peny_kosong = j;
                        break;
                    }
                }
            }
            pair<int, int> koordinat_dipanen = stringToCoord(KoorPanen[i]);
            for (auto &product_result : productResult)
            {
                ProductObject *new_pointer_prod_obj = new ProductObject(product_result);
                currentPlayer->panen(row_peny_kosong, col_peny_kosong, koordinat_dipanen.first, koordinat_dipanen.second, new_pointer_prod_obj);
            }
            if (i != KoorPanen.size() - 1)
                cout << ", ";
        }
        cout << " telah dipanen!" << endl;
    }

    void tanam()

    {
        if (listPlayer[turn - 1]->getPeran() != "Petani")
        {
            cout << "Anda bukan petani mass!" << endl;
            throw invalidCommandException();
        }
        vector<string> allNamaBarang = listPlayer[turn - 1]->getAllNamaBarang();
        bool notFound = 1;
        for (auto it = allNamaBarang.begin(); it != allNamaBarang.end() && notFound; it++)
        {
            for (auto &plant : plantMap)
            {
                if (plant.second.getNamaGameObject() == *it)
                {
                    notFound = 0;
                }
            }
        }
        if (notFound)
        {
            cout << "Tidak ada tanaman di penyimpanan Anda!!" << endl;
            throw invalidCommandException();
        }
        vector<pair<pair<int, int>, pair<string, int>>> isiLahan = listPlayer[turn - 1]->getAllPosisiNamaBerat();
        if (isiLahan.size() == rowLahan * colLahan)
        {
            cout << "Ladang penuh!! Kosongkan dulu ladangmu :))" << endl;
            throw invalidCommandException();
        }
        vector<vector<TradeObject *>> penyimpananSkrg = listPlayer[turn - 1]->getPenyimpanan();
        cout << "Pilih tanaman dari penyimpanan" << endl;
        listPlayer[turn - 1]->cetakPenyimpanan();
        string slotTanam = "";
        pair<int, int> currentCoordPenyimpanan;
        do
        {
            cout << "Slot: ";
            cin >> slotTanam;
            currentCoordPenyimpanan = stringToCoord(slotTanam);
        } while (currentCoordPenyimpanan.first < 0 || currentCoordPenyimpanan.second < 0 || currentCoordPenyimpanan.first >= rowPenyimpanan || currentCoordPenyimpanan.second >= colPenyimpanan || penyimpananSkrg[currentCoordPenyimpanan.first][currentCoordPenyimpanan.second]->getKodeHuruf() == "   " || (penyimpananSkrg[currentCoordPenyimpanan.first][currentCoordPenyimpanan.second]->getType() != "MATERIAL_PLANT" && penyimpananSkrg[currentCoordPenyimpanan.first][currentCoordPenyimpanan.second]->getType() != "FRUIT_PLANT"));

        cout << "Kamu memilih " << penyimpananSkrg[currentCoordPenyimpanan.first][currentCoordPenyimpanan.second]->getNama() << endl
             << endl;
        cout << "Pilih petak tanah yang akan ditanami\n\n";
        listPlayer[turn - 1]->cetakLadangLahan();

        string slotMenanam = "";
        pair<int, int> currentCoordMenanam;
        Field<CultivatedObject> lahanSkrg = listPlayer[turn - 1]->getLahan();
        do
        {
            cout << "Slot: ";
            cin >> slotMenanam;
            currentCoordMenanam = stringToCoord(slotMenanam);
        } while (currentCoordMenanam.first < 0 || currentCoordMenanam.second < 0 || currentCoordMenanam.first >= rowLahan || currentCoordMenanam.second >= colLahan || lahanSkrg.getStorage()[currentCoordMenanam.first][currentCoordMenanam.second]->getKodeHuruf() != "   ");
        // membuat pointer baru untuk tanaman
        TradeObject *temp = listPlayer[turn - 1]->getPenyimpanan()[currentCoordPenyimpanan.first][currentCoordPenyimpanan.second];
        CultivatedObject *tanamanBaru = new CultivatedObject(temp->getId(), temp->getKodeHuruf(), temp->getNama(), temp->getType(), temp->getCultivateWeight(), temp->getPrice());
        // set kosong dan tanam
        listPlayer[turn - 1]->setBarangPenyimpananKosong(currentCoordPenyimpanan.first, currentCoordPenyimpanan.second);
        // mencari
        listPlayer[turn - 1]->setBarangLahan(currentCoordMenanam.first, currentCoordMenanam.second, tanamanBaru);
        cout << "Cangkul, cangkul, cangkul yang dalam~!\n";
        cout << tanamanBaru->getNama() << " berhasil ditanam!\n\n";
    }

    void ternak()

    {
        if (listPlayer[turn - 1]->getPeran() != "Peternak")
        {
            cout << "Anda bukan peternak mass!" << endl;
            throw invalidCommandException();
        }
        vector<string> allNamaBarang = listPlayer[turn - 1]->getAllNamaBarang();
        bool notFound = 1;
        for (auto it = allNamaBarang.begin(); it != allNamaBarang.end() && notFound; it++)
        {
            for (auto &hewan : animalMap)
            {
                if (hewan.second.getNamaGameObject() == *it)
                {
                    notFound = 0;
                }
            }
        }
        if (notFound)
        {
            cout << "Tidak ada hewan di penyimpanan Anda!!" << endl;
            throw invalidCommandException();
        }
        vector<pair<pair<int, int>, pair<string, int>>> isiLadang = listPlayer[turn - 1]->getAllPosisiNamaBerat();
        if (isiLadang.size() == rowLadang * colLadang)
        {
            cout << "Peternakan penuh!! Kosongkan dulu peternakanmu :))" << endl;
            throw invalidCommandException();
        }
        vector<vector<TradeObject *>> penyimpananSkrg = listPlayer[turn - 1]->getPenyimpanan();
        cout << "Pilih hewan dari penyimpanan" << endl;
        listPlayer[turn - 1]->cetakPenyimpanan();
        string slotHewan = "";
        pair<int, int> currentCoordPenyimpanan;
        do
        {
            cout << "Slot: ";
            cin >> slotHewan;
            currentCoordPenyimpanan = stringToCoord(slotHewan);
        } while (currentCoordPenyimpanan.first < 0 || currentCoordPenyimpanan.second < 0 || currentCoordPenyimpanan.first >= rowPenyimpanan || currentCoordPenyimpanan.second >= colPenyimpanan || penyimpananSkrg[currentCoordPenyimpanan.first][currentCoordPenyimpanan.second]->getKodeHuruf() == "   " || (penyimpananSkrg[currentCoordPenyimpanan.first][currentCoordPenyimpanan.second]->getType() != "HERBIVORE" && penyimpananSkrg[currentCoordPenyimpanan.first][currentCoordPenyimpanan.second]->getType() != "CARNIVORE" && penyimpananSkrg[currentCoordPenyimpanan.first][currentCoordPenyimpanan.second]->getType() != "OMNIVORE"));

        cout << "Kamu memilih " << penyimpananSkrg[currentCoordPenyimpanan.first][currentCoordPenyimpanan.second]->getNama() << endl
             << endl;
        cout << "Pilih petak tanah yang akan ditinggali\n\n";
        listPlayer[turn - 1]->cetakLadangLahan();

        string slotMenternak = "";
        pair<int, int> currentCoordMenternak;
        Field<CultivatedObject> lahanSkrg = listPlayer[turn - 1]->getLahan();
        do
        {
            cout << "Petak tanah: ";
            cin >> slotMenternak;
            currentCoordMenternak = stringToCoord(slotMenternak);
        } while (currentCoordMenternak.first < 0 || currentCoordMenternak.second < 0 || currentCoordMenternak.first >= rowLadang || currentCoordMenternak.second >= colLadang || lahanSkrg.getStorage()[currentCoordMenternak.first][currentCoordMenternak.second]->getKodeHuruf() != "   ");
        // membuat pointer baru untuk tanaman
        TradeObject *temp = listPlayer[turn - 1]->getPenyimpanan()[currentCoordPenyimpanan.first][currentCoordPenyimpanan.second];
        CultivatedObject *hewanBaru = new CultivatedObject(temp->getId(), temp->getKodeHuruf(), temp->getNama(), temp->getType(), temp->getCultivateWeight(), temp->getPrice());
        // set kosong dan tanam
        listPlayer[turn - 1]->setBarangPenyimpananKosong(currentCoordPenyimpanan.first, currentCoordPenyimpanan.second);
        // mencari
        listPlayer[turn - 1]->setBarangLahan(currentCoordMenternak.first, currentCoordMenternak.second, hewanBaru);
        cout << "Dengan hati-hati, kamu meletakkan seekor " << hewanBaru->getNama() << " di kandang.\n\n";
        cout << hewanBaru->getNama() << " telah menjadi peliharaanmu sekarang\n\n";
    }

    void kasihMakan()
    {
        if (listPlayer[turn - 1]->getPeran() != "Peternak")
        {
            throw invalidCommandException();
        }
        listPlayer[turn - 1]->cetakLadangLahan();
        vector<vector<CultivatedObject *>> isiLahan = listPlayer[turn - 1]->getLahan().getStorage();
        vector<vector<TradeObject *>> penyimpananSemua = listPlayer[turn - 1]->getPenyimpanan();
        bool valid = 0;
        int status = 0;
        for (auto &isi_row_lahan : isiLahan)
        {
            for (auto &isi_lahan : isi_row_lahan)
            {
                for (auto &isi_row_penyimpanan : penyimpananSemua)
                {
                    for (auto &isiPenyimpanan : isi_row_penyimpanan)
                    {
                        if ((isiPenyimpanan->getType() == "PRODUCT_FRUIT_PLANT" && ((isi_lahan->getType() == "HERBIVORE") || (isi_lahan->getType() == "OMNIVORE"))) || (isiPenyimpanan->getType() == "PRODUCT_ANIMAL" && (isi_lahan->getType() == "CARNIVORE") || (isi_lahan->getType() == "OMNIVORE")))
                        {
                            valid = 1;
                            if (isi_lahan->getType() == "HERBIVORE")
                                status |= 1;
                            else if (isi_lahan->getType() == "CARNIVORE")
                                status |= 2;
                            else
                                status |= 4;
                        }
                    }
                }
            }
        }
        if (!valid)
        {
            cout << "KASIH_MAKAN TIDAK DAPAT DILAKUKAN: TIDAK ADA HEWAN YANG DAPAT DIBERI MAKANAN DALAM PENYIMPANAN" << endl;
            return;
        }
        string coordInput;
        bool notValid = 1;
        string namaHewan;
        string tipeHewan;
        pair<int, int> petakKandang;
        pair<int, int> petakPenyimpanan;
        do
        {
            cout << "Petak kandang: ";
            cin >> coordInput;
            try
            {
                pair<int, int> realCoord = stringToCoord(coordInput);
                if (realCoord.first < 0 || realCoord.second < 0 || realCoord.first >= rowLadang || realCoord.second >= colLadang)
                {
                    notValid = 1;
                }
                else
                {
                    if (isiLahan[realCoord.first][realCoord.second]->getKodeHuruf() == "   ")
                    {
                        cout << "Uh petak ini kosong mas!" << endl;
                        notValid = 1;
                    }
                    else
                    {
                        string tipe_hewan = isiLahan[realCoord.first][realCoord.second]->getType();
                        if ((tipe_hewan == "HERBIVORE" && !(status & 1)) || (tipe_hewan == "CARNIVORE" && !(status & 2)) || (tipe_hewan == "OMNIVORE" && !(status & 4)))
                        {
                            cout << "TIDAK ADA MAKANAN DALAM PENYIMPANAN UNTUK DIMAKAN" << endl;
                            notValid = 1;
                        }
                        else
                        {
                            tipeHewan = tipe_hewan;
                            namaHewan = isiLahan[realCoord.first][realCoord.second]->getNama();
                            petakKandang = realCoord;
                            notValid = 0;
                        }
                    }
                }
            }
            catch (...)
            {
                notValid = 1;
            }
        } while (notValid);
        cout << "Kamu memilih " << namaHewan << " untuk diberi makan." << endl;
        cout << "Pilih pangan yang akan diberikan:" << endl;
        listPlayer[turn - 1]->cetakPenyimpanan();
        notValid = 1;
        do
        {
            cout << "Slot: ";
            cin >> coordInput;
            try
            {
                pair<int, int> realCoord = stringToCoord(coordInput);
                if (realCoord.first < 0 || realCoord.second < 0 || realCoord.first >= rowPenyimpanan || realCoord.second >= colPenyimpanan)
                {
                    notValid = 1;
                }
                else
                {
                    if (penyimpananSemua[realCoord.first][realCoord.second]->getKodeHuruf() == "   ")
                    {
                        cout << "Uh petak ini kosong mas!" << endl;
                        notValid = 1;
                    }
                    else
                    {
                        string tipe_barang = penyimpananSemua[realCoord.first][realCoord.second]->getType();
                        if ((tipe_barang == "PRODUCT_FRUIT_PLANT" && ((tipeHewan == "HERBIVORE") || (tipeHewan == "OMNIVORE"))) || (tipe_barang == "PRODUCT_ANIMAL" && (tipeHewan == "CARNIVORE") || (tipeHewan == "OMNIVORE")))
                        {
                            notValid = 0;
                            petakPenyimpanan = realCoord;
                        }
                        else
                        {
                            cout << "Makanan ini tidak bisa diberi ke hewan itu!" << endl;
                            notValid = 1;
                        }
                    }
                }
            }
            catch (...)
            {
                notValid = 1;
            }
        } while (notValid);
        listPlayer[turn - 1]->beriPangan(petakPenyimpanan.first, petakPenyimpanan.second, petakKandang.first, petakKandang.second);
        vector<vector<CultivatedObject *>> storageBaru = listPlayer[turn - 1]->getLahan().getStorage();
        cout << namaHewan << " sudah diberi makan dan beratnya menjadi " << storageBaru[petakKandang.first][petakKandang.second]->getCurrentBerat() << endl;
    }

    void pungutPajak()
    {
        if (listPlayer[turn - 1]->getPeran() != "Walikota")
        {
            throw invalidCommandException();
        }
        try
        {
            listPlayer[turn - 1]->pungutPajak(listPlayer, listPlayer.size());
        }
        catch (...)
        {
            cout << "Error occured. Returning..." << endl;
        }
    }

    void jual() {
        this->shop.Sell();
    }

    void beli() {
        this->shop.Buy();
    }

    void setPelakuShop(){
        this->shop.setPelaku(getCurrentPlayer());
    }

    void tambahPlayer()
    {
        string jenis_pemain;
        string user;
        cout << "Masukkan jenis pemain: ";
        cin >> jenis_pemain;
        cout << "Masukkan nama pemain: ";
        cin >> user;
        try
        {
            listPlayer[turn - 1]->tambahPlayer(jenis_pemain);
            Player *new_player;
            if (jenis_pemain == "Peternak")
            {
                new_player = new Peternak(user, 40, 50, rowPenyimpanan, colPenyimpanan, rowLadang, colLadang);
            }
            else
            {
                new_player = new Petani(user, 40, 50, rowPenyimpanan, colPenyimpanan, rowLahan, colLahan);
            }
            listPlayer.push_back(new_player);
        }
        catch (const uangTidakCukupException &utc)
        {
            cout << "Uang tidak cukup!" << endl;
        }
        catch (const invalidCommandException &ice)
        {
            cout << "Anda tidak dapat menambah pemain!" << endl;
        }
        catch (...)
        {
            cout << "tambahPlayer: error lain ditemui" << endl;
        }
    }

    void next()
    {
        cout << "Giliran dilanjut ke pemain berikutnya." << endl;
        this->nextTurn();
        for (int i = 0; i < this->listPlayer.size(); i++)
        {
            if (listPlayer[i]->getPeran() == "Petani")
            {
                listPlayer[i]->next();
            }
        }
    }

    void bangun()
    {
        if (listPlayer[turn - 1]->getPeran() != "Walikota")
        {
            throw invalidCommandException();
        }
        try
        {
            cout << "Resep bangunan yang ada adalah sebagai berikut." << endl;
            int i = 1;
            for (auto ite = recipeMap.begin(); ite != recipeMap.end(); ite++)
            {
                cout << i << ". " << ite->second.getNamaGameObject();
                if (ite->second.getListMaterial().size() == 0)
                {
                    cout << "\n";
                }
                else
                {
                    cout << " (";
                    for (int j = 0; j < ite->second.getListMaterial().size(); j++)
                    {
                        if (j != ite->second.getListMaterial().size() - 1)
                            cout << ite->second.getListMaterial()[j] << " " << ite->second.getMaterialQuantity()[j] << ",";
                        else
                        {
                            cout << ite->second.getListMaterial()[j] << " " << ite->second.getMaterialQuantity()[j] << ")\n";
                        }
                    }
                }
                i++;
            }
            string input;
            bool valid = false;
            do
            {
                cout << "Bangunan yang ingin dibangun: ";
                cin >> input;
                try
                {

                    for (auto &ite : recipeMap)
                    {
                        if (ite.second.getNamaGameObject() == input)
                        {

                            listPlayer[turn - 1]->bangunBangunan(ite.second);
                            valid = true;
                        }
                    }
                    if (!valid)
                    {
                        cout << "Kamu tidak punya resep bangunan tersebut!" << endl;
                    }
                    else
                    {
                        cout << input << " berhasil dibangun dan telah menjadi hak milik walikota!" << endl;
                        ;
                    }
                }
                catch (KurangMaterialException &kme)
                {
                    cout << kme.message();
                }
            } while (!valid);
        }
        catch (...)
        {
            cout << "Error occured. Returning..." << endl;
        }
    }

 void makan(){
            vector<vector<TradeObject*>> penyimpanan_pemain = listPlayer[turn - 1]->getPenyimpanan();
            bool foodExist = false;
            for(auto &row_penyimpanan_pemain: penyimpanan_pemain){
                for(auto &elem_penyimpanan: row_penyimpanan_pemain){
                    for(auto &product: productMap){
                        if(elem_penyimpanan->getKodeHuruf() != "   " && product.second.getAddedWeight() != 0 && elem_penyimpanan->getKodeHuruf() == product.second.getKodeHuruf()){
                            foodExist = true;
                        }
                    }
                }
            }
            if(!foodExist){
                cout << "Anda tidak punya makanan yang bisa dimakan!" << endl;
                return;
            }

            cout << "Pilih makanan dari penyimpanan\n\n";
            string input_petak;
            bool notValid = 1;
            pair<int, int> coord_input;
            this->listPlayer[turn - 1]->cetakPenyimpanan();
            
            do{
                notValid = 0;
                cout << "Slot: ";
                cin >> input_petak;
                coord_input = stringToCoord(input_petak);
                if (!(coord_input.first < 0 || coord_input.second < 0 || coord_input.first >= rowPenyimpanan || coord_input.second >= colPenyimpanan)){
                 
                    try{

                        listPlayer[turn - 1]->makan(coord_input.first,coord_input.second);
                        notValid = 0;
                        // cout << new_tr_obj->getType();
                    }catch( BukanMakananException e){
                        // cout << new_tr_obj->getType();
                        cout << e.message();
                        notValid = 1;
                    }catch(MakananKosongException e){
                        cout << e.message();
                        notValid = 1;
                    }
                }

            }while(notValid || (coord_input.first < 0 || coord_input.second < 0 || coord_input.first >= rowPenyimpanan || coord_input.second >= colPenyimpanan) || penyimpanan_pemain[coord_input.first][coord_input.second]->getKodeHuruf() == "   " || productMap.find(penyimpanan_pemain[coord_input.first][coord_input.second]->getKodeHuruf()) == productMap.end() || productMap[penyimpanan_pemain[coord_input.first][coord_input.second]->getKodeHuruf()].getAddedWeight() == 0);

            cout << "Dengan lahapnya, kamu memakanan hidangan itu" << endl;
            cout << "Alhasil, berat badan kamu naik menjadi " << listPlayer[turn - 1]->getBerat() << endl;
        }


};

#endif
