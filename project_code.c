#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/* 
- Struct Node untuk representasi Binary Search Tree (BST)
- Menyimpan data kontak berupa nama dan nomor telepon,
- serta pointer ke anak kiri dan anak kanan.
*/  
struct node
{
    char nama[15];          // Menyimpan nama kontak (maksimal 14 karakter)
    long long int no_telp;  // Menyimpan nomor telepon (menggunakan tipe data long long untuk menghindari overflow)
    struct node* left;      // Pointer ke anak kiri (nilai/nama yang lebih kecil secara alfabet)
    struct node* right;     // Pointer ke anak kanan (nilai/nama yang lebih besar secara alfabet)
};

// Pointer global sebagai root/akar dari BST kontak
struct node* root = NULL;

/*
- Fungsi untuk membuat node baru di memori (Alokasi Dinamis)
- @param nama[] Sifat string nama kontak baru
- @param no_telp Nomor telepon kontak baru
- @return Alamat memori dari node baru yang berhasil dibuat
*/
struct node* CreateNode(char nama[15], long long int no_telp)
{
    // Mengalokasikan memori untuk node baru
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    
    // Menyalin data ke dalam node baru
    strcpy(newNode->nama, nama);
    newNode->no_telp = no_telp;
    
    // Inisialisasi pointer anak kiri dan kanan sebagai NULL
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

/*
- Fungsi rekursif untuk insert node baru ke dalam BST berdasarkan urutan alfabet nama
- @param current Pointer ke node saat ini (node yang sedang dicek)
- @param nama[] Nama kontak yang akan dimasukkan
- @param no_telp Nomor telepon yang akan dimasukkan
- @return Pointer yang menunjuk ke node saat ini (posisi tree yang terupdate)
*/
struct node* insertNode(struct node* current, char nama[15], long long int no_telp)
{
    // Jika posisi saat ini kosong (NULL), maka node baru akan ditempatkan di sini
    if (current == NULL) {
        return CreateNode(nama, no_telp);
    }

    // Jika nama baru secara alfabet lebih kecil dari nama di node saat ini, belok ke kiri
    if (strcmp(nama, current->nama) < 0) {
        current->left = insertNode(current->left, nama, no_telp);
    }

    // Jika nama baru secara alfabet lebih besar, belok ke kanan
    else if (strcmp(nama, current->nama) > 0) {
        current->right = insertNode(current->right, nama, no_telp);
    }

    // Jika hasil strcmp == 0, berarti nama sudah ada di tree (duplikat tidak diizinkan)
    else {
        printf("Kontak dengan nama '%s' sudah ada di daftar,\n", nama);
    }

    return current;
}

/*
- Fungsi rekursif untuk mencari node berdasarkan nama kontak
- @param current Pointer ke node saat ini
- @param nama[] Nama yang dicari
- @return Pointer ke node target jika ditemukan, atau NULL jika tidak ditemukan
*/
struct node* searchNode(struct node* current, char nama[30])
{
    // Basis rekursif: Jika filter sampai ke daun terluar dan tetap NULL, berarti data tidak ada
    if(current == NULL)
    {
        return NULL;
    }
    
    // Jika nama cocok
    int hasil = strcmp(nama, current->nama);
    if(hasil == 0)
    {
        return current;
    }

    // Jika nama yang dicari lebih kecil secara alfabet, cari ke sub-tree kiri
    else if(hasil < 0)
    {
        return searchNode(current->left, nama);
    }

    // Jika nama yang dicari lebih besar secara alfabet, cari ke sub-tree kanan
    else
    {
        return searchNode(current->right, nama);
    }
}

/*
- Fungsi antarmuka (wrapper) untuk mencari kontak melalui input user
*/
void cariKontak()
{
    char nama[30];

    printf("Masukkan nama yang dicari: ");
    scanf(" %29[^\n]", nama); //Membaca input string termasuk spasi hingga batas 29 karakter
    while(getchar() != '\n'); // Membersihkan buffer input

    struct node* hasil = searchNode(root, nama);

    // Menampilkan hasil pencarian
    if(hasil != NULL)
    {
        printf("\nKontak ditemukan!\n");
        printf("Nama     : %s\n", hasil->nama);
        printf("No Telp  : 0%lld\n", hasil->no_telp); // Menambahkan angka '0' di depan format output nomor telepon
    }
    else
    {
        printf("\nKontak tidak ditemukan!\n");
    }
}

/*
- Fungsi pembantu untuk mencari node dengan nilai terkecil (paling kiri) pada suatu sub-tree
- Digunakan untuk mencari In-Order Successor saat proses penghapusan node beranak dua
- @param current Pointer ke akar sub-tree kanan
- @return Pointer ke node paling kiri (nilai terkecil)
*/
struct node* findMinNode(struct node* current)
{
    // Terus bergerak ke kiri sampai menemukan node terkiri
    while(current->left != NULL)
    {
        current = current->left;
    }
    return current;
}

/*
- Fungsi rekursif untuk menghapus node dari BST berdasarkan nama
- @param current Pointer ke node saat ini
- @param nama[] Nama kontak yang ingin dihapus
- @return Pointer yang menunjuk ke node terupdate
*/
struct node* deleteNode(struct node* current, char nama[15])
{
    // Jika node tidak ditemukan
    if(current == NULL)
    {
        printf("Kontak dengan nama '%s' tidak ditemukan!\n", nama);
        return NULL;
    }
    
