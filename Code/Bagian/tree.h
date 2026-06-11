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
void      visualisasiTreeHierarki(TreeNode* node, int level, int showId);
int       kumpulkanRumpun(TreeNode* node, TreeNode** rumpunOut);
int       kumpulkanMataPelajaranDariRumpun(TreeNode* rumpun, TreeNode** mapelOut);

#endif // TREE_H
