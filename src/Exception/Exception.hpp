#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP
#include <exception>

using namespace std;




class MakananSalahException : public exception{
    public:
        const char* message(){
            return  "Makanan tidak dapat dimakan oleh hewan ini\n";
        }
    
};

class uangTidakCukupException : public exception{
    public:
        const char* message(){
            return "Uang tidak cukup!\n";
        }
};

class tambahPlayerInvalidException : public exception{
    public:
        const char* message(){
            return "Peran player tidak valid\n";
        }
};

class invalidCommandException  : public exception{
    public:
        const char* message(){
            return "Command tidak valid\n";
        }
};


#endif