
#include "../GameObject/gameObject.hpp"
#include "../FieldObject/Field.hpp"

class Player{
    protected:
        int id;
        int kekayaan;
        string nama;
        string peran;
        Field penyimpanan;
        
    public:
        Player(int id, string nama, string peran){
            this->id = id;
            this->nama = nama;
            this->peran = peran;
        }
        ~Player() {
        }
        void virtual next(){}
        void virtual muat();
        void virtual jual(int, int);
        void virtual beli(TradeObject*, int);
        void virtual makan();
        void virtual tambahPlayer(Game& game, int id,string nama, string peran);
        // throw utk yg lain selain walikota
        void virtual cetakPenyimpanan(){
            penyimpanan.cetak();
        }

        virtual int bayarPajak();
        void virtual cetakLahan();
        string getNama(){
            return this->nama;
        }
        string getPeran(){
            return this->getPeran();
        }
};