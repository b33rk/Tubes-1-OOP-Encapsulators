#include "../GameObject/gameObject.hpp"
#include "../FieldObject/Field.hpp"

class Player
{
protected:
    int id;
    int kekayaan;
    int berat;
    int uang;
    string nama;
    string peran;
    Field<TradeObject> penyimpanan;

public:
    Player(int id, string nama, string peran, int berat, int uang);
    ~Player();
    void virtual next() {}
    void virtual muat();
    void virtual jual(int, int);
    void virtual beli(TradeObject *, int);
    void virtual makan();
    void virtual cetakPenyimpanan();
    void virtual cetakLahan();
    string getNama();
    string getPeran();
    int getUang();
    void setUang(int uangBaru);
    void setKekayaan(int kekayaan);
    float persentasePajak(int KKP);
    int virtual bayarPajak();
};