    int hasil = strcmp(nama, current->nama);
    
    // Cari node yang akan dihapus di sub-tree kiri atau kanan
    if(hasil < 0)
    {
        current->left = deleteNode(current->left, nama);
    }
    else if(hasil > 0)
    {
        current->right = deleteNode(current->right, nama);
    }
    else
    {
        // Node yang akan dihapus ditemukan
        
        // Kasus 1: Node adalah leaf (tidak ada anak)
        if(current->left == NULL && current->right == NULL)
        {
            free(current);  // Membebaskan memori
            return NULL;    // Mengembalikan NULL ke parent-nya
        }
        
        // Kasus 2: Node memiliki satu anak (hanya anak kanan)
        if(current->left == NULL)
        {
            struct node* temp = current->right; // Amankan alamat anak kanan
            free(current);                      // Hapus node saat ini
            return temp;                        // Hubungkan anak kanan langsung ke parent
        }
        
        // Kasus 2: Node memiliki satu anak (hanya anak kiri)
        if(current->right == NULL)
        {
            struct node* temp = current->left;  // Amankan alamat anak kiri
            free(current);                      // Hapus node saat ini
            return temp;                        // Hubungkan anak kiri langsung ke parent
        }
        
        // Kasus 3: Node memiliki dua anak
        // Cari in-order successor (node minimum di subtree kanan)
        struct node* successor = findMinNode(current->right);
        
        // Salin data successor ke node saat ini
        strcpy(current->nama, successor->nama);
        current->no_telp = successor->no_telp;
        
        // Hapus successor
        current->right = deleteNode(current->right, successor->nama);
    }
    
