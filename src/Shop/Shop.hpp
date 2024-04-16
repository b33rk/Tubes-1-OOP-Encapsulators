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
            const char *neonGreen = "\033[1;32m";
            const char *reset = "\033[0m";
            if(this->numOfItems != 0) {
                cout << "Berikut merupakan hal yang dapat Anda Beli\n";
                for(int i = 0; i < this->numOfItems; i++) {
                    cout << i + 1 << "  ";
                    if(this->items[i].second == -1) {
                        cout << neonGreen << this->items[i].first.getNama() << reset;
                        cout << "\n   harga : " << this->items[i].first.getPrice() << "\n";
                    } else {
                        cout << neonGreen << this->items[i].first.getNama() << reset;
                        cout << "\n   harga : " << this->items[i].first.getPrice() << "\n   jumlah : " << this->items[i].second << "\n";
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
 
                cout << "\nNomor barang ingin dibeli : ";
                cin >> pilihanBarang;
                pilihBarang(pilihanBarang);
                if(this->items[pilihanBarang-1].second == 0) {
                    throw barangKosongException();
                }

                cout << "Kuantitas : ";
                cin >> kuantitas;
                if(isBangunan(this->items[pilihanBarang-1].first.getNama()) && kuantitas > this->items[pilihanBarang-1].second) {
                    throw pembelianMelebihiStokException();
                } else {
                    int totalPengeluaran = kuantitas * this->items[pilihanBarang-1].first.getPrice();

                    if(totalPengeluaran > pelaku->getUang()) {
                        throw uangTidakCukupException();
                    } else{
                        pelaku->setUang(pelaku->getUang() - totalPengeluaran);
                    }
                }

                cout << "\nSelamat Anda behasil membeli " << kuantitas << " "<<  this->items[pilihanBarang-1].first.getNama();
                cout << ". Uang Anda tersisa " << pelaku->getUang() << " gulden.\n";
                // display penyimpanan
                cout << "Pilih slot untuk menyimpan barang yang Anda beli!\n";
                pelaku->cetakPenyimpanan();

                cout << "\n\nPilih petak slot yang ingin diisi : \n";
                for(int i = 0; i < kuantitas; i++) {
                    string inputSlot;
                    cout << i+1 << ".   ";
                    cin >> inputSlot;
                    pair<int, int> coord = stringToCoord(inputSlot);

                    if((coord.first >= 0 && coord.first < pelaku->getPenyimpananField().getRow()) && (coord.second >= 0  && coord.second < pelaku->getPenyimpananField().getCol())) {
                        TradeObject * object = new TradeObject(items[pilihanBarang - 1].first);
                        pelaku->setBarangPenyimpanan(coord.first, coord.second, object);
                    } else {
                        throw invalidPetak();
                        cout << "Pembelian gagal!\n";
                    }
                }
                cout << items[pilihanBarang - 1].first.getNamaGameObject() << " berhasil disimpan dalam penyimpanan!\n\n";
                
                // ngurangi barang di toko
                if(items[pilihanBarang - 1].second >= 0) {
                    items[pilihanBarang - 1].second--;
                }


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
            } catch (barangKosongException e) {
                cout << e.message();
            } catch (pembelianLuarItemException e) {
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
            if(pilihan <= 0 && pilihan > this->items.size()) {
                throw pembelianLuarItemException();
            }
            if(pelaku->getPeran() == "Walikota" && isBangunan(this->items[pilihan-1].first.getNama())) {
                throw invalidPembelianException();
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

                int tempPrice, totalPenjualan = 0;

                for(int i = 0; i < slotJual.size(); i++) {
                    pair<int, int> coord = stringToCoord(slotJual[i]);

                    if((coord.first >= 0 && coord.first < pelaku->getPenyimpananField().getRow()) && (coord.second >= 0  && coord.second < pelaku->getPenyimpananField().getCol())) {
                        bool masukToko = true;
                        vector<vector<TradeObject *>> temp = pelaku->getPenyimpanan();

                        if(temp[coord.first][coord.second]->getType() == "BANGUNAN" && (pelaku->getPeran() != "Walikota")) {
                            throw invalidPenjualanException();
                        }

                        // yang dijual bangunan
                        if(isBangunan(temp[coord.first][coord.second]->getNama())) {
                            for(int i= 0; i < items.size(); i++) {
                                if(this->items[i].first.getNama() == temp[coord.first][coord.second]->getNama()) {
                                    this->items[i].second++;
                                    masukToko = false;
                                    break;
                                }
                            }

                            if(masukToko) {
                                this->items.push_back({*temp[coord.first][coord.second], 1});
                            }
                        } else {
                            for(int i= 0; i < items.size(); i++) {
                                if(this->items[i].first.getNama() == temp[coord.first][coord.second]->getNama()) {
                                    masukToko = false;
                                    break;
                                }
                            }

                            if(masukToko) {
                                this->items.push_back({*temp[coord.first][coord.second], -1});
                            }
                        }

                        tempPrice = pelaku->getBarangPenyimpananPrice(coord.first, coord.second);
                        totalPenjualan += tempPrice;
                        pelaku->setBarangPenyimpananKosong(coord.first, coord.second);
                        pelaku->setUang(pelaku->getUang() + tempPrice);
                    } else {
                        throw invalidPetak();
                        cout << "Penjualan gagal!\n";
                    }
                }
                cout << "Barang Anda berhasil dijual! Uang Anda bertambah " << totalPenjualan << " gulden!";

            } catch (itemPenyimpananKosongException e) {
                cout << e.message();
            } catch (invalidPetak e) {
                cout << e.message();
            } catch (invalidPenjualanException e) {
                cout << e.message();
            } catch (...) {
                cout << "Terjadi kesalahan saat penjualan\n";
            }
        }

        vector<pair<TradeObject, int>> getItems() {
            return this->items;
        }
};
