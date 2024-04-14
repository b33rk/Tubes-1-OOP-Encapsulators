#include "../GameObject/gameObject.hpp"

template<class T>
class Field {
    private:
        int row;
        int col;
        int static jumlahIsi;
        vector<vector<T*>> barang;
    public:
        Field(){
            this->row = 0;
            this->col = 0;
            this->jumlahIsi = 0;
            this->initBarang();
        }
        Field(int row, int col) {
            this->row = row;
            this->col = col;
            this->jumlahIsi = 0;
            this->initBarang();

        }

        void initBarang(){
            this->barang.resize(this->row);// make outer vector row size
            for (int i = 0 ; i < this->row ; i++){
                this->barang[i].resize(this->col); // make inner vector col size;
                for (int j = 0 ; j < this->col ; j++ ){
                    this->barang[i][j] = new T(); 
                }
            }
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

        vector<vector<T*>> getBarang(){
            return this->barang;
        }

        int getRow(){
            return this->row;
        }

        int getCol(){
            return this->col;
        }

        void incrementJumlahIsi(){
            this->jumlahIsi++;
        }

        void setBarang(int row, int col, T* object){
            delete this->barang[row][col];
            this->barang[row][col] = object;
        }

        

};

// class ladang: Field {
// };

// class lahan: Field {
// };