#include "../Player/Player.hpp"
#include "../GameObject/GameObject.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string.h>

string const pathConfig = "../Config";

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
        Player** listPlayer;
        int jumlahPlayer;
        int turn;
    public:
        Game(){}
        void nextTurn() {
            if (turn == jumlahPlayer){
                turn = 1;
            } else {
                turn++;
            }
        }
        void initialMisc() {
            string myText;
            ifstream MiscFile(pathConfig + "/misc.txt");

            getline (MiscFile, myText);
            stringstream ss(myText);
            goalUang = stoi(myText);
        }
        void tambah() {

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
