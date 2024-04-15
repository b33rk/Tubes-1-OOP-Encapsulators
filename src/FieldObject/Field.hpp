#ifndef FIELD_HPP
#define FIELD_HPP

#include "../GameObject/GameObject.hpp"

template <class T>
class Field
{
private:
    int row;
    int col;
    int static jumlahIsi;
    string tipe;
    vector<vector<T *>> storage;

public:
    Field()
    {
        this->row = 0;
        this->col = 0;
        this->jumlahIsi = 0;
        this->initBarang();
    }
    Field(int row, int col)
    {
        this->row = row;
        this->col = col;
        this->jumlahIsi = 0;
        this->initBarang();
    }

    Field& operator=(const Field& origin){
        this->row = origin.row;
        this->col = origin.col;
        this->jumlahIsi = origin.jumlahIsi;
        this->initBarang();
        for (int i = 0 ; i < this->row ; i++){
            for (int j = 0 ; j < this->col ; j++){
                delete this->storage[i][j];
                this->storage[i][j] = origin[i][j]
            }
        }
        return *this;
        
    }

    void initBarang()
    {
        this->storage.resize(this->row); // make outer vector row size
        for (int i = 0; i < this->row; i++)
        {
            this->storage[i].resize(this->col); // make inner vector col size;
            for (int j = 0; j < this->col; j++)
            {
                this->storage[i][j] = new T();
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
    int getJumlahIsi()
    {
        return jumlahIsi;
    }

    T *getBarang(int row, int col)
    {
        return this->storage[row][col];
    }

    int getRow()
    {
        return this->row;
    }

    int getCol()
    {
        return this->col;
    }

    void incrementJumlahIsi()
    {
        this->jumlahIsi++;
    }

    void setBarang(int row, int col, T *object)
    {
        if (this->storage[row][col].getKodeHuruf() != "   ")
        {
            throw BarangKosongException();
        }
        delete this->storage[row][col];
        this->storage[row][col] = object;
    }

    vector<vector<T *>> getStorage()
    {
        return this->storage;
    }

    void insertFirst(T* object){
        for (int i = 0 ; i < this->row ; i++){
            for (int j = 0 ; j < this->col ; j++){
                if (this->storage[i][j].getKodeHuruf() == "   "){
                    this->setBarang(i,j,object);
                    return;
                }
            }

        }
        throw  penyimpananPenuhException();
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
    
    vector<string> getAllNamaBarang(){
        return {};
    }
};

class cultivateField: public Field<CultivatedObject> {
    public:
        void cetak() {
            Field::cetak();
            vector<TradeObject> listUnik = getUniqueValue();
            for (TradeObject elmt : listUnik) {
                cout << " - " << elmt.getKodeHuruf() << ": " << elmt.getNama() << endl;
            }
        }
};

class penyimpanan: public Field<TradeObject> {
    public:
        void cetak() {
            Field::cetak();
            cout << "Total slot kosong: " << getRow()*getCol() - getJumlahIsi() << endl;
        }
};

#endif