#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <iostream>

#include "../GameMaster/GameMaster.hpp"

using namespace std;

class Command {
    private:   
        string command;
        vector<string> commandWalikota, commandPetani, commandPeternak;
    public:
        Command() {

        }

        void terimaCommand() {
            cin >> command;
        }

        bool isValid(string peran) {
            switch(turn) {
                case : 
            }
        }
};

#endif