
#include "../GameObject/gameObject.hpp"
#include "../FieldObject/Field.hpp"

class Player{
    protected:
        int id;
        int kekayaan;
        int berat;
        string nama;
        string peran;
        Field<TradeObject> penyimpanan;
        
    public:
        Player(int id, string nama, string peran, int berat){
            this->id = id;
            this->nama = nama;
            this->peran = peran;
            this->berat = berat;
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
        void setKekayaan(int kekayaan){
            this->kekayaan = kekayaan;
        }
        float persentasePajak(int KKP){
            if(KKP <= 6){
                return 0.5;
            }else if(KKP <=25){
                return 0.15;
            }else if(KKP <= 50){
                return 0.25;
            }else if(KKP <= 500){
                return 0.3;
            }else{
                return 0.35;
            }
        }
};