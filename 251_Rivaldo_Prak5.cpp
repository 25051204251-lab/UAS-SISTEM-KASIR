#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// ======================================================
// STRUCT BARANG
// ======================================================
struct Barang {
    string kode;
    string nama;
    string kategori;
    int harga;
    int stok;
};

// ======================================================
// LINKED LIST
// ======================================================
struct Node {
    Barang data;
    Node* next;
};

Node* head = NULL;

// ======================================================
// STACK TRANSAKSI
// ======================================================
struct StackNode {
    string transaksi;
    StackNode* next;
};

StackNode* top = NULL;

// ======================================================
// QUEUE PELANGGAN
// ======================================================
struct QueueNode {
    string nama;
    QueueNode* next;
};

QueueNode* front = NULL;
QueueNode* rear = NULL;

// ======================================================
// BST
// ======================================================
struct TreeNode {
    Barang data;
    TreeNode* left;
    TreeNode* right;
};

TreeNode* root = NULL;

// ======================================================
// HASH TABLE
// ======================================================
const int SIZE = 10;

struct HashNode {
    Barang data;
    HashNode* next;
};

HashNode* hashTable[SIZE] = {NULL};

// ======================================================
// SIMPAN CSV
// ======================================================
void simpanCSV() {

    ofstream file("data_barang.csv");

    file << "Kode,Nama,Kategori,Harga,Stok\n";

    Node* temp = head;

    while(temp != NULL) {

        file << temp->data.kode << ",";
        file << temp->data.nama << ",";
        file << temp->data.kategori << ",";
        file << temp->data.harga << ",";
        file << temp->data.stok << "\n";

        temp = temp->next;
    }

    file.close();
}

// ======================================================
// HASH FUNCTION
// ======================================================
int hashFunction(string kode) {

    int jumlah = 0;

    for(int i = 0; i < kode.length(); i++) {
        jumlah += kode[i];
    }

    return jumlah % SIZE;
}

// ======================================================
// INSERT HASH
// ======================================================
void insertHash(Barang barang) {

    int index = hashFunction(barang.kode);

    HashNode* baru = new HashNode;

    baru->data = barang;
    baru->next = hashTable[index];

    hashTable[index] = baru;
}

// ======================================================
// SEARCH HASH
// ======================================================
void searchHash() {

    string nama;

    cin.ignore();

    cout << "\nMasukkan nama barang : ";
    getline(cin, nama);

    Node* temp = head;

    while(temp != NULL) {

        if(temp->data.nama == nama) {

            cout << "\nBarang ditemukan!\n";
            cout << "Kode     : " << temp->data.kode << endl;
            cout << "Nama     : " << temp->data.nama << endl;
            cout << "Kategori : " << temp->data.kategori << endl;
            cout << "Harga    : Rp " << temp->data.harga << endl;
            cout << "Stok     : " << temp->data.stok << endl;

            return;
        }

        temp = temp->next;
    }

    cout << "\nBarang tidak ditemukan!\n";
}

// ======================================================
// GRAPH KATEGORI
// ======================================================
void tampilGraph() {

    string cariKategori;
    bool ketemu = false;

    cin.ignore();

    cout << "\nMasukkan kategori : ";
    getline(cin, cariKategori);

    Node* temp = head;

    cout << "\nBarang dalam kategori "
         << cariKategori << " :\n";

    while(temp != NULL) {

        if(temp->data.kategori == cariKategori) {

            cout << "- " << temp->data.nama << endl;

            ketemu = true;
        }

        temp = temp->next;
    }

    if(!ketemu) {
        cout << "Kategori tidak ditemukan!\n";
    }
}

// ======================================================
// TAMBAH BARANG
// ======================================================
void tambahBarang() {

    Node* baru = new Node;

    cout << "\nKode Barang  : ";
    cin >> baru->data.kode;

    cin.ignore();

    cout << "Nama Barang  : ";
    getline(cin, baru->data.nama);

    cout << "Kategori     : ";
    getline(cin, baru->data.kategori);

    cout << "Harga Barang : ";
    cin >> baru->data.harga;

    cout << "Stok Barang  : ";
    cin >> baru->data.stok;

    baru->next = NULL;

    if(head == NULL) {
        head = baru;
    }
    else {

        Node* temp = head;

        while(temp->next != NULL) {
            temp = temp->next;
        }

        temp->next = baru;
    }

    insertHash(baru->data);

    simpanCSV();

    cout << "\nBarang berhasil ditambahkan!\n";
}

