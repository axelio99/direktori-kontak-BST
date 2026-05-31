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
        return createNode(nama, no_telp);
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