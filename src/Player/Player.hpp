#include "../GameObject/gameObject.hpp"
#include "../FieldObject/Field.hpp"

class Player
{
protected:
    int id;
    int kekayaan;
    int berat;
    string nama;
    string peran;
    Field<TradeObject> penyimpanan;

public:
    Player(int id, string nama, string peran, int berat);
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
    void setKekayaan(int kekayaan);
    float persentasePajak(int KKP);
};