// ======================================================
// TAMPIL BARANG
// ======================================================
void tampilBarang() {

    if(head == NULL) {

        cout << "\nData barang kosong!\n";
        return;
    }

    Node* temp = head;

    cout << "\n========== DAFTAR BARANG ==========\n";

    while(temp != NULL) {

        cout << "Kode     : " << temp->data.kode << endl;
        cout << "Nama     : " << temp->data.nama << endl;
        cout << "Kategori : " << temp->data.kategori << endl;
        cout << "Harga    : Rp " << temp->data.harga << endl;
        cout << "Stok     : " << temp->data.stok << endl;
        cout << "-----------------------------------\n";

        temp = temp->next;
    }
}

// ======================================================
// CARI BARANG
// ======================================================
void cariBarang() {

    string cari;
    bool ketemu = false;

    cout << "\nMasukkan kode barang : ";
    cin >> cari;

    Node* temp = head;

    while(temp != NULL) {

        if(temp->data.kode == cari) {

            cout << "\nBarang ditemukan!\n";
            cout << "Nama      : " << temp->data.nama << endl;
            cout << "Kategori  : " << temp->data.kategori << endl;
            cout << "Harga     : Rp " << temp->data.harga << endl;
            cout << "Stok      : " << temp->data.stok << endl;

            ketemu = true;
        }

        temp = temp->next;
    }

    if(!ketemu) {
        cout << "\nBarang tidak ditemukan!\n";
    }
}

