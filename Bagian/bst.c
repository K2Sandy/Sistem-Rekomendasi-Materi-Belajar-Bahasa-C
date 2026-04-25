#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"

// ============================================================
// bst.c — Implementasi Binary Search Tree
// ============================================================

BSTNode* insertBST(BSTNode* node, Materi m) {
    if (node == NULL) {
        BSTNode* newNode = (BSTNode*)malloc(sizeof(BSTNode));
        newNode->data  = m;
        newNode->left  = NULL;
        newNode->right = NULL;
        return newNode;
    }
    if (m.tingkatKesulitan < node->data.tingkatKesulitan)
        node->left  = insertBST(node->left,  m);
    else if (m.tingkatKesulitan > node->data.tingkatKesulitan)
        node->right = insertBST(node->right, m);
    return node;
}

void preorderTraversalBST(BSTNode* node, const char* prefix) {
    if (node == NULL) return;
    printf(" %s|-- %s (Kesulitan: %d)\n",
           prefix, node->data.nama, node->data.tingkatKesulitan);

    char newPrefix[100];
    strcpy(newPrefix, prefix);
    strcat(newPrefix, "    ");
    preorderTraversalBST(node->left,  newPrefix);
    preorderTraversalBST(node->right, newPrefix);
}

void kumpulkanMateriInorder(BSTNode* node, int filterKatId,
                             int maxDurasi, int maxSulit,
                             Materi* arr[], int* count) {
    if (node == NULL) return;

    kumpulkanMateriInorder(node->left, filterKatId, maxDurasi, maxSulit, arr, count);

    if (node->data.kategoriId      == filterKatId &&
        node->data.durasiMenit     <= maxDurasi   &&
        node->data.tingkatKesulitan <= maxSulit) {
        arr[(*count)++] = &(node->data);
    }

    kumpulkanMateriInorder(node->right, filterKatId, maxDurasi, maxSulit, arr, count);
}
