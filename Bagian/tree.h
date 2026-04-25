#ifndef TREE_H
#define TREE_H

// ============================================================
// tree.h — General Tree (Sistem Kategori Mata Pelajaran)
// ============================================================

#define MAX_CHILDREN 10

typedef struct TreeNode {
    int             idKategori;
    char            namaKategori[100];
    int             numChildren;
    struct TreeNode* children[MAX_CHILDREN];
} TreeNode;

TreeNode* buatNodeTree(int id, const char* nama);
void      addChild    (TreeNode* parent, TreeNode* child);

#endif // TREE_H
