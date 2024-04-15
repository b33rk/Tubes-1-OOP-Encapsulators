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

public:
    Field()
    {
        this->row = 0;
        this->col = 0;
        this->jumlahIsi = 0;
        this->tipe = "   ";
        this->initBarang();
    }
    Field(int row, int col, string tipe)
    {
        this->row = row;
        this->col = col;
        this->jumlahIsi = 0;
        this->tipe = tipe;
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
    }
    void virtual cetak()
    {
        int totalLebar = col * 6 + 4;
        string judul = "[" + tipe + "]";
        int panjangJudul = judul.length();
        int banyakSamaDengan = (totalLebar - panjangJudul) / 2;
        string barJudul = string(banyakSamaDengan, '=') + judul + string(banyakSamaDengan, '=');

        if (panjangJudul % 2 != totalLebar % 2)
        {
            barJudul += "=";
        }

        cout << barJudul << endl;
        cout << "       ";
        for (int i = 0; i < col; i++)
        {
            cout << (char)(i + 65) << "     ";
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
            if (i < 9)
            {
                cout << " 0" << (i + 1) << " |";
            }
            else
            {
                cout << " " << (i + 1) << " |";
            }
            for (int j = 0; j < col; j++)
            {
                storage[i][j]->cetakBarang();
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
        if (this->storage[row][col]->getKodeHuruf() != "   ")
        {
            throw petakTidakKosongException();
        }
        delete this->storage[row][col];
        this->storage[row][col] = object;
        if (object->getKodeHuruf() != "   ")
        {
            this->jumlahIsi++;
        }
    }

    vector<vector<T *>> getStorage()
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
    vector<TradeObject *> getUniqueValue()
    {
        vector<TradeObject *> listBarang;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (storage[i][j]->getKodeHuruf() != "   ")
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
                    hasil[inc].first.first = i;
                    hasil[inc].first.second = j;
                    hasil[inc].second.first = storage[i][j]->getNamaGameObject();
                    hasil[inc].second.second = storage[i][j]->getCurrentBerat();
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
        vector<TradeObject *> listUnik = getUniqueValue();
        for (TradeObject *elmt : listUnik)
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