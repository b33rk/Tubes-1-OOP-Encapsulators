#include "../GameObject/GameObject.hpp"
#include <vector>
#include <bits/stdc++.h>

class Field {
    private:
        int row;
        int col;
        int static jumlahIsi;
        string tipe;
        TradeObject** barang;
    public:
        Field(int row, int col) {
            this->row = row;
            this->col = col;
            for (int i = 0; i < row; i++){
                for (int j = 0; j < col; j++) {
                    // barang[i][j].setNama("kosong");
                    barang[i][j].setKode("   ");
                }
            }
        }
        void virtual cetak(){
            cout << "     ================[ " << tipe << "]=================" << endl;
            cout << "   ";
            for (int i = 0; i < col; i++){
                cout << (char)(i + 40) << "     ";
            }
            cout << endl;
            cout << "    +";
            for (int i = 0; i < col; i++){
                cout << "-----+";
            }
            cout << endl;
            for (int i = 0; i < row; i++){
                cout << " 0" << i << " |";
                for (int j = 0; j < col; j++){
                    barang[i][j].cetakBarang();
                }
                cout << endl;
                cout << "    +";
                for (int i = 0; i < col; i++){
                    cout << "-----+";
                }
                cout << endl;
            }
        }
        int getJumlahIsi(){
            return jumlahIsi;
        }
        int getrow(){
            return row;
        }
        int getcol(){
            return col;
        }
        vector<TradeObject> getUniqueValue() {
            vector<TradeObject> listBarang;
            for (int i = 0; i < row; i++){
                for (int j = 0; j < col; j++) {
                    if (barang[i][j].getKode() != "   " && 
                        find(listBarang.begin(), listBarang.end(), barang[i][j]) == listBarang.end()) {
                        listBarang.push_back(barang[i][j]);
                    }
                }
            }
            
        }
};

class cultivateField: public Field {
    public:
        void cetak() {
            Field::cetak();
            vector<TradeObject> listUnik = getUniqueValue();
            for (TradeObject elmt : listUnik) {
                cout << " - " << elmt.getKode() << ": " << elmt.getNama() << endl;
            }
        }
};

class penyimpanan: public Field {
    public:
        void cetak() {
            Field::cetak();
            cout << "Total slot kosong: " << getrow()*getcol() - getJumlahIsi() << endl;
        }
};

// class peternakan: public Field {
//     public:
//         void cetak() {
//             cout << "     ================[ Peternakan ]===================" << endl;
//             Field::cetak();
//         }