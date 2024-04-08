#include "Player.hpp"

class Peternak : public Player {
    private:
        Field<CultivatedObject> lahan; // sapi dll bisa di panen dan menambah berat jadi diasumsikan sebagai cultivatedobject
    public:

        Peternak(int id, string nama) : Player(id,nama,"Peternak"){}
        void beriMakan();
        void ternak(CultivatedObject* hewan, int row, int col){
            this->lahan.setBarang(row,col,hewan);
        }
        int hitungKekayaan(Game game){ // Apakah harus ada game ?
            int total = 0;
            vector<vector<CultivatedObject*>> barang = this->lahan.getBarang();
            for (int i = 0; i < lahan.getRow(); i++){
                for(int j = 0; j<lahan.getCol() ; j++){
                    if (barang[i][j]->getKodeHuruf() != "  "){
                        int price = barang[i][j]->getPrice();
                        total += price;
                    }
                }
            }
            vector<vector<TradeObject*>> penyimpanan = this->penyimpanan.getBarang();
            for (int i = 0; i < this->penyimpanan.getRow(); i++){
                for(int j = 0; j<this->penyimpanan.getCol() ; j++){
                    if (barang[i][j]->getKodeHuruf() != "   "){
                        int price = barang[i][j]->getPrice();
                        total += price;
                    } 
                }
            }
            total += this->kekayaan;
            return total;
        }
        int bayarPajak(Game game){ // apakah harus ada game ?
            int KKP = this->hitungKekayaan(game) - 11;
            float persentase;
            int pajak;
            if(KKP > 0){
                if(KKP <= 6){
                persentase = 0.5;
                }else if(KKP <=25){
                    persentase = 0.15;
                }else if(KKP <= 50){
                    persentase = 0.25;
                }else if(KKP <= 500){
                    persentase = 0.3;
                }else{
                    persentase = 0.35;
                }
                int pajak = KKP*persentase;
            }else{
                pajak = 0;
            }
            if(pajak > this->kekayaan){
                pajak = this->kekayaan;
                this->setKekayaan(0);
            }else{
                this->setKekayaan(this->kekayaan - pajak);
            }
            return pajak;
        }
        void cetakLahan(){
            lahan.cetak();
        }
};

