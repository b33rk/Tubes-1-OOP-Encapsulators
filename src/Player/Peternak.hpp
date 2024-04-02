#include "Player.hpp"

class Peternak : public Player {
    private:
        Field lahan;
    public:

        Peternak(int id, string nama) : Player(id,nama,"Peternak"){}
        void beriMakan();
        void ternak(CultivatedObject* hewan, int row, int col){
            this->lahan[row][col] = hewan;
        }
        int hitungKekayaan(Game game){
            int total = 0;
            TradeObject** barang = this->lahan.getBarang();
            for (int i = 0; i < lahan.getRow(); i++){
                for(int j = 0; j<lahan.getCol() ; j++){
                    if (barang[i][j].kode_huruf != "XXX"){
                        int price = game.getPrice(barang[i][j].kode_huruf);
                        total += price;
                    }
                }
            }
            TradeObject** penyimpanan = this->lahan.getPenyimpanan();
            for (int i = 0; i < lahan.getRow(); i++){
                for(int j = 0; j<lahan.getCol() ; j++){
                    if (barang[i][j].kode_huruf != "XXX"){
                        int price = game.getPrice(barang[i][j].kode_huruf);
                        total += price;
                    } 
                }
            }
            total += this->kekayaan;
            return total;
        }
        int bayarPajak(Game game){
            int KKP = hitungKekayaan(game) - 11;
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

