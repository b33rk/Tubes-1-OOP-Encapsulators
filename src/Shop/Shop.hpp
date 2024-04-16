#include "../Player/Player.hpp"
#include "../Exception/Exception.hpp"
#include "../GameObject/GameObject.hpp"
#include <vector>

class Shop {
    private:
        int numOfItems; // jumlah barang di toko
        Player* pelaku; // peran(walikota, petani, peternak)
        vector<pair<TradeObject, int>> items;    // item yang ada (nama barang, jumlah)
        
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
                items.push_back({ vectorInit[i].first, vectorInit[i].second });
            }
        }

        void setPelaku(Player* newPelaku) {
            this->pelaku = newPelaku;
        }

        void displayShop() {
            if(this->numOfItems != 0) {
                cout << "Berikut merupakan hal yang dapat Anda Beli\n";
                for(int i = 0; i < this->numOfItems; i++) {
                    cout << i + 1 << "  " << this->items[i].first.getNama() << " - " << this->items[i].first.getPrice();
                    if(this->items[i].second >= 0) {
                        cout << " berjumlah : " << this->items[i].second << "\n";
                    }
                }
            } else {
                throw itemTokoKosongException();
            }
        }
        
        void Buy() {
            // validasi peran, uang, slot
            cout << "Selamat datang di toko!!\n";

            try {
                displayShop();

                int pilihanBarang, kuantitas;

                cout << "\nUang Anda : " << pelaku->getUang() << "\n";
                pilihSlot();
 
                cout << "\nBarang ingin dibeli : " << pilihanBarang << "\n";
                pilihBarang(pilihanBarang);

                cout << "Kuantitas : " << kuantitas << "\n";
                beliBarang(kuantitas, pilihanBarang);

                cout << "\nSelamat Anda behasil membeli " << kuantitas << this->items[pilihanBarang-1].first.getNama();
                cout << ". Uang Anda tersisa" << pelaku->getUang() << " gulden.\n";
                // display penyimpanan
                cout << "Pilih slot untuk menyimpan barang yang Anda beli!\n";
                pelaku->cetakPenyimpanan();

                cout << "\n\nPilih petak slot yang ingin diisi : \n";
                for(int i = 0; i < kuantitas; i++) {
                    string inputSlot;
                    cout << i+1 << ".   " << inputSlot << "\n";
                    pair<int, int> coord = stringToCoord(inputSlot);

                    // validasi
                    if((coord.first >= 0 && coord.first < pelaku->getPenyimpananField().getRow()) && (coord.second >= 0  && coord.second < pelaku->getPenyimpananField().getCol())) {
                        TradeObject * object = new TradeObject(items[pilihanBarang - 1].first);
                        pelaku->setBarangPenyimpanan(coord.first, coord.second, object);
                    } else {
                        throw invalidPetak();
                        cout << "Pembelian gagal!\n";
                    }
                }
                cout << items[pilihanBarang - 1].first.getNamaGameObject() << " berhasil disimpan dalam penyimpanan!\n\n";
            } catch (itemTokoKosongException e) {
                cout << e.message();
            } catch (penyimpananPenuhException e) {
                cout << e.message();
            } catch (invalidPembelianException e) {
                cout << e.message();
            } catch (pembelianMelebihiStokException e) {
                cout << e.message();
            } catch (uangTidakCukupException e) {
                cout << e.message();
            } catch (invalidPetak e) {
                cout << e.message();
            } catch (...) {
                cout << "Terjadi kesalahan saat pembelian\n";
            }
        }

        void pilihSlot() {
            cout << "Slot penyimpanan tersedia: " << pelaku->getPenyimpananField().getSisa() << "\n";
            if(pelaku->getPenyimpananField().getSisa() <= 0) {
                throw penyimpananPenuhException();
            }
        }

        void pilihBarang(int pilihan) {
            if(pilihan <= 0 && pilihan >this->items.size()) {
                throw pembelianLuarItemException();
            }
            if(pelaku->getPeran() == "Walikota" && isBangunan(this->items[pilihan-1].first.getNama())) {
                throw invalidPembelianException();
            }
        }

        void beliBarang(int kuantitas, int pilihan) {
            if(isBangunan(this->items[pilihan-1].first.getNama()) && kuantitas > this->items[pilihan-1].second) {
                throw pembelianMelebihiStokException();
            }
        }

        void Sell() {
            try {
                vector<string> slotJual;
                if(pelaku->getPenyimpananField().getJumlahIsi() == 0) {
                    throw itemPenyimpananKosongException();
                }
                cout << "Berikut merupakan penyimpanan Anda\n";
                pelaku->cetakPenyimpanan();
                
                cout << "\n\nSilahkan pilih petak yang ingin Anda jual!\n";
                cout << "Ketik -1 apabila sudah cukup\n";

                int j = 1;
                bool terimaInput = true;
                do {
                    string inputJual;
                    cout << j << ".  ";
                    // validasi input
                    cin >> inputJual;
                    if(inputJual == "-1"){
                        terimaInput = false;
                    } else {
                        slotJual.push_back(inputJual);
                    }
                    j++;
                }while(terimaInput);

                int tempPrice;

                for(int i = 0; i < slotJual.size(); i++) {
                    pair<int, int> coord = stringToCoord(slotJual[i]);

                    if((coord.first >= 0 && coord.first < pelaku->getPenyimpananField().getRow()) && (coord.second >= 0  && coord.second < pelaku->getPenyimpananField().getCol())) {
                        tempPrice = pelaku->getBarangPenyimpananPrice(coord.first, coord.second);
                        pelaku->setBarangPenyimpananKosong(coord.first, coord.second);
                        pelaku->setUang(pelaku->getUang() + tempPrice);
                    } else {
                        throw invalidPetak();
                        cout << "Penjualan gagal!\n";
                    }
                }
                cout << "Barang Anda berhasil dijual! Uang Anda bertambah " << tempPrice << " gulden!";

            } catch (itemPenyimpananKosongException e) {
                cout << e.message();
            } catch (invalidPetak e) {
                cout << e.message();
            } catch (...) {
                cout << "Terjadi kesalahan saat penjualan\n";
            }
        }

        vector<pair<TradeObject, int>> getItems() {
            return this->items;
        }
};
