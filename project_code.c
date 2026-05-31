#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

