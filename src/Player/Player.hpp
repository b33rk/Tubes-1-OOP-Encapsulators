#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../GameObject/GameObject.hpp"
#include "../FieldObject/Field.hpp"

class Player
{
protected:
    // int id;
    // int kekayaan;
    int berat;
    int uang;
    string nama;
    string peran;
    Field<TradeObject> penyimpanan;

public:
    Player();
    Player(string, string, int, int, int, int);
    //~Player();
    void virtual next() {}
    //void virtual muat();
    //void virtual jual(int, int);
    //void virtual beli(TradeObject *, int);
    void virtual makan(TradeObject *);
    void virtual cetakPenyimpanan();
    //void virtual cetakLahan();
    string getNama();
    string getPeran();
    int getUang();
    void setUang(int uangBaru);
    // void setKekayaan(int kekayaan);
    float persentasePajak(int KKP);
    int virtual bayarPajak();
    virtual void setBarangFirstPenyimpanan(TradeObject *);
    virtual void setBarangFirstLahan(CultivatedObject *);
    virtual void setBarangPenyimpanan(int, int, TradeObject *);
    virtual void setBarangLahan(int, int, CultivatedObject *);
    int getBerat();
    void setBerat(int);
    virtual vector<pair<pair<int, int>, pair<string, int>>> getAllPosisiNamaBerat();
    vector<string> getAllNamaBarang();
    virtual Field<CultivatedObject> getLahan();
    vector<vector<TradeObject*>> getPenyimpanan();
    void setBarangPenyimpananKosong(int, int);
    int getBarangPenyimpananPrice(int, int);
};

#endif