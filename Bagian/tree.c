#include <stdlib.h>
#include <string.h>
#include "tree.h"

// ============================================================
// tree.c — Implementasi General Tree
// ============================================================

TreeNode* buatNodeTree(int id, const char* nama) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->idKategori  = id;
    newNode->numChildren = 0;
    strcpy(newNode->namaKategori, nama);
    return newNode;
}

void addChild(TreeNode* parent, TreeNode* child) {
    if (parent->numChildren < MAX_CHILDREN)
        parent->children[parent->numChildren++] = child;
}
