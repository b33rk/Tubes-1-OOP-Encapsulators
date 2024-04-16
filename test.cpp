#include <iostream>

int main() {
    char input;

    // Meminta input dari pengguna
    std::cout << "Masukkan karakter (-1 untuk keluar): ";

    // Loop terus menerus hingga input -1 diberikan
    while ((input = std::cin.get()) != -1) {
        // Lakukan sesuatu dengan input
        std::cout << "Karakter yang dimasukkan adalah: " << input << std::endl;

        // Hapus karakter newline dari input buffer
        std::cin.ignore();
        
        // Meminta input lagi
        std::cout << "Masukkan karakter (-1 untuk keluar): ";
    }

    std::cout << "Program selesai." << std::endl;

    return 0;
}
