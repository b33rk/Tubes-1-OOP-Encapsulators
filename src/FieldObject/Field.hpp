#ifndef FIELD_HPP
#define FIELD_HPP

#include "../GameObject/GameObject.hpp"
#include "../Exception/Exception.hpp"

template <class T>
class Field
{
private:
    int row;
    int col;
    int jumlahIsi;
    string tipe;
    vector<vector<T *>> storage;
    vector<T> memory;

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

    Field &operator=(const Field &origin)
    {
        this->row = origin.row;
        this->col = origin.col;
        this->jumlahIsi = origin.jumlahIsi;
        this->initBarang();
        for (int i = 0; i < this->row; i++)
        {
            for (int j = 0; j < this->col; j++)
            {
                delete this->storage[i][j];
                this->storage[i][j] = origin.storage[i][j];
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
                this->storage[i][j] = new T;
            }
        }
        //cout << "PRINT" << endl;
        /*
        for(int i = 0; i < this->row; ++i){
            for(int j = 0; j < this->col; ++j){
                cout << this->storage[i][j]->getKodeHuruf() << endl;
            }
        }*/
    }
    void virtual cetak(bool cetak_warna = false)
    {
        cout << "     ================[ " << tipe << "]=================" << endl;
        cout << "   ";
        for (int i = 0; i < col; i++)
        {
            cout << (char)(i + 40) << "     ";
        }
        cout << endl;
        cout << "    +";
        for (int i = 0; i < col; i++)
        {
            cout << "-----+";
        }
        cout << endl;
        for (int i = 0; i < row; i++)
        {
            cout << " 0" << i << " |";
            for (int j = 0; j < col; j++)
            {
                storage[i][j]->cetakBarang(cetak_warna);
            }
            cout << endl;
            cout << "    +";
            for (int i = 0; i < col; i++)
            {
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
        //cout << "SAMPAI BARANG" << endl;
        //cout << this->storage[0].size() << endl;
        //cout << this->storage[0][0]->getKodeHuruf() << endl;
        if (this->storage[row][col]->getKodeHuruf() != "   ")
        {
            throw BarangKosongException();
        }
        //cout << "SIAP2 DELTE" << endl;
        delete this->storage[row][col];
        //cout << "SELESAI EDE" << endl;
        this->storage[row][col] = object;
        if (object->getKodeHuruf() != "   ")
        {
            this->jumlahIsi++;
        }
    }

    vector<vector<T*>> getStorage()
    {
        return this->storage;
    }

    void insertFirst(T *object)
    {
        for (int i = 0; i < this->row; i++)
        {
            for (int j = 0; j < this->col; j++)
            {
                if (this->storage[i][j]->getKodeHuruf() == "   ")
                {
                    this->setBarang(i, j, object);
                    return;
                }
            }
        }
        throw penyimpananPenuhException();
    }
    vector<TradeObject*> getUniqueValue()
    {
        vector<TradeObject*> listBarang;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (storage[i][j]->getKodeHuruf() != "   " 
                    )
                {
                    listBarang.push_back(storage[i][j]);
                }
            }
        }
        return listBarang;
    }

    vector<string> getAllNamaBarang()
    {
        vector<string> namaBarang;
        for (int i = 0; i < this->row; i++)
        {
            for (int j = 0; j < this->col; j++)
            {
                if (storage[i][j]->getKodeHuruf() != "   ")
                {
                    namaBarang.push_back(storage[i][j]->getNamaGameObject());
                }
            }
        }
        return namaBarang;
    }

    vector<pair<pair<int, int>, pair<string, int>>> getAllPosisiNamaBerat()
    {
        vector<pair<pair<int, int>, pair<string, int>>> hasil;
        int inc = 0;
        for (int i = 0; i < this->row; i++)
        {
            for (int j = 0; j < this->col; j++)
            {
                if (storage[i][j]->getKodeHuruf() != "   ")
                {
                    hasil.push_back(make_pair(make_pair(i, j), make_pair(storage[i][j]->getNamaGameObject(), storage[i][j]->getCurrentBerat())));
                }
            }
        }
        return hasil;
    }
};

class cultivateField : public Field<CultivatedObject>
{
public:
    void cetak()
    {
        Field::cetak();
        vector<TradeObject*> listUnik = getUniqueValue();
        for (TradeObject* elmt : listUnik)
        {
            cout << " - " << elmt->getKodeHuruf() << ": " << elmt->getNama() << endl;
        }
    }
};

class penyimpanan : public Field<TradeObject>
{
public:
    void cetak()
    {
        Field::cetak();
        cout << "Total slot kosong: " << getRow() * getCol() - getJumlahIsi() << endl;
    }
};

#endif