    return current;
}

/*
- Fungsi antarmuka untuk menghapus kontak melalui input user
*/
void hapusKontak()
{
    char nama[30];
    
    printf("Masukkan nama kontak yang ingin dihapus: ");
    scanf(" %29[^\n]", nama);
    while(getchar() != '\n');
    
    // Validasi apakah kontak tersebut ada sebelum dihapus
    struct node* hasil = searchNode(root, nama);
    
    if(hasil != NULL)
    {
        root = deleteNode(root, nama);
        printf("Kontak '%s' berhasil dihapus!\n", nama);
    }
    else
    {
        printf("Kontak dengan nama '%s' tidak ditemukan!\n", nama);
    }
}


/*
- Fungsi rekursif Traversal In-Order (Kiri -> Root -> Kanan)
- Traversal In-Order otomatis mencetak data secara urut (Ascending / A-Z)
- @param current Pointer ke node saat ini
*/
void inOrder(struct node* current)
{
    if(current != NULL)
    {
        inOrder(current->left); // Kunjungi sub-tree kiri

        // Cetak data node saat ini (Root)
        printf("Nama     : %s\n", current->nama);
        printf("No Telp  : 0%lld\n", current->no_telp);
        printf("-------------------------\n");

        inOrder(current->right); // Kunjungi sub-tree kanan
    }
}

/*
- Fungsi antarmuka untuk menampilkan seluruh isi kontak dari A sampai Z
*/
void tampilkanSemuaKontak()
{
    if(root == NULL)
    {
        printf("Daftar kontak masih kosong!\n");
    }
    else
    {
        printf("\n==== Daftar Kontak ====\n");
        printf("-------------------------\n");
        inOrder(root); // Memanggil fungsi traversal
        printf("=========================\n");
    }
}

/*
- Fungsi rekursif untuk mencetak kontak yang huruf pertama namanya masuk dalam rentang abjad tertentu
- @param current Pointer ke node saat ini
- @param batasBawah Karakter batas awal abjad (misal: 'a')
- @param batasAtas Karakter batas akhir abjad (misal: 'e')
*/
void cetakKontakRentangAbjad(struct node* current, char batasBawah, char batasAtas)
{
    if(current!=NULL)
    {    
        // Konversi karakter ke lowercase agar pengecekan bersifat Case-Insensitive
        char hurufPertama = tolower(current->nama[0]);
        char left = tolower(batasBawah);
        char right = tolower(batasAtas);

        // Optimasi BST: Jika huruf pertama >= batas bawah, ada kemungkinan anak kiri juga masuk rentang
        if (hurufPertama >= left)
        {
            cetakKontakRentangAbjad(current->left, batasBawah, batasAtas);
        }

        // Jika huruf pertama berada di dalam rentang [left ... right], cetak kontaknya
        if (hurufPertama >= left && hurufPertama <= right)
        {
            printf("- %-15s : 0%lld\n", current->nama, current->no_telp);
        }

        // Optimasi BST: Jika huruf pertama <= batas atas, ada kemungkinan anak kanan juga masuk rentang
        if (hurufPertama <= right)
        {
            cetakKontakRentangAbjad(current->right, batasBawah, batasAtas);
        }
    }
}

/*
- Fungsi antarmuka untuk menerima input rentang abjad dari user lalu memicu pencetakan
- @param current Pointer ke root tree kontak
*/
void cetakKontak(struct node* current)
{
    if(current == NULL){
        printf("Daftar kontak masih kosong!\n");
        return;
    }
    char batasBawah; char batasAtas;
    printf("Input batas bawah: "); scanf(" %c", &batasBawah);
    printf("Input batas atas: "); scanf(" %c", &batasAtas);
    
    while(getchar() != '\n'); // Membersihkan sisa buffer input

    printf("Tekan enter untuk mencetak kontak...\n"); getchar();

    printf("Daftar kontak dari rentang '%c' sampai '%c':\n", batasBawah, batasAtas);
    printf("===========================================\n");
    cetakKontakRentangAbjad(current, batasBawah, batasAtas);
    printf("===========================================\n");
}

/*
- Fungsi rekursif untuk menghitung tinggi (height) maksimal dari suatu node/sub-tree
- @param current Pointer ke node yang dihitung tingginya
- @return Nilai integer tinggi node (0 jika NULL)
*/
int height(struct node* current) {
    if(current == NULL) {
        return 0; 
    }

    // Hitung tinggi sub-tree kiri dan kanan secara rekursif
    int leftHeight = height(current->left);
    int rightHeight = height(current->right);

    // Ambil nilai tinggi yang paling maksimal lalu ditambah 1 (karena menghitung node saat ini)
    if (leftHeight > rightHeight) {
        return leftHeight + 1;
    } 
        return rightHeight + 1;
}

/*
- Fungsi untuk menganalisis dan memeriksa keseimbangan struktur BST
- Keseimbangan diukur dari selisih tinggi sub-tree kiri dan sub-tree kanan
*/
void analisiskeseimbangantree() {
    if(root == NULL) {
        printf("Daftar kontak masih kosong!\n");
        return; 
    }

    // Hitung tinggi masing-masing sub-tree dari root utama
    int tinggikiri = height(root->left);
    int tinggikanan = height(root->right);
    
    // Balance Factor = Tinggi Kiri - Tinggi Kanan
    int balanceFactor = tinggikiri - tinggikanan;
    
    printf("\n=== Analisis Keseimbangan Tree kontak ===\n");
    printf("Tinggi subtree kiri  : %d\n", tinggikiri);
    printf("Tinggi subtree kanan : %d\n", tinggikanan);
    printf("Balance Factor       : %d\n", balanceFactor);

    // Kriteria seimbang jika Balance Factor bernilai -1, 0, atau 1
    if (balanceFactor >= -1 && balanceFactor <= 1) {
        printf("Tree kontak seimbang\n");
    } else {
        printf("Tree kontak tidak seimbang\n");
    }
}

// Fungsi Utama
int main () {
    int pilihan;
    char nama[15];
    long long int no_telp;

    do{
        printf("=============================\n");
        printf("  Aplikasi Direktori Kontak\n");
        printf("=============================\n");
        printf("1. Tambah Kontak Baru\n");
        printf("2. Cari Kontak\n");
        printf("3. Hapus Kontak\n");
        printf("4. Tampilkan Semua Kontak (A-Z)\n");
        printf("5. Cetak Kontak Berdasarkan Rentang Abjad\n");
        printf("6. Analisis Keseimbangan Tree Kontak\n");
        printf("7. Keluar\n");
        printf("=============================\n");
        printf("Pilih menu (1-7): ");
        scanf("%d", &pilihan);

        while(getchar() != '\n');

        switch(pilihan) {
            case 1:
                printf("\n[Tambah Kontak Baru]\n");
                printf("Masukkan Nama (Max 14 huruf): ");
                scanf(" %14[^\n]", nama);
                while(getchar() != '\n');
                printf("Masukkan No Telp: ");
                scanf("%lld", &no_telp);
                root = insertNode(root, nama, no_telp);
                printf("Kontak '%s' berhasil ditambahkan!\n", nama);
                break;

            case 2:
                printf("\n[Cari Kontak]\n");
                cariKontak();
                break;
            
                case 3:
                printf("\n[Hapus Kontak]\n");
                hapusKontak();
                break;

            case 4:
                tampilkanSemuaKontak();
                break;

            case 5:
                printf("\n[Cetak Kontak Berdasarkan Rentang Abjad]\n");
                cetakKontak(root);
                break;
            
            case 6:
                analisiskeseimbangantree();
                break;
            
            case 7:
                printf("Terima kasih telah menggunakan aplikasi direktori kontak!\n");
                break;
            
            default:
                printf("Pilihan tidak valid, silakan coba lagi.\n");
        }
    } while (pilihan != 7);

    return 0;
}