// ======================================================
// SORTING HARGA
// ======================================================
void sortingHarga() {

    if(head == NULL) {
        return;
    }

    Node* i;
    Node* j;

    for(i = head; i != NULL; i = i->next) {

        for(j = i->next; j != NULL; j = j->next) {

            if(i->data.harga > j->data.harga) {

                Barang temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }

    simpanCSV();

    cout << "\nBarang berhasil diurutkan berdasarkan harga!\n";
}

// ======================================================
// PUSH STACK
// ======================================================
void pushTransaksi(string data) {

    StackNode* baru = new StackNode;

    baru->transaksi = data;
    baru->next = top;

    top = baru;
}

// ======================================================
// CHECKOUT
// ======================================================
void checkout() {

    string namaBarang;
    int jumlahBeli;
    bool ketemu = false;

    cin.ignore();

    cout << "\nNama barang dibeli : ";
    getline(cin, namaBarang);

    Node* temp = head;

    while(temp != NULL) {

        if(temp->data.nama == namaBarang) {

            ketemu = true;

            cout << "Jumlah beli : ";
            cin >> jumlahBeli;

            if(jumlahBeli > temp->data.stok) {

                cout << "\nStok tidak cukup!\n";
                return;
            }

            temp->data.stok -= jumlahBeli;

            int total = temp->data.harga * jumlahBeli;

            string transaksi =
                temp->data.nama +
                " x" +
                to_string(jumlahBeli) +
                " | Total Rp " +
                to_string(total);

            pushTransaksi(transaksi);

            simpanCSV();

            cout << "\nCheckout berhasil!\n";
            cout << "Total bayar : Rp " << total << endl;
            cout << "Sisa stok   : " << temp->data.stok << endl;

            return;
        }

        temp = temp->next;
    }

    if(!ketemu) {
        cout << "\nBarang tidak ditemukan!\n";
    }
}

// ======================================================
// TAMPIL RIWAYAT
// ======================================================
void tampilRiwayat() {

    if(top == NULL) {

        cout << "\nBelum ada transaksi!\n";
        return;
    }

    StackNode* temp = top;

    cout << "\n======= RIWAYAT TRANSAKSI =======\n";

    while(temp != NULL) {

        cout << "- " << temp->transaksi << endl;

        temp = temp->next;
    }
}

// ======================================================
// TAMBAH ANTRIAN
// ======================================================
void tambahAntrian() {

    QueueNode* baru = new QueueNode;

    cin.ignore();

    cout << "\nNama pelanggan : ";
    getline(cin, baru->nama);

    baru->next = NULL;

    if(front == NULL) {
        front = rear = baru;
    }
    else {
        rear->next = baru;
        rear = baru;
    }

    cout << "\nPelanggan masuk ke antrian!\n";
}

// ======================================================
// PROSES ANTRIAN
// ======================================================
void prosesAntrian() {

    if(front == NULL) {

        cout << "\nAntrian kosong!\n";
        return;
    }

    QueueNode* hapus = front;

    cout << "\nPelanggan diproses : "
         << front->nama << endl;

    front = front->next;

    delete hapus;

    if(front == NULL) {
        rear = NULL;
    }
}

// ======================================================
// TAMPIL ANTRIAN
// ======================================================
void tampilAntrian() {

    if(front == NULL) {

        cout << "\nAntrian kosong!\n";
        return;
    }

    QueueNode* temp = front;

    cout << "\n========== ANTRIAN PELANGGAN ==========\n";

    while(temp != NULL) {

        cout << "- " << temp->nama << endl;

        temp = temp->next;
    }
}

// ======================================================
// INSERT BST
// ======================================================
TreeNode* insertBST(TreeNode* root, Barang data) {

    if(root == NULL) {

        TreeNode* baru = new TreeNode;

        baru->data = data;
        baru->left = NULL;
        baru->right = NULL;

        return baru;
    }

    if(data.kode < root->data.kode) {
        root->left = insertBST(root->left, data);
    }

    else if(data.kode > root->data.kode) {
        root->right = insertBST(root->right, data);
    }

    return root;
}

// ======================================================
// TAMBAH STOK GUDANG
// ======================================================
void tambahBST() {

    string kode;
    int tambahStok;
    bool ketemu = false;

    cout << "\nMasukkan kode barang : ";
    cin >> kode;

    cout << "Tambah stok : ";
    cin >> tambahStok;

    Node* temp = head;

    while(temp != NULL) {

        if(temp->data.kode == kode) {

            temp->data.stok += tambahStok;

            root = insertBST(root, temp->data);

            simpanCSV();

            cout << "\nStok gudang berhasil ditambahkan!\n";
            cout << "Total stok sekarang : "
                 << temp->data.stok << endl;

            ketemu = true;
            return;
        }

        temp = temp->next;
    }

    if(!ketemu) {
        cout << "\nBarang tidak ditemukan!\n";
    }
}

// ======================================================
// INORDER
// ======================================================
void inorder(TreeNode* root) {

    if(root == NULL) {
        return;
    }

    inorder(root->left);

    cout << "\nKode     : " << root->data.kode << endl;
    cout << "Nama     : " << root->data.nama << endl;
    cout << "Kategori : " << root->data.kategori << endl;
    cout << "Harga    : Rp " << root->data.harga << endl;
    cout << "Stok     : " << root->data.stok << endl;
    cout << "---------------------------\n";

    inorder(root->right);
}

// ======================================================
// TAMPIL BST
// ======================================================
void tampilBST() {

    if(root == NULL) {

        cout << "\nData gudang kosong!\n";
        return;
    }

    cout << "\n========== DATA GUDANG ==========\n";

    inorder(root);
}

// ======================================================
// MAIN PROGRAM
// ======================================================
int main() {

    int pilih;

    do {

        cout << "\n========== SISTEM KASIR ==========\n";
        cout << "1. Tambah Barang\n";
        cout << "2. Tampilkan Barang\n";
        cout << "3. Cari Barang Berdasarkan Kode\n";
        cout << "4. Urutkan Harga Barang\n";
        cout << "5. Checkout\n";
        cout << "6. Riwayat Transaksi\n";
        cout << "7. Tambah Antrian Pelanggan\n";
        cout << "8. Proses Antrian Pelanggan\n";
        cout << "9. Tampilkan Antrian\n";
        cout << "10. Tambah Stok Gudang\n";
        cout << "11. Tampilkan Data Gudang\n";
        cout << "12. Pencarian Cepat Barang\n";
        cout << "13. Cari Barang Berdasarkan Kategori\n";
        cout << "0. Keluar\n";
        cout << "==================================\n";

        cout << "Pilih menu : ";
        cin >> pilih;

        switch(pilih) {

            case 1:
                tambahBarang();
                break;

            case 2:
                tampilBarang();
                break;

            case 3:
                cariBarang();
                break;

            case 4:
                sortingHarga();
                break;

            case 5:
                checkout();
                break;

            case 6:
                tampilRiwayat();
                break;

            case 7:
                tambahAntrian();
                break;

            case 8:
                prosesAntrian();
                break;

            case 9:
                tampilAntrian();
                break;

            case 10:
                tambahBST();
                break;

            case 11:
                tampilBST();
                break;

            case 12:
                searchHash();
                break;

            case 13:
                tampilGraph();
                break;

            case 0:
                cout << "\nProgram selesai.\n";
                break;

            default:
                cout << "\nMenu tidak tersedia!\n";
        }

    } while(pilih != 0);

    return 0;
}