
#include "../GameObject/gameObject.hpp"
#include "../FieldObject/Field.hpp"

class Player{
    protected:
        int id;
        int kekayaan;
        string nama;
        Field penyimpanan;
    public:
        Player(int id, string nama){
            this->id = id;
            this->nama = nama;
        }
        ~Player() {
        }
        void virtual next(){}
        void virtual muat();
        void virtual jual(int, int);
        void virtual beli(TradeObject*, int);
        void virtual makan();
        void virtual tambahPlayer(Game& a, string jenis, string nama);
        // throw utk yg lain selain walikota
        void virtual cetakPenyimpanan(){
            penyimpanan.cetak();
        }

        void virtual bayarPajak();
        void virtual cetakLahan();
};