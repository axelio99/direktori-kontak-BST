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