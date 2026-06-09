#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct node
{
    char nama[15];
    long long int no_telp;
    struct node* left;
    struct node* right;
};

struct node* root = NULL;

struct node* CreateNode(char nama[15], long long int no_telp)
{
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    strcpy(newNode->nama, nama);
    newNode->no_telp = no_telp;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct node* insertNode(struct node* current, char nama[15], long long int no_telp)
{
    if (current == NULL) {
        return CreateNode(nama, no_telp);
    }
    if (strcmp(nama, current->nama) < 0) {
        current->left = insertNode(current->left, nama, no_telp);
    }
    else if (strcmp(nama, current->nama) > 0) {
        current->right = insertNode(current->right, nama, no_telp);
    }
    else {
        printf("Kontak dengan nama '%s' sudah ada di daftar,\n", nama);
    }

    return current;
}

struct node* searchNode(struct node* current, char nama[30])
{
    if(current == NULL)
    {
        return NULL;
    }
    
    int hasil = strcmp(nama, current->nama);
    if(hasil == 0)
    {
        return current;
    }
    else if(hasil < 0)
    {
        return searchNode(current->left, nama);
    }
    else
    {
        return searchNode(current->right, nama);
    }
}

void cariKontak()
{
    char nama[30];

    printf("Masukkan nama yang dicari: ");
    scanf("%s", nama);

    struct node* hasil = searchNode(root, nama);

    if(hasil != NULL)
    {
        printf("\nKontak ditemukan!\n");
        printf("Nama     : %s\n", hasil->nama);
        printf("No Telp  : %lld\n", hasil->no_telp);
    }
    else
    {
        printf("\nKontak tidak ditemukan!\n");
    }
}

struct node* findMinNode(struct node* current)
{
    while(current->left != NULL)
    {
        current = current->left;
    }
    return current;
}

struct node* deleteNode(struct node* current, char nama[15])
{
    if(current == NULL)
    {
        printf("Kontak dengan nama '%s' tidak ditemukan!\n", nama);
        return NULL;
    }
    
    int hasil = strcmp(nama, current->nama);
    
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
            free(current);
            return NULL;
        }
        
        // Kasus 2: Node memiliki satu anak (hanya anak kanan)
        if(current->left == NULL)
        {
            struct node* temp = current->right;
            free(current);
            return temp;
        }
        
        // Kasus 2: Node memiliki satu anak (hanya anak kiri)
        if(current->right == NULL)
        {
            struct node* temp = current->left;
            free(current);
            return temp;
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

void hapusKontak()
{
    char nama[30];
    
    printf("Masukkan nama kontak yang ingin dihapus: ");
    scanf("%s", nama);
    
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

void inOrder(struct node* current)
{
    if(current != NULL)
    {
        inOrder(current->left);
        printf("Nama     : %s\n", current->nama);
        printf("No Telp  : %lld\n", current->no_telp);
        printf("-------------------------\n");
        inOrder(current->right);
    }
}

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
        inOrder(root);
        printf("=========================\n");
    }
}

void cetakKontakRentangAbjad(struct node* current, char batasBawah, char batasAtas)
{
    if(current!=NULL)
    {    
        char hurufPertama = tolower(current->nama[0]);
        char left = tolower(batasBawah);
        char right = tolower(batasAtas);

        if (hurufPertama >= left)
        {
            cetakKontakRentangAbjad(current->left, batasBawah, batasAtas);
        }

        if (hurufPertama >= left && hurufPertama <= right)
        {
            printf("- %-15s : %lld\n", current->nama, current->no_telp);
        }

        if (hurufPertama <= right)
        {
            cetakKontakRentangAbjad(current->right, batasBawah, batasAtas);
        }
    }
}

void cetakKontak(struct node* current)
{
    if(current == NULL){
        printf("Daftar kontak masih kosong!\n");
        return;
    }
    char batasBawah; char batasAtas;
    printf("Input batas bawah: "); scanf(" %c", &batasBawah);
    printf("Input batas atas: "); scanf(" %c", &batasAtas);
    
    while(getchar() != '\n');

    printf("Tekan enter untuk mencetak kontak...\n"); getchar();

    printf("Daftar kontak dari rentang '%c' sampai '%c':\n", batasBawah, batasAtas);
    printf("===========================================\n");
    cetakKontakRentangAbjad(current, batasBawah, batasAtas);
    printf("===========================================\n");
}

int height(struct node* current) {
    if(current == NULL) {
        return 0; }

int leftheight = height(current->left);
int rightheight = height(current->right);

if (leftheight > rightheight) {
    return leftheight + 1; } 
    return rightheight + 1;
}

void analisiskeseimbangantree() {
    if(root == NULL) {
        printf("Daftar kontak masih kosong!\n");
        return; 
    }

    int tinggikiri = height(root->left);
    int tinggikanan = height(root->right);
    int balanceFactor = tinggikiri - tinggikanan;
    
    printf("\n=== Analisis Keseimbangan Tree kontak ===\n");
    printf("Tinggi subtree kiri  : %d\n", tinggikiri);
    printf("Tinggi subtree kanan : %d\n", tinggikanan);
    printf("Balance Factor       : %d\n", balanceFactor);

    if (balanceFactor >= -1 && balanceFactor <= 1) {
        printf("Tree kontak seimbang\n");
    } else {
        printf("Tree kontak tidak seimbang\n");
    }
}

int main () {
    int pilihan;
    char nama[15];
    long long int no_telp;

    do{
        printf("\n===========================\n");
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
                scanf("%14s", nama);
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