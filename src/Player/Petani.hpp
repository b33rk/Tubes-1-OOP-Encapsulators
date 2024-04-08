#include "Player.hpp"
#include "../GameMaster/GameMaster.hpp"

class Petani : public Player {
    private:
        Field<CultivatedObject> ladang;
    public:
        Petani(int id, string nama) : Player(id,nama,"Petani"){
        }
        void next(){
            vector<vector<CultivatedObject*>> barang= this->ladang.getBarang();
            for (int i = 0; i < ladang.getJumlahIsi(); i++){
                for(int j = 0; j<ladang.getRow() ; j++){
                    barang[i][j]->incrementWeight();
                }
            }
        }
        void panen(int, int) {
            // a;
            // product b(nama)
        }
        void tanam(CultivatedObject* tanaman, int row, int col){
            this->ladang.setBarang(row,col,tanaman);         
        }
        int hitungKekayaan(Game game){ //  apakah harus ada game ?
            int total = 0;
            vector<vector<CultivatedObject*>> barang = this->ladang.getBarang();
            for (int i = 0; i < ladang.getRow(); i++){
                for(int j = 0; j<ladang.getCol() ; j++){
                    if (barang[i][j]->getKodeHuruf() != "   "){
                        // int price = game.getPrice(barang[i][j].kode_huruf);
                        int price = barang[i][j]->getPrice();
                        total += price;
                    }
                }
            }
            vector<vector<TradeObject*>> penyimpanan = this->penyimpanan.getBarang();
        
            for (int i = 0; i < ladang.getRow(); i++){
                for(int j = 0; j<ladang.getCol() ; j++){
                    if (barang[i][j]->getKodeHuruf() != "   "){
                        int price = penyimpanan[i][j]->getPrice();
                        total += price;
                    } 
                }
            }
            total += this->kekayaan;
            return total;
        }
        int bayarPajak(Game game){
            int KKP = hitungKekayaan(game) - 13;
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
        void cetakLadang(){
            ladang.cetak();
        }
};


// ask for get in fields