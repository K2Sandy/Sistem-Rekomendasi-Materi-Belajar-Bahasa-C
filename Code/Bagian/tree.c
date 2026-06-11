#include <stdlib.h>
#include <string.h>
#include <stdio.h>
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

// ============================================================
// Visualisasi Struktur Tree (Hierarki dengan indentasi)
// ============================================================
void visualisasiTreeHierarki(TreeNode* node, int level, int showId) {
    if (node == NULL) return;
    
    // Print indentasi berdasarkan level
    for (int i = 0; i < level; i++) {
        printf("  ");
    }
    
    // Tampilkan node
    if (level == 0) {
        printf("📚 %s\n", node->namaKategori);
    } else if (node->numChildren > 0) {
        printf("📂 %s\n", node->namaKategori);
    } else {
        // Ini adalah leaf (mata pelajaran)
        if (showId) {
            printf("   [%d] %s\n", node->idKategori, node->namaKategori);
        } else {
            printf("   • %s\n", node->namaKategori);
        }
    }
    
    // Rekursi ke anak
    for (int i = 0; i < node->numChildren; i++) {
        visualisasiTreeHierarki(node->children[i], level + 1, showId);
    }
}

// ============================================================
// Helper: Ambil rumpun (branch nodes) dari root
// ============================================================
int kumpulkanRumpun(TreeNode* node, TreeNode** rumpunOut) {
    int count = 0;
    if (node == NULL) return 0;
    
    // Ambil semua children dari root yang memiliki children sendiri (= rumpun)
    for (int i = 0; i < node->numChildren; i++) {
        if (node->children[i]->numChildren > 0) {
            rumpunOut[count++] = node->children[i];
        }
    }
    return count;
}

// Helper: Ambil mata pelajaran dari rumpun
int kumpulkanMataPelajaranDariRumpun(TreeNode* rumpun, TreeNode** mapelOut) {
    int count = 0;
    if (rumpun == NULL) return 0;
    
    // Ambil semua children dari rumpun yang tidak punya children (= mata pelajaran)
    for (int i = 0; i < rumpun->numChildren; i++) {
        if (rumpun->children[i]->numChildren == 0) {
            mapelOut[count++] = rumpun->children[i];
        }
    }
    return count;
}
