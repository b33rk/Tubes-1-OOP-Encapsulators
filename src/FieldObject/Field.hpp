#include "../GameObject/gameObject.hpp"

class Field {
    private:
        int row;
        int col;
        int static jumlahIsi;
        TradeObject** barang;
    public:
        Field(){
            this->row = 0;
            this->col = 0;
        }
        Field(int row, int col) {
            this->row = row;
            this->col = col;
        }
        void cetak(){
            cout << "    ================[ Penyimpanan ]==================" << endl;
            cout << "   A     B     C     D     E     F     G     H   " << endl;
            cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
            for (int i = 0; i < row; i++){
                cout << " 0" << i << " |";
                for (int j = 0; j < col; j++){
                    barang[i][j].cetakBarang();
                }
                cout << endl;
                cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
            }
            cout << "Total slot kosong: " << row*col - jumlahIsi << endl;
        }
        int getJumlahIsi(){
            return jumlahIsi;
        }

        TradeObject** getBarang(){
            return this->barang;
        }

};

// class ladang: Field {
// };

// class lahan: Field {
// };