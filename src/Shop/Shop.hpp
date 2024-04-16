#include "../Player/Player.hpp"
#include "../Exception/Exception.hpp"
#include "../GameObject/GameObject.hpp"

class Shop {
    private:
        int numOfItems; // jumlah barang di toko
        Player* pelaku; // peran(walikota, petani, peternak)
        vector<pair<TradeObject, int>> items;    // item yang ada (nama barang, harga)
        
        // apakah bangunan atau tidak
        bool isBangunan(string namaItem) {
            return namaItem == "SMALL_HOUSE" || namaItem == "MEDIUM_HOUSE" || namaItem == "LARGE_HOUSE" || namaItem == "HOTEL";
        }

        pair<int, int> stringToCoord(string s){
            if(s.size() != 3){
                return make_pair(-1, -1);
            }
            char col = s[0];
            char row = 10 * (s[1] - '0') + (s[2] - '0');
            int colNum = col - 'A';
            int rowNum = row - 1;
            return make_pair(rowNum, colNum);
        }

    public:
        Shop() {
            this->numOfItems = 0;
        }

        void initToko(vector<pair<TradeObject, int>> vectorInit) {
            this->numOfItems = vectorInit.size();

            for(int i = 0; i < this->numOfItems; i++) {
                items.push_back({ vectorInit.first, vectorInit.second });
            }
        }

        void displayShop() {
            if(this->numOfItems != 0) {
                for(int i = 0; i < this->numOfItems; i++) {
                    cout << i + 1 << "  " << this->items[i].first.getNama() << " - " << this->items[i].first.getPrice();
                    if(this->items[i].second >= 0) {
                        cout << " berjumlah : "this->items[i].second << "\n";
                    }
                }
            } else {
                cout << "Tidak ada barang yang bisa Anda beli!\n";
            }
        }
        
        void Buy() {
            // validasi peran, uang, slot
            cout << "Selamat datang di toko!!\n";
            cout << "Berikut merupakan hal yang dapat Anda Beli\n";

            displayShop();

            int pilihanBarang, kuantitas;

            try {
                cout << "\nUang Anda : " << pelaku->getUang() << "\n";
                pilihSlot();
 
                cout << "\nBarang ingin dibeli : " << pilihanBarang << "\n";
                pilihBarang(pilihanBarang);

                cout << "Kuantitas : " << kuantitas << "\n";
                beliBarang(kuantitas, pilihanBarang);

                cout << "\nSelamat Anda behasil membeli " << kuantitas << ;
                cout << ". Uang Anda tersisa
                " << pelaku->getUang() << " gulden.\n";
                // display penyimpanan
                cout << "Pilih slot untuk menyimpan barang yang Anda beli!\n";
                pelaku->cetakPenyimpanan();

                cout << "\n\nPilih petak slot yang ingin diisi : \n"
                for(int i = 0; i < kuantitas; i++) {
                    string inputSlot;
                    cout << i+1 << ".   " << inputSlot << "\n";
                    pair<int, int> coord = stringToCoord(inputSlot);
                    setBarang(coord.first, coord.second, items)
                }
                cout << " berhasil disimpan dalam penyimpanan!\n\n";
            } catch (penyimpananPenuhException e) {
                cout << e.message();
            } catch (invalidPembelianxception e) {
                cout << e.message();
            } catch (uangTidakCukupException e) {
                cout << e.message();
            } catch (penyimpananPenuhException e) {
                cout << e.message();
            } 
        }

        void Sell() {
            try {
                vector<string> slotJual;
                cout << "Berikut merupakan penyimpanan Anda\n";
                pelaku->cetakPenyimpanan();
                
                cout << "\n\nSilahkan pilih petak yang ingin Anda jual!\n";
                cout << "Ketik -1 apabila sudah cukup"

                int i = 1;
                bool terimaInput = true;
                do {
                    string inputJual;
                    cout << i << "  ";
                    // validasi input
                    cin >> inputJual;
                    if(inputJual == -1){
                        terimaInput = false;
                    } else {
                        slotJual.push_back(inputJual);
                    }
                    cout << "\n";
                    i++;
                }while(terimaInput);

                for(int i = 0; i < slotJual.size(); i++) {
                    pair<int, int> coord = stringToCoord(slotJual[i]);
                    setKosong(coord.first, coord.second);
                }

                cout << "Barang Anda berhasil dijual! Uang Anda bertambah " << << " gulden!";

            } catch () {

            }
        }

        void pilihSlot() {
            cout << "Slot penyimpanan tersedia: " << pelaku.getSisaSlot() << "\n";
            if(pelaku.getSisaSlot() == 0) {
                throw penyimpananPenuhException();
            }
        }

        void pilihBarang(int pilihan) {
            if(pelaku->getPeran() == "Walikota" && isBangunan(this->items[i-1].first)) {
                throw invalidPembelianxception();
            }
        }

        void beliBarang(int kuantitas, int pilihanBarang) {

        }

        vector<pair<TradeObject, int>> getItems() {
            return this->items;
        }
};