#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct item{
    string nama;
    string jenis;
    int level;
    int jumlah;
};

struct e_slot{
    bool kosong = true;
    item equipment;
};

struct player{
    string nama;
    e_slot slot[4];
    item inventory[3];
    int jumlahitem = 0;
};

const int MAX = 100;
item inventory[MAX];
int jumlahData = 0;

player p;
string namaFile = "inventory.txt";

string namaItemList[] = {"Sword", "Shield", "Potion", "Armor", "Ring"};
string jenisList[] = {"Weapon", "Defense", "Consumable"};

void generateRandom(){

}

//pengubah huruf kecil
string huruf_kecil(string kata){
    for(int i = 0; i < kata.length(); i++){
        kata[i] = tolower(kata[i]);
    }
    return kata;
}


void menu() {
    int pilih;

    do {
        cout << "\n===== INVENTORY GAME =====\n";
        cout << "1. Generate Random\n";
        cout << "2. Tampilkan Seluruh Item\n";
        cout << "3. Tampilkan Equio\n";
        cout << "4. Sorting Item\n";
        cout << "5. Searching\n";
        cout << "6. Equip Item\n";
        cout << "7. Save ke File\n";
        cout << "8. Load dari File\n";
        cout << "9. Ganti File\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> pilih;

        switch (pilih) {
            case 1: 
                generateRandom(); 
                break;
            case 2: 
                tampilItem(); 
                break;
            case 3: 
                sorting();
                break;
            case 4: 
                searchMenu(); 
                break;
            case 5: 
                saveToFile(); 
                break;
            case 6: 
                loadFromFile(); 
                break;
            case 7: 
                pointerDemo(); 
                break;
            case 0: cout << "Terima kasih!\n"; break;
            default: cout << "Pilihan salah!\n";
        }

    } while (pilih != 0);
}


int main() {
    menu();
    return 0;
}