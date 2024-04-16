#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <iostream>

#include "../GameMaster/GameMaster.hpp"

using namespace std;

class Command
{
private:
    string perintah, peran;
    vector<string> commandWalikota = {
        "NEXT",
        "CETAK_PENYIMPANAN",
        "MAKAN",
        "BELI",
        "JUAL",
        "SIMPAN",
        "PUNGUT_PAJAK",
        "BANGUN",
        "TAMBAH_PEMAIN"};

    vector<string> commandPetani = {
        "NEXT",
        "CETAK_PENYIMPANAN",
        "MAKAN",
        "BELI",
        "JUAL",
        "SIMPAN",
        "CETAK_LADANG",
        "TANAM",
        "PANEN"};

    vector<string> commandPeternak = {
        "NEXT",
        "CETAK_PENYIMPANAN",
        "MAKAN",
        "BELI",
        "JUAL",
        "SIMPAN",
        "CETAK_PETERNAKAN",
        "TERNAK",
        "KASIH_MAKAN",
        "PANEN"};

public:
    Command() {}
    Command(Player *player)
    {
        this->perintah = "";
        this->peran = player->getPeran();
    }

    void terimaCommand()
    {
        cout << ">> ";
        const char *yellow = "\033[0;93;1m";
        const char *reset = "\033[0m";
        cout << yellow;
        cin >> perintah;
        cout << reset;

        // INI PROSEDURAL !
        // if(!isValid(this->peran)){
        //     throw invalidCommandException();
        // }
    }

    bool validateCommand(vector<string> listCommand)
    {
        bool valid = false;
        for (int i = 0; i < listCommand.size(); i++)
        {
            if (this->perintah == listCommand[i])
                valid = true;
        }

        return valid;
    }

    string getPerintah()
    {
        return this->perintah;
    }

    bool isValid(string peran)
    {
        if (peran == "Walikota")
        {
            return validateCommand(commandWalikota);
        }
        else if (peran == "Petani")
        {
            return validateCommand(commandPetani);
        }
        else
        {
            return validateCommand(commandPeternak);
        }
    }

    void displayCommand(vector<string> listCommand)
    {
        cout << "Command yang bisa Anda jalankan :\n";
        for (int i = 0; i < listCommand.size(); i++)
        {
            cout << "- " << listCommand[i] << "\n";
        }
    }

    void displayAvailableCommand()
    {
        if (peran == "Walikota")
        {
            return displayCommand(commandWalikota);
        }
        else if (peran == "Petani")
        {
            return displayCommand(commandPetani);
        }
        else
        {
            return displayCommand(commandPeternak);
        }
    }

    void setPeran(string peran)
    {
        this->peran = peran;
    }
};

#endif