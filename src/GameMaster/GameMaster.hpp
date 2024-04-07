//#include "../Player/Player.hpp"
#include "../GameObject/GameObject.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string.h>
#include <vector>
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
        //Player* listPlayer;
        int jumlahPlayer;
        int turn;
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
            ProductObject product(stoi(tokens[0]), tokens[1], tokens[2], tokens[3], tokens[4], stoi(tokens[5]), stoi(tokens[6]));
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
                p.second.cetak();
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
            
        }

        void tambah() {

        }
};
