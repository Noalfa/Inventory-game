#include <iostream>   // input output
#include <fstream>    // file handling
#include <cstdlib>    // rand()
#include <ctime>      // time()

using namespace std;

// ================= STRUCT =================

struct item{
    string nama;   // nama item
    string tipe;   // Equipment / Potion
    string grade;  // grade item
    int level;     // level item
};

struct e_slot{
    bool kosong = true; // slot kosong atau tidak
    item equipment;     // item yang dipasang
};

struct player{
    string nama;         // nama player
    e_slot slot[4];      // 4 slot equipment
    item inventory[10];  // max 10 item
    int jumlahitem = 0;  // jumlah item
};

// ================= GLOBAL =================

player p; // data player
string namaFile = "inventory.txt"; // file aktif

// list random
string namaItemList[] = {"Sword", "Armor", "Ring"};
string potionList[] = {"Healing Potion", "Boost Potion"};
string gradeList[] = {"Copper", "Silver", "Diamond"};

// ================= TAMBAH ITEM =================

void tambahItem() {
    if (p.jumlahitem >= 10) { // cek penuh
        cout << "Inventory penuh!\n";
        return;
    }

    item baru;
    int pilih;

    cout << "\n=== TAMBAH ITEM ===\n";
    cout << "1. Equipment\n";
    cout << "2. Potion\n";
    cout << "Pilih tipe: ";
    cin >> pilih;
    cin.ignore(); // buang newline

    if (pilih == 1) {
        baru.tipe = "Equipment";

        cout << "Nama item: ";
        getline(cin, baru.nama);

        cout << "Grade (Copper/Silver/Diamond): ";
        getline(cin, baru.grade);
    }
    else if (pilih == 2) {
        baru.tipe = "Potion";

        cout << "Nama potion (Healing Potion / Boost Potion): ";
        getline(cin, baru.nama);

        baru.grade = "-"; // potion tidak pakai grade
    }
    else {
        cout << "Pilihan tidak valid!\n";
        return;
    }

    cout << "Level: ";
    cin >> baru.level;

    p.inventory[p.jumlahitem] = baru; // simpan
    p.jumlahitem++;

    cout << "Item berhasil ditambahkan!\n";
}

// ================= RANDOM =================

void generateRandom() {
    int n;
    cout << "Jumlah item: ";
    cin >> n;

    if (n > 10) n = 10; // batas max

    srand(time(0)); // seed random

    p.jumlahitem = n;

    for (int i = 0; i < n; i++) {

        int tipeRand = rand() % 2; // 0 atau 1

        if (tipeRand == 0) {
            // equipment
            p.inventory[i].tipe = "Equipment";
            p.inventory[i].nama = namaItemList[rand() % 3];
            p.inventory[i].grade = gradeList[rand() % 3];
        } else {
            // potion
            p.inventory[i].tipe = "Potion";
            p.inventory[i].nama = potionList[rand() % 2];
            p.inventory[i].grade = "-";
        }

        p.inventory[i].level = rand() % 10 + 1; // level 1-10
    }

    cout << "Random item dibuat!\n";
}

// ================= TAMPIL =================

void tampilItem(){
    if (p.jumlahitem == 0) {
        cout << "Inventory kosong!\n";
        return;
    }

    cout << "\n=== INVENTORY ===\n";
    for (int i = 0; i < p.jumlahitem; i++) {
        cout << i + 1 << ". ";
        cout << p.inventory[i].nama << " | ";
        cout << p.inventory[i].tipe << " | ";
        cout << p.inventory[i].grade << " | Lv.";
        cout << p.inventory[i].level << "\n";
    }
}

// ================= EQUIPMENT =================

void equipment(){
    cout << "\n=== EQUIPMENT ===\n";
    for (int i = 0; i < 4; i++) {
        cout << i + 1 << ". ";
        if (p.slot[i].kosong){
            cout << "Kosong\n";
        }else{
            cout << p.slot[i].equipment.nama;
            cout << " (Lv." << p.slot[i].equipment.level << ")\n";
        }
    }
}

// ================= LOWERCASE =================

string huruf_kecil(string kata){
    for(int i = 0; i < kata.length(); i++){
        kata[i] = tolower(kata[i]); // ubah ke huruf kecil
    }
    return kata;
}

// ================= SWAP =================

void swapItem(item &a, item &b) {
    item temp = a;
    a = b;
    b = temp;
}

// ================= QUICK SORT =================

