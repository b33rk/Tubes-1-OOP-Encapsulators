#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP
#include <exception>
#include <stdexcept>
#include <string>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

class MakananSalahException : public exception
{
public:
    const char *message()
    {
        return "Makanan tidak dapat dimakan oleh hewan ini\n";
    }
    const char *what() const noexcept override
    {
        return "Makanan tidak dapat dimakan oleh hewan ini\n";
    }
};

class uangTidakCukupException : public exception
{
public:
    const char *message()
    {
        return "Uang tidak cukup!\n";
    }
    const char *what() const noexcept override
    {
        return "Uang tidak cukup!\n";
    }
};

class tambahPlayerInvalidException : public exception
{
public:
    const char *message()
    {
        return "Peran player tidak valid\n";
    }
    const char *what() const noexcept override
    {
        return "Peran player tidak valid\n";
    }
};

class invalidCommandException : public exception
{
public:
    const char *message()
    {
        return "COMMAND TIDAK VALID!!!\n";
    }
    const char *what() const noexcept override
    {
        return "COMMAND TIDAK VALID!!!\n";
    }
};

class petakTidakKosongException : public exception
{
public:
    const char *message()
    {
        return "Petak tersebut tidak kosong !\n";
    }
    const char *what() const noexcept override
    {
        return "Petak tersebut tidak kosong !\n";
    }
};

class penyimpananPenuhException : public exception
{
public:
    const char *message()
    {
        return "Penyimpanan sudah penuh\n";
    }
    const char *what() const noexcept override
    {
        return "Penyimpanan sudah penuh\n";
    }
    //     penyimpananPenuhException(  )
};

class BukanMakananException : public exception
{
public:
    const char *message()
    {
        return "Barang tersebut bukan makanan mass!!\n";
    }
    const char *what() const noexcept override
    {
        return "Barang tersebut bukan makanan mass!!\n";
    }
};

class BarangKosongException : public exception
{
public:
    const char *message()
    {
        return "Barang tersebut kosong mass!!\n";
    }
    const char *what() const noexcept override
    {
        return "Barang tersebut kosong mass!!\n";
    }
};

class PanenKosongException : public exception
{
public:
    const char *message()
    {
        return "Tidak ada barang yang bisa dipanen!\n";
    }
    const char *what() const noexcept override
    {
        return "Tidak ada barang yang bisa dipanen!\n";
    }
};

class KurangMaterialException : public exception
{
private:
    vector<string> materials;
    vector<int> quantity;
    string finalMessage;

public:
    KurangMaterialException()
    {
        this->finalMessage = "Kamu tidak punya sumber daya yang cukup! Masih memerlukan ";
    }
    KurangMaterialException(const vector<string> &materials, const vector<int> &quantity) : materials(materials), quantity(quantity), exception()
    {
        this->finalMessage = "Kamu tidak punya sumber daya yang cukup! Masih memerlukan ";
        int count = 0;
        for (int i = 0; i < materials.size(); i++)
        {
            if (quantity[i] > 0)
            {
                if (count >= 1)
                {
                    finalMessage.append(", ");
                }
                finalMessage.append(to_string(quantity[i]));
                finalMessage.append(" ");
                count++;
                finalMessage.append(materials[i]);
            }
        }
        finalMessage.append("\n");
    }
    const char *message()
    {
        return this->finalMessage.c_str();
    }
    const char *what() const noexcept override
    {
        return this->finalMessage.c_str();
    }
};
class invalidPembelianException : public exception
{
public:
    const char *message()
    {
        return "Pembelian barang tersebut tidak bisa Anda lakukan sebagai Walikota!!\n";
    }
    const char *what() const noexcept override
    {
        return "Pembelian barang tersebut tidak bisa Anda lakukan sebagai Walikota!!\n";
    }
};

class pembelianLuarItemException : public exception
{ 
public:
    const char *message()
    {
        return "Pembelian barang di luar daftar!!\n";
    }
const char *what() const noexcept override
    {
        return "Pembelian barang di luar daftar!!\n";
    }
};

class pembelianMelebihiStokException : public exception
{ 
public:
    const char *message()
    {
        return "Pembelian kuantitas barang melebihi stok!!\n";
    }
    const char *what() const noexcept override
    {
        return "Pembelian kuantitas barang melebihi stok!!\n";
    }
};

class itemTokoKosongException : public exception
{
    public:
        const char *message()
        {
            return "Tidak ada barang yang bisa Anda beli!\n";
        }
        const char *what() const noexcept override
        {
            return "Tidak ada barang yang bisa Anda beli!\n";
        }
};

class itemPenyimpananKosongException : public exception
{
    public:
        const char *message()
        {
            return "Tidak ada barang yang bisa Anda jual!\n";
        }
        const char *what() const noexcept override
        {
            return "Tidak ada barang yang bisa Anda jual!\n";
        }
};

class itemPenyimpananKosongMakanException : public exception
{
    public:
        const char *message()
        {
            return "Tidak ada barang yang bisa Anda makan! Anda tidak punya makanan yang bisa dimakan!\n";
        }
        const char *what() const noexcept override
        {
            return "Tidak ada barang yang bisa Anda makan!\n";
        }
};

class invalidPetak : public exception
{
    public:
        const char *message()
        {
            return "Pilihan petak di luar batas!\n";
        }
        const char *what() const noexcept override
        {
            return "Pilihan petak di luar batas!\n";
        }
};

class invalidPenjualanException : public exception
{
public:
    const char *message()
    {
        return "Penjualan barang tersebut tidak bisa Anda lakukan!!\n";
    }
    const char *what() const noexcept override
    {
        return "Penjualan barang tersebut tidak bisa Anda lakukan!!\n";
    }
};

#endif
