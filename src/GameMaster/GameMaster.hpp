#ifndef GAMEMASTER_HPP
#define GAMEMASTER_HPP

#include "../Player/Player.hpp"
#include "../Player/Petani.hpp"
#include "../Player/Peternak.hpp"
#include "../Player/Walikota.hpp"
#include "../GameObject/GameObject.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string.h>

#include <vector>
#include <algorithm>
#include <map>

using namespace std;

string const pathConfig = "./config";

const char* spaces = " \n\r\t";

class Game {
    public:
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
        vector<Player*> listPlayer;
        map<string, CultivatedObject> plantMap;
        map<string, CultivatedObject> animalMap;
        map<string, ProductObject> productMap;
        map<string, Recipe> recipeMap;
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
        Game(){}
        void nextTurn() {
            if (turn == jumlahPlayer){
                turn = 1;
            } else {
                turn++;
            }
        }

        Player* getCurrentPlayer() {
            return this->listPlayer[turn - 1];
        }

        vector<Player*> getListPlayer() {
            return this->listPlayer;
        }

       // return pair p, p.first = row, p.second = col
        pair<int, int> stringToCoord(string s){
            if(s.size() != 3){
                return make_pair(-1, -1);
            }
            char col = s[0];
            char row = 10 * (s[1] - '0') + (s[2] - '0');
            int colNum = col - 'A';
            int rowNum = row - 1;
            return make_pair(rowNum, colNum);
        }

        string coordToString(int row, int col){
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

        void readPlant(vector<string> tokens){
            if(tokens.size() != 6) throw "readPlant: panjang token != 6";
            CultivatedObject plant(stoi(tokens[0]), tokens[1], tokens[2], tokens[3], stoi(tokens[4]), stoi(tokens[5]));
            plantMap[tokens[1]] = plant;
        }

        void readAnimal(vector<string> tokens){
            if(tokens.size() != 6) throw "readAnimal: panjang token != 6";
            CultivatedObject animal(stoi(tokens[0]), tokens[1], tokens[2], tokens[3], stoi(tokens[4]), stoi(tokens[5]));
            animalMap[tokens[1]] = animal;
        }

        void readProduct(vector<string> tokens){
            if(tokens.size() != 7) throw "readProduct: panjang token != 7";
            ProductObject product(stoi(tokens[0]), tokens[1], tokens[2], stoi(tokens[6]), tokens[3], tokens[4], stoi(tokens[5]));
            productMap[tokens[1]] = product;
        }

        void readRecipe(vector<string> tokens){
            if(tokens.size() < 4 || tokens.size() % 2 == 1) throw "readRecipe: panjang token < 4 atau panjang token ganjil";
            vector<string> materials;
            vector<int> materialQuantity;
            for(int i = 4; i < tokens.size(); i += 2){
                materials.push_back(tokens[i]);
                materialQuantity.push_back(stoi(tokens[i + 1]));
            }
            Recipe recipe(stoi(tokens[0]), tokens[1], tokens[2], stoi(tokens[3]), materials, materialQuantity);
            recipeMap[tokens[1]] = recipe;
        }

        void initialMisc() {
            ifstream MiscFile(pathConfig + "/" + "misc" + ".txt");
            if(!MiscFile) throw strerror(errno);
            string allText = "";
            string currentText;
            while(getline(MiscFile, currentText)){
                allText += currentText + '\n';
            }
            allText.erase(allText.find_last_not_of(spaces)+1);
            vector<string> splitted = split(allText, '\n');
            for(int i = 0; i < 5; ++i){
                string splitString = splitted[i];
                splitString.erase(splitString.find_last_not_of(spaces) + 1);
                
                switch (i){
                case 0:
                    goalUang = stoi(splitString);
                    break;
                case 1:
                    goalBerat = stoi(splitString);
                    break;
                default: // INI SEMUA BISA KEBALIK AWIKWOK
                    vector<string> splittedSpace = split(splitString, ' ');
                    switch(i){
                        case 2:
                            rowPenyimpanan = stoi(splittedSpace[0]); // GAK YAKIN, BISA JADI KEBALIK SAMA YANG BAWAH
                            colPenyimpanan = stoi(splittedSpace[1]);  // GAK TAU MANA ROW MANA COL // UPD: BENER
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
            /*
            this->rowLadang = 10;
            this->colLadang = 8;
            this->rowLahan = 10;
            this->colLahan = 8;
            this->colPenyimpanan = 10;
            this->rowPenyimpanan = 8;*/
            this->listPlayer.push_back(new Walikota("Walikota", 40, 50, this->rowPenyimpanan, this->colPenyimpanan));
            this->listPlayer.push_back(new Petani("Petani1", 40, 50, this->rowPenyimpanan,this->colPenyimpanan, this->rowLahan, this->colLahan));
            this->listPlayer.push_back(new Peternak("Peternak1", 40, 50, this->rowPenyimpanan, this->colPenyimpanan, this->rowLadang, this->colLadang));
            this->jumlahPlayer = listPlayer.size();
        }

        vector<string> split(const string &s, char delim){
            vector<string> result;
            stringstream ss(s);
            string item;
            while(getline(ss, item, delim)){
                result.push_back(item);
            }
            return result;
        }

        void muat_general(string namaFile, void(Game::*func)(vector<string>)){
            ifstream currentFile(pathConfig + "/" + namaFile + ".txt");
            if(!currentFile) throw strerror(errno);
            string allText = "";
            string currentText;
            while(getline(currentFile, currentText)){
                allText += currentText + '\n';
            }
            allText.erase(allText.find_last_not_of(spaces) + 1);
            vector<string> splitted = split(allText, '\n');
            for(auto &splitString: splitted){
                splitString.erase(splitString.find_last_not_of(spaces) + 1);
                vector<string> splittedSpace = split(splitString, ' ');
                (this->*func)(splittedSpace);
            }
        }

        void muat_semua_config(){
            // muat_general dengan argumen function pointer milik Game
            muat_general("plant", &Game::readPlant);
            muat_general("animal", &Game::readAnimal);
            muat_general("product", &Game::readProduct);
            muat_general("recipe", &Game::readRecipe);
            initialMisc();
        }

        void cetak_state(){
            for(auto &p: plantMap){
                p.second.cetak();
                cout << endl;
            }
            cout << endl;
            for(auto &p: animalMap){
                p.second.cetak();
                cout << endl;
            }
            for(auto &p: productMap){
                p.second.cetakBarang();
                cout << endl;
            }
            cout << endl;
            for(auto &p: recipeMap){
                
                p.second.cetak();
                cout << endl;
            }
            cout << endl;
            cout << goalUang << " " << goalBerat << " " << rowPenyimpanan << " " << colPenyimpanan << " " << rowLahan << " " << colLahan << " " << rowLadang << " " << colLadang << endl;
        }

        void muat_player_state(){
            bool player_loaded = false;
            bool valid_input = false;
            string filePath;
            // loading player
            do{
                string input;
                do{
                    cout << "Apakah anda ingin memuat state? (y/n)";
                    cin >> input;
                    cout << endl;
                    input.erase(input.find_last_not_of(spaces) + 1);
                }while(input != "y" && input != "n");

                if(input == "n"){
                    Player* new_petani = new Petani ("Petani1", 40, 50, rowPenyimpanan, colPenyimpanan, rowLahan, colLahan);
                    Player* new_peternak1 = new Peternak("Peternak1", 40, 50, rowPenyimpanan, colPenyimpanan, rowLadang, colLadang);
                    Player* new_walikota1 = new Walikota("Walikota1", 40, 50, rowPenyimpanan, colPenyimpanan);
                    //petaniMemory.push_back(new_petani1);
                    //peternakMemory.push_back(new_peternak1);
                    //walkotMemory.push_back(new_walikota1);
                    listPlayer.push_back(new_petani);
                    listPlayer.push_back(new_peternak1);
                    listPlayer.push_back(new_walikota1);
                    sort(listPlayer.begin(), listPlayer.end(), [](Player* p1, Player* p2){
                        return p1->getNama() < p2->getNama();
                    });
                    player_loaded = true;
                    valid_input = true;
                }else{
                    cout << "Masukkan lokasi berkas state (b utk back): ";
                    cin >> filePath;
                    cout << endl;
                    filePath.erase(filePath.find_last_not_of(spaces) + 1);
                    if(filePath != "b"){
                        ifstream playerFile(filePath);
                        if(playerFile){
                            valid_input = true;
                        }else{
                            cout << "File reading failed!" << endl;
                        }
                    }
                }
            }while(!valid_input);

            if(player_loaded) return;

            ifstream currentFile(filePath);

            if(!currentFile) throw strerror(errno);
            
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
            //allText.erase(allText.find_last_not_of(spaces) + 1);
            //vector<string> splitted = split(allText, '\n');
            //int pVector = 0;
            for(int i = 0; i < N; ++i){
                string playerName;
                getline(currentFile, playerName);
                playerName.erase(playerName.find_last_not_of(spaces) + 1);
                //splitted[i].erase(splitted[pVector].find_last_not_of(spaces) + 1);
                vector<string> playerInfo = split(playerName, ' ');
                int kodePlayer; // 0 bwt petani & peternak, 1 bwt walikota
                Player* new_player;
                if(playerInfo[1] == "Petani"){
                    new_player = new Petani(playerInfo[0], stoi(playerInfo[2]), stoi(playerInfo[3]), rowPenyimpanan, colPenyimpanan, rowLahan, colLahan);
                    //petaniMemory.push_back(new_petani);
                    //new_player = &petaniMemory.back();
                    kodePlayer = 0;
                }else if(playerInfo[1] == "Peternak"){
                    new_player = new Peternak(playerInfo[0], stoi(playerInfo[2]), stoi(playerInfo[3]), rowPenyimpanan, colPenyimpanan, rowLadang, colLadang);                    
                    //peternakMemory.push_back(new_peternak);
                    //new_player = &peternakMemory.back();
                    kodePlayer = 0;
                }else if(playerInfo[1] == "Walikota"){
                    new_player = new Walikota(playerInfo[0], stoi(playerInfo[2]), stoi(playerInfo[3]), rowPenyimpanan, colPenyimpanan);
                    //walkotMemory.push_back(new_walkot);
                    //new_player = &walkotMemory.back();
                    kodePlayer = 1;
                }else{
                    throw "muat_player_state(): tipe player tidak diketahui";
                }
                string numberM;
                getline(currentFile, numberM);
                numberM.erase(numberM.find_last_not_of(spaces) + 1);
                int M = stoi(numberM);
                for(int j = 0; j < M; ++j){
                    string inventoryString;
                    getline(currentFile, inventoryString);
                    inventoryString.erase(inventoryString.find_last_not_of(spaces) + 1);
                    bool notFound = 1;
                    TradeObject* objInInv;
                    for(auto it = plantMap.begin(); it != plantMap.end() && notFound; it++){
                        if(it->second.getNama() == inventoryString){
                            //CultivatedObject copyPlantMap(it->second);
                            //cultObjMemory.push_back(copyPlantMap);
                            objInInv = new CultivatedObject(it->second);
                            notFound = 0;
                        }
                    }
                    for(auto it = animalMap.begin(); it != animalMap.end() && notFound; it++){
                        if(it->second.getNama() == inventoryString){
                            //CultivatedObject copyAnimalMap(it->second);
                            //cultObjMemory.push_back(copyAnimalMap);
                            objInInv = new CultivatedObject(it->second);
                            notFound = 0;
                        }
                    }
                    for(auto it = productMap.begin(); it != productMap.end() && notFound; it++){
                        if(it->second.getNama() == inventoryString){
                            //ProductObject copyProductMap(it->second);
                            //prodObjMemory.push_back(copyProductMap);
                            objInInv = new ProductObject(it->second);
                            notFound = 0;
                        }
                    }
                    for(auto it = recipeMap.begin(); it != recipeMap.end() && notFound; it++){
                        if(it->second.getNamaGameObject() == inventoryString){
                            Recipe copyRecipe(it->second);
                            //cout << "MAKING NEW OBJ" << endl;
                            //TradeObject newTradeObj(copyRecipe.getId(),copyRecipe.getKodeHuruf(),copyRecipe.getNamaGameObject(),copyRecipe.getPrice(),"BANGUNAN");
                            //tradeObjMemory.push_back(newTradeObj);
                            objInInv = new TradeObject(copyRecipe.getId(),copyRecipe.getKodeHuruf(),copyRecipe.getNamaGameObject(),copyRecipe.getPrice(),"BANGUNAN");
                            //cout << "DONE MAKING NEW OBJ" << endl;
                            notFound = 0;
                        }
                    }
                    if(notFound){
                        //cout << inventoryString << endl;
                        throw "muat_player_state(): notFound";
                    }
                    new_player->setBarangFirstPenyimpanan(objInInv);
                    //cout << j << endl;
                }
                //cout << "SELESAI AMBIL PENYIMPANAN " << i << endl;
                if(!kodePlayer){
                    //cout << "SING" << endl;
                    string numberK;
                    getline(currentFile, numberK);
                    numberK.erase(numberK.find_last_not_of(spaces) + 1);
                    int K = stoi(numberK);
                    for(int k = 0; k < K; ++k){
                        //cout << "K: HERE" << k << endl;
                        string lokasi_nama_berat;
                        getline(currentFile, lokasi_nama_berat);
                        lokasi_nama_berat.erase(lokasi_nama_berat.find_last_not_of(spaces) + 1);
                        vector<string> barangInfo = split(lokasi_nama_berat, ' ');
                        pair<int, int> pairCoord = this->stringToCoord(barangInfo[0]);
                        CultivatedObject* cultObject;
                        for(auto it = animalMap.begin(); it != animalMap.end(); it++){
                            if(it->second.getNama() == barangInfo[1]){
                                //CultivatedObject copyCultObject(it->second);
                                //cultObjMemory.push_back(copyCultObject);
                                cultObject = new CultivatedObject(it->second);
                            }
                        }
                        for(auto it = plantMap.begin(); it != plantMap.end(); it++){
                            if(it->second.getNama() == barangInfo[1]){
                                //CultivatedObject copyCultObject(it->second);
                                //cultObjMemory.push_back(copyCultObject);
                                cultObject = new CultivatedObject(it->second);
                            }
                        }
                        cultObject->setWeight(stoi(barangInfo[2]));
                        //cout << pairCoord.first << " " << pairCoord.second << endl;
                        new_player->setBarangLahan(pairCoord.first, pairCoord.second, cultObject);
                    }
                }
                listPlayer.push_back(new_player);
            }
            sort(listPlayer.begin(), listPlayer.end(), [](Player* p1, Player* p2){
                return p1->getNama() < p2->getNama();
            });
            //cout << "HERE" << endl;
            string numberItemTokoM;
            getline(currentFile, numberItemTokoM);
            numberItemTokoM.erase(numberItemTokoM.find_last_not_of(spaces) + 1);
            int numberItemM = stoi(numberItemTokoM);
            vector<pair<TradeObject, int>> inisialisasiToko;
            for(int m = 0; m < numberItemM; ++m){
                string itemDanJumlah;
                getline(currentFile, itemDanJumlah);
                itemDanJumlah.erase(itemDanJumlah.find_last_not_of(spaces) + 1);
                vector<string> itemJumlah = split(itemDanJumlah, ' ');

                bool notFound = 1;
                TradeObject* objInInv;
                for(auto it = plantMap.begin(); it != plantMap.end() && notFound; it++){
                    if(it->second.getNama() == itemJumlah[0]){
                        objInInv = new CultivatedObject(it->second);
                        notFound = 0;
                    }
                }
                for(auto it = animalMap.begin(); it != animalMap.end() && notFound; it++){
                    if(it->second.getNama() == itemJumlah[0]){
                        objInInv = new CultivatedObject(it->second);
                        notFound = 0;
                    }
                }
                for(auto it = productMap.begin(); it != productMap.end() && notFound; it++){
                    if(it->second.getNama() == itemJumlah[0]){
                        objInInv = new ProductObject(it->second);
                        notFound = 0;
                    }
                }
                for(auto it = recipeMap.begin(); it != recipeMap.end() && notFound; it++){
                    if(it->second.getNamaGameObject() == itemJumlah[0]){
                        Recipe copyRecipe(it->second);
                        objInInv = new TradeObject(copyRecipe.getId(),copyRecipe.getKodeHuruf(),copyRecipe.getNamaGameObject(),copyRecipe.getPrice(),"BANGUNAN");
                        notFound = 0;
                    }
                }

                TradeObject final_object(*objInInv);
                delete objInInv;

                inisialisasiToko.push_back(make_pair(final_object, stoi(itemJumlah[1])));
            }
            for(auto it = productMap.begin(); it != productMap.end(); it++){
                bool found = 0;
                for(auto &obj: inisialisasiToko){
                    if(obj.first.getKodeHuruf() == it->second.getKodeHuruf()) found = 1;
                }
                if(!found){
                    TradeObject copy_temp(it->second);
                    inisialisasiToko.push_back(make_pair(copy_temp, 0));
                }
            }
            for(auto it = recipeMap.begin(); it != recipeMap.end(); it++){
                bool found = 0;
                for(auto &obj: inisialisasiToko){
                    if(obj.first.getKodeHuruf() == it->second.getKodeHuruf()) found = 1;
                }
                if(!found){
                    Recipe copyRecipe(it->second);
                    TradeObject copy_temp(copyRecipe.getId(),copyRecipe.getKodeHuruf(),copyRecipe.getNamaGameObject(),copyRecipe.getPrice(),"BANGUNAN");
                    inisialisasiToko.push_back(make_pair(copy_temp, 0));
                }
            }
            for(auto it = plantMap.begin(); it != plantMap.end(); it++){
                TradeObject copy_temp(it->second);
                inisialisasiToko.push_back(make_pair(copy_temp, -1));
            }
            for(auto it = animalMap.begin(); it != animalMap.end(); it++){
                TradeObject copy_temp(it->second);
                inisialisasiToko.push_back(make_pair(copy_temp, -1));
            }
            turn = 1;
            jumlahPlayer = listPlayer.size();
        }

        void simpan(){
            string lokasi = "";    

            cout << "Masukkan lokasi berkas state: ";
            cin >> lokasi;
            cout << endl;

            ofstream file(lokasi);
            
            if(!file.good()){
                cout << "Lokasi berkas tidak valid" << endl;
            }else{
                int jumlahPlayer = listPlayer.size();
                file << jumlahPlayer << endl;
                for(int i = 0; i < listPlayer.size(); ++i){
                    //cout << i << endl;
                    string usrnm = listPlayer[i]->getNama();
                    //cout << "i" << endl;
                    string tipe = listPlayer[i]->getPeran();
                    //cout << "10" << endl;
                    int berat_badan = listPlayer[i]->getBerat();
                    //cout << "4" << endl;
                    int uang = listPlayer[i]->getUang();
                    //cout << i << endl;
                    file << usrnm << " " << tipe << " " << berat_badan << " " << uang << endl;
                    vector<string> allNamaBarang = listPlayer[i]->getAllNamaBarang();
                    file << allNamaBarang.size() << endl;
                    for(auto &x: allNamaBarang){
                        file << x << endl;
                    }
                    //cout << i << " " << i << endl;
                    if(listPlayer[i]->getPeran() == "Peternak" || listPlayer[i]->getPeran() == "Petani"){
                        vector<pair<pair<int, int>, pair<string, int>>> allPosisiNamaBerat = listPlayer[i]->getAllPosisiNamaBerat();
                        file << allPosisiNamaBerat.size() << endl;
                        //cout << "PENYIMPANAN" << i << endl;
                        for(auto &x: allPosisiNamaBerat){
                            file << coordToString(x.first.first, x.first.second) << " " << x.second.first << " " << x.second.second << endl;
                        }
                    }
                }
                // TODO: TULIS TOKO ABIS INI 
                file.close();
            }
        }

        int getJumlahPlayer(){
            return this->jumlahPlayer;
        }

        string getPlayerNama(int i){
            return this->listPlayer[i]->getNama();
        }

        int bayarPajakPlayer(int i){
            return this->listPlayer[i]->bayarPajak();

        }
        string getPeranPlayer(int i){
            return this->listPlayer[i]->getPeran();
        }

        void tanam(){
            if(listPlayer[turn - 1]->getPeran() != "Petani"){
                cout << "Anda bukan petani mass!" << endl;
                throw invalidCommandException();
            }
            vector<string> allNamaBarang = listPlayer[turn - 1]->getAllNamaBarang();
            bool notFound = 1;
            for(auto it = allNamaBarang.begin(); it != allNamaBarang.end() && notFound; it++){
                for(auto &plant: plantMap){
                    if(plant.second.getNamaGameObject() == *it){
                        notFound = 0;
                    }
                }
            }
            if(notFound){
                cout << "Tidak ada tanaman di penyimpanan Anda!!" << endl;
                throw invalidCommandException();
            }
            vector<pair<pair<int, int>, pair<string, int>>> isiLahan = listPlayer[turn - 1]->getAllPosisiNamaBerat();
            if(isiLahan.size() == rowLahan * colLahan){
                cout << "Lahan penuh!! Kosongkan dulu lahanmu :))" << endl;
                throw invalidCommandException();
            }
            vector<vector<TradeObject*>> penyimpananSkrg = listPlayer[turn - 1]->getPenyimpanan();
            cout << "Pilih tanaman dari penyimpanan" << endl;
            listPlayer[turn - 1]->cetakPenyimpanan();
            string slotTanam = "";
            pair<int, int> currentCoord;
            do{
                cout << "Slot: ";
                cin >> slotTanam;
                currentCoord = stringToCoord(slotTanam);
            }while(currentCoord.first < 0 || currentCoord.second < 0 || currentCoord.first >= rowPenyimpanan || currentCoord.second >= colPenyimpanan 
            || penyimpananSkrg[currentCoord.first][currentCoord.second]->getKodeHuruf() == "   ");
            cout << "Kamu memilih " << penyimpananSkrg[currentCoord.first][currentCoord.second]->getNama() << endl;
            //listPlayer[turn - 1]->cetak
        }

        void tambahPlayer(){
            string jenis_pemain;
            string user;
            cout << "Masukkan jenis pemain: ";
            cin >> jenis_pemain;
            cout << "Masukkan nama pemain: ";
            cin >> user;
            try{
                listPlayer[turn - 1]->tambahPlayer(jenis_pemain);
                Player* new_player;
                if(jenis_pemain == "Peternak"){
                    new_player = new Peternak(user, 40, 50, rowPenyimpanan, colPenyimpanan, rowLadang, colLadang);
                }else{
                    new_player = new Petani(user, 40, 50, rowPenyimpanan, colPenyimpanan, rowLahan, colLahan);   
                }
                listPlayer.push_back(new_player);
            }catch(const uangTidakCukupException& utc){
                cout << "Uang tidak cukup!" << endl;
            }catch(const invalidCommandException& ice){
                cout << "Anda tidak dapat menambah pemain!" << endl;
            }catch(...){
                cout << "tambahPlayer: error lain ditemui" << endl;
            }
        }
};

#endif