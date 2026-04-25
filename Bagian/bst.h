#ifndef BST_H
#define BST_H

// ============================================================
// bst.h — Binary Search Tree (Database Materi)
// ============================================================

#include "materi.h"

typedef struct BSTNode {
    Materi           data;
    struct BSTNode*  left;
    struct BSTNode*  right;
} BSTNode;

BSTNode* insertBST             (BSTNode* node, Materi m);
void     preorderTraversalBST  (BSTNode* node, const char* prefix);
void     kumpulkanMateriInorder(BSTNode* node, int filterKatId,
                                int maxDurasi, int maxSulit,
                                Materi* arr[], int* count);

#endif // BST_H
