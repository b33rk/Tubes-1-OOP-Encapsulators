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
    private:
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
    public:
        Game(){}
        void nextTurn() {
            if (turn == jumlahPlayer){
                turn = 1;
            } else {
                turn++;
            }
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
            if(tokens.size() <= 4 || tokens.size() % 2 == 1) throw "readRecipe: panjang token <= 4 atau panjang token ganjil";
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
                            colPenyimpanan = stoi(splittedSpace[1]);  // GAK TAU MANA ROW MANA COL
                            break;
                        case 3:
                            rowLahan = stoi(splittedSpace[0]);
                            colLahan = stoi(splittedSpace[1]);
                            break;
                        case 4:
                            rowLadang = stoi(splittedSpace[0]);
                            colLadang = stoi(splittedSpace[1]);
                            break;
                        default:
                            throw "initialMisc: gak masuk switch case manapun (how)";
                    }
                    break;
                }                
            }
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
                
                //p.second.cetakBarang();
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
                    Player* petani1 = new Petani("Petani1", 40, 50);
                    Player* peternak1 = new Peternak("Peternak1", 40, 50);
                    Player* walikota = new Walikota("Walikota1", 40, 50);
                    listPlayer.push_back(petani1);
                    listPlayer.push_back(peternak1);
                    listPlayer.push_back(walikota);
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
                    new_player = new Petani(playerInfo[0], stoi(playerInfo[2]), stoi(playerInfo[3]));
                    kodePlayer = 0;
                }else if(playerInfo[1] == "Peternak"){
                    new_player = new Peternak(playerInfo[0], stoi(playerInfo[2]), stoi(playerInfo[3]));
                    kodePlayer = 0;
                }else if(playerInfo[1] == "Walikota"){
                    new_player = new Walikota(playerInfo[0], stoi(playerInfo[2]), stoi(playerInfo[3]));
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
                            CultivatedObject copyPlantMap(it->second);
                            objInInv = &copyPlantMap;
                            notFound = 0;
                        }
                    }
                    for(auto it = animalMap.begin(); it != animalMap.end() && notFound; it++){
                        if(it->second.getNama() == inventoryString){
                            CultivatedObject copyAnimalMap(it->second);
                            objInInv = &copyAnimalMap;
                            notFound = 0;
                        }
                    }
                    for(auto it = productMap.begin(); it != productMap.end() && notFound; it++){
                        if(it->second.getNama() == inventoryString){
                            ProductObject copyProductMap(it->second);
                            objInInv = &copyProductMap;
                            notFound = 0;
                        }
                    }
                    if(notFound){
                        throw "muat_player_state(): notFound";
                    }
                    new_player->setBarangFirstPenyimpanan(objInInv);
                }
                if(!kodePlayer){
                    string numberK;
                    getline(currentFile, numberK);
                    numberK.erase(numberK.find_last_not_of(spaces) + 1);
                    int K = stoi(numberK);
                    for(int k = 0; k < K; ++k){
                        string lokasi_nama_berat;
                        getline(currentFile, lokasi_nama_berat);
                        lokasi_nama_berat.erase(lokasi_nama_berat.find_last_not_of(spaces) + 1);
                        
                    }
                }
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

        void tambahGamePlayer(Player* player){
            this->listPlayer[this->jumlahPlayer] = player;
            this->jumlahPlayer++;
        }
};

#endif