#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP
#include <exception>
#include <stdexcept>
using namespace std;

class MakananSalahException : public exception
{
public:
    const char *message()
    {
        return "Makanan tidak dapat dimakan oleh hewan ini\n";
    }
};

class uangTidakCukupException : public exception
{
public:
    const char *message()
    {
        return "Uang tidak cukup!\n";
    }
};

class tambahPlayerInvalidException : public exception
{
public:
    const char *message()
    {
        return "Peran player tidak valid\n";
    }
};

class invalidCommandException : public exception
{
public:
    const char *message()
    {
        return "Command tidak valid\n";
    }
};

class petakTidakKosongException : public exception
{
public:
    const char *message()
    {
        return "Petak tersebut tidak kosong !\n";
    }
};

class penyimpananPenuhException : public exception
{
private:
    string type;

public:
    string message()
    {
        return this->type + " sudah penuh\n";
    }
    //     penyimpananPenuhException(  )
};

class BukanMakananException : public exception
{
public:
    const char *message()
    {
        return "Barang tersebut bukan makanan mass!!\n";
    }
};

class BarangKosongException : public exception
{
public:
    const char *message()
    {
        return "Barang tersebut kosong mass!!\n";
    }
};

class KurangMaterialException : public exception{
    private:
        vector<string> materials;
        vector<int> quantity;
        string finalMessage;
    public:
        KurangMaterialException(const vector<string>& materials, const vector<int>& quantity) : materials(materials) , quantity(quantity), exception(){
            finalMessage = "Kamu tidak punya sumber daya yang cukup! Masih memerlukan ";
            for (int i = 0 ; i < materials.size() ; i++){
                if (quantity[i] > 0){
                    finalMessage.append(to_string(quantity[i]));
                    finalMessage.append(" ");
                    finalMessage.append(materials[i]);
                    if (i != materials.size() - 1){
                        finalMessage.append(", ");
                    }
                    else {
                        finalMessage.append(" ");
                    }
                }
            }
            finalMessage.append("\n");
        }
        const char* message() {
            return finalMessage.c_str();
        }

};

#endif