int partitionNama(item arr[], int low, int high) {
    string pivot = huruf_kecil(arr[high].nama);
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (huruf_kecil(arr[j].nama) < pivot) {
            i++;
            swapItem(arr[i], arr[j]);
        }
    }

    swapItem(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSortNama(item arr[], int low, int high) {
    if (low < high) {
        int pi = partitionNama(arr, low, high);

        quickSortNama(arr, low, pi - 1);
        quickSortNama(arr, pi + 1, high);
    }
}

// ================= QUICK SORT LEVEL =================

int partitionLevel(item arr[], int low, int high) {
    int pivot = arr[high].level;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j].level < pivot) {
            i++;
            swapItem(arr[i], arr[j]);
        }
    }

    swapItem(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSortLevel(item arr[], int low, int high) {
    if (low < high) {
        int pi = partitionLevel(arr, low, high);

        quickSortLevel(arr, low, pi - 1);
        quickSortLevel(arr, pi + 1, high);
    }
}

// ================= SORTING =================

void sorting() {
    if (p.jumlahitem == 0) {
        cout << "Inventory kosong!\n";
        return;
    }

    int pilih;
    cout << "\n--- SORTING (QUICK SORT) ---\n";
    cout << "1. Berdasarkan Nama\n";
    cout << "2. Berdasarkan Level\n";
    cout << "Pilih: ";
    cin >> pilih;

    if (pilih == 1) {
        quickSortNama(p.inventory, 0, p.jumlahitem - 1);
    } else if (pilih == 2) {
        quickSortLevel(p.inventory, 0, p.jumlahitem - 1);
    } else {
        cout << "Pilihan tidak valid!\n";
        return;
    }

    cout << "Sorting selesai (Quick Sort)!\n";
}

// ================= BINARY SEARCH =================

int binarySearchNama(item arr[], int jumlah, string target) {

    int kiri = 0;
    int kanan = jumlah - 1;

    target = huruf_kecil(target);

    while (kiri <= kanan) {

        int tengah = (kiri + kanan) / 2;

        string namaTengah = huruf_kecil(arr[tengah].nama);

        if (namaTengah == target)
            return tengah;

        if (namaTengah < target)
            kiri = tengah + 1;
        else
            kanan = tengah - 1;
    }

    return -1;
}

int binarySearchLevel(item arr[], int jumlah, int target) {

    int kiri = 0;
    int kanan = jumlah - 1;

    while (kiri <= kanan) {

        int tengah = (kiri + kanan) / 2;

        if (arr[tengah].level == target)
            return tengah;

        if (arr[tengah].level < target)
            kiri = tengah + 1;
        else
            kanan = tengah - 1;
    }

    return -1;
}

// ================= SEARCHING =================

void searching() {

    if (p.jumlahitem == 0) {
        cout << "Inventory kosong!\n";
        return;
    }

    item temp[10];

    for (int i = 0; i < p.jumlahitem; i++) {
        temp[i] = p.inventory[i];
    }

    int pilih;

    cout << "\n=== SEARCHING ===\n";
    cout << "1. Cari Nama\n";
    cout << "2. Cari Level\n";
    cout << "Pilih: ";
    cin >> pilih;
    cin.ignore();

    if (pilih == 1) {

        quickSortNama(temp, 0, p.jumlahitem - 1);

        string target;

        cout << "Masukkan nama item: ";
        getline(cin, target);

        int hasil = binarySearchNama(temp, p.jumlahitem, target);

        if (hasil == -1) {
            cout << "Item tidak ditemukan!\n";
        } else {
            cout << "\nItem ditemukan:\n";

            int kiri = hasil;

            while (kiri >= 0 && huruf_kecil(temp[kiri].nama) == huruf_kecil(target)) {
                kiri--;
            }
            kiri++;

            while (kiri < p.jumlahitem && huruf_kecil(temp[kiri].nama) == huruf_kecil(target)) {

                cout << temp[kiri].nama << " | ";
                cout << temp[kiri].tipe << " | ";
                cout << temp[kiri].grade << " | Lv.";
                cout << temp[kiri].level << endl;

                kiri++;
            }
        }

    }
    else if (pilih == 2) {

        quickSortLevel(temp, 0, p.jumlahitem - 1);

        int level;

        cout << "Masukkan level: ";
        cin >> level;

        int hasil = binarySearchLevel(temp, p.jumlahitem, level);

        if (hasil == -1) {
            cout << "Item tidak ditemukan!\n";
        } else {

            cout << "\nItem dengan level tersebut:\n";

            int kiri = hasil;

            while (kiri >= 0 && temp[kiri].level == level)
                kiri--;

            kiri++;

            while (kiri < p.jumlahitem && temp[kiri].level == level) {

                cout << temp[kiri].nama << " | ";
                cout << temp[kiri].tipe << " | ";
                cout << temp[kiri].grade << " | Lv.";
                cout << temp[kiri].level << endl;

                kiri++;
            }
        }

    }
    else {
        cout << "Pilihan tidak valid!\n";
    }
}

// ================= EQUIP ITEM =================

void equipItem() {

    if (p.jumlahitem == 0) {
        cout << "Inventory kosong!\n";
        return;
    }

    tampilItem();

    int index;

    cout << "\nPilih nomor item yang ingin di-equip: ";
    cin >> index;

    index--;

    if (index < 0 || index >= p.jumlahitem) {
        cout << "Item tidak valid!\n";
        return;
    }

    if (p.inventory[index].tipe != "Equipment") {
        cout << "Potion tidak bisa di-equip!\n";
        return;
    }

    for (int i = 0; i < 4; i++) {
        if (!p.slot[i].kosong &&
            p.slot[i].equipment.nama == p.inventory[index].nama &&
            p.slot[i].equipment.level == p.inventory[index].level) {

            cout << "Item sudah terpasang!\n";
            return;
        }
    }

    equipment();

    int slot;

    cout << "Pilih slot (1-4): ";
    cin >> slot;

    slot--;

    if (slot < 0 || slot >= 4) {
        cout << "Slot tidak valid!\n";
        return;
    }

    p.slot[slot].equipment = p.inventory[index];
    p.slot[slot].kosong = false;

    for (int i = index; i < p.jumlahitem - 1; i++) {
        p.inventory[i] = p.inventory[i + 1]; // geser
    }
    p.jumlahitem--;

    cout << "Equipment berhasil dipasang!\n";
}

// ================= FILE =================

void saveFile() {

    ofstream file(namaFile); // buka file tulis

    if (!file) {
        cout << "Gagal membuka file!\n";
        return;
    }

    file << p.jumlahitem << endl; // simpan jumlah item

    for (int i = 0; i < p.jumlahitem; i++) {
        file << p.inventory[i].nama << "|";
        file << p.inventory[i].tipe << "|";
        file << p.inventory[i].grade << "|";
        file << p.inventory[i].level << endl;
    }

    for (int i = 0; i < 4; i++) {
        file << p.slot[i].kosong << "|";

        if (!p.slot[i].kosong) {
            file << p.slot[i].equipment.nama << "|";
            file << p.slot[i].equipment.tipe << "|";
            file << p.slot[i].equipment.grade << "|";
            file << p.slot[i].equipment.level;
        }

        file << endl;
    }

    file.close();

    cout << "Data berhasil disimpan ke " << namaFile << endl;
}

// ================= LOAD =================

void loadFile() {

    ifstream file(namaFile);

    if (!file) {
        cout << "File tidak ditemukan!\n";
        return;
    }

    file >> p.jumlahitem;
    file.ignore();

    if (p.jumlahitem > 10)
        p.jumlahitem = 10;

    string temp;

    for (int i = 0; i < p.jumlahitem; i++) {
        getline(file, p.inventory[i].nama, '|');
        getline(file, p.inventory[i].tipe, '|');
        getline(file, p.inventory[i].grade, '|');
        getline(file, temp);
        p.inventory[i].level = stoi(temp);
    }

    for (int i = 0; i < 4; i++) {
        getline(file, temp, '|');
        p.slot[i].kosong = stoi(temp);

        if (!p.slot[i].kosong) {
            getline(file, p.slot[i].equipment.nama, '|');
            getline(file, p.slot[i].equipment.tipe, '|');
            getline(file, p.slot[i].equipment.grade, '|');
            getline(file, temp);
            p.slot[i].equipment.level = stoi(temp);
        }
    }

    file.close();

    cout << "Data berhasil dimuat dari " << namaFile << endl;
}

// ================= GANTI FILE =================

void gantiFile() {

    cout << "\nNama file saat ini : " << namaFile << endl;

    cout << "Masukkan nama file baru : ";
    cin >> namaFile;

    if (namaFile.find(".txt") == string::npos) {
        namaFile += ".txt"; // otomatis tambah ekstensi
    }

    cout << "File aktif sekarang : " << namaFile << endl;

    loadFile(); // langsung load
}

// ================= MENU =================

void menuFile(){
    int pilih;
    cout << "1. Load File\n";
    cout << "2. Save File\n";
    cout << "3. Buat File Baru\n";
    cout << "Pilih: ";cin >> pilih;
    switch (pilih){
    case 1: loadFile(); break;
    case 2: saveFile(); break;
    case 3: gantiFile(); break;
    }
}

void menuEquipment(){
    int pilih;
    cout << "1. Tampilkan Equipment\n";
    cout << "2. Pakai Equipment\n";
    cout << "Pilih: ";cin >> pilih;
    switch (pilih){
    case 1: equipment(); break;
    case 2: equipItem(); break;
    }
}

void menuAdd(){
    int pilih;
    cout << "1. Add Item (Generate Random)\n";
    cout << "2. Add Item (Manual)\n";
    cout << "Pilih: ";cin >> pilih;
    switch (pilih){
    case 1: generateRandom(); break;
    case 2: tambahItem(); break;
    }
}

void menu() {
    int pilih;

    do {
        cout << "\n===== INVENTORY GAME =====\n";
        cout << "1. Add Item\n";
        cout << "2. Tampilkan Seluruh Item\n";
        cout << "3. Equipment\n";
        cout << "4. Sorting Item\n";
        cout << "5. Searching\n";
        cout << "6. File\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> pilih;

        switch (pilih) {
            case 1: menuAdd(); break;
            case 2: tampilItem(); break;
            case 3: menuEquipment(); break;
            case 4: sorting(); break;
            case 5: searching(); break;
            case 6: menuFile(); break;
            case 0: cout << "Terima kasih!\n"; break;
            default: cout << "Pilihan salah!\n";
        }

    } while (pilih != 0);
}

// ================= MAIN =================

int main() {
    menu(); // jalankan program
    return 0;
}