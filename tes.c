#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_CHILDREN 10

typedef struct {
    int kategoriId; char nama[50]; char deskripsi[50];
    int tingkatKesulitan; int durasiMenit;      
} Materi;

Materi buatMateri(int katId, const char* nama, const char* desk, int kesulitan, int durasi) {
    Materi m; m.kategoriId = katId; strcpy(m.nama, nama); strcpy(m.deskripsi, desk);
    m.tingkatKesulitan = kesulitan; m.durasiMenit = durasi; return m;
}

void bersihkanBuffer() { int c; while ((c = getchar()) != '\n' && c != EOF); }

typedef struct ListNode { Materi data; struct ListNode* next; } ListNode;
typedef struct { ListNode* head; } PlaylistLinkedList;
void initLinkedList(PlaylistLinkedList* list) { list->head = NULL; }
void tambahMateri(PlaylistLinkedList* list, Materi m) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode)); newNode->data = m; newNode->next = NULL;
    if (list->head == NULL) { list->head = newNode; return; }
    ListNode* temp = list->head; while (temp->next != NULL) temp = temp->next; temp->next = newNode;
}
void tampilkanPlaylist(PlaylistLinkedList* list) {
    if (list->head == NULL) { printf("\n [-] Daftar belajarmu masih kosong.\n"); return; }
    ListNode* temp = list->head; int no = 1;
    printf("\n =========================================================================\n");
    printf(" %-4s %-25s %-12s %-10s %s\n", "No", "Judul Materi", "Sulit(/100)", "Waktu", "Keterangan");
    printf(" -------------------------------------------------------------------------\n");
    while (temp != NULL) {
        printf(" %-4d %-25s %-12d %-10d %s\n", no++, temp->data.nama, temp->data.tingkatKesulitan, temp->data.durasiMenit, temp->data.deskripsi);
        temp = temp->next;
    }
    printf(" =========================================================================\n");
}

typedef struct BSTNode { Materi data; struct BSTNode* left; struct BSTNode* right; } BSTNode;
BSTNode* insertBST(BSTNode* node, Materi m) {
    if (node == NULL) {
        BSTNode* newNode = (BSTNode*)malloc(sizeof(BSTNode)); newNode->data = m; 
        newNode->left = NULL; newNode->right = NULL; return newNode;
    }
    if (m.tingkatKesulitan < node->data.tingkatKesulitan) node->left = insertBST(node->left, m);
    else if (m.tingkatKesulitan > node->data.tingkatKesulitan) node->right = insertBST(node->right, m);
    return node;
}

typedef struct TreeNode { int idKategori; char namaKategori[100]; int numChildren; struct TreeNode* children[MAX_CHILDREN]; } TreeNode;
TreeNode* buatNodeTree(int id, const char* nama) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->idKategori = id; strcpy(newNode->namaKategori, nama); newNode->numChildren = 0; return newNode;
}
void addChild(TreeNode* parent, TreeNode* child) {
    if (parent->numChildren < MAX_CHILDREN) { parent->children[parent->numChildren++] = child; }
}

// FUNGSI TABEL PEMILIHAN MATERI
void prosesPilihMateri(Materi* arr[], int count, PlaylistLinkedList* playlist) {
    if (count == 0) {
        printf("\n [-] Tidak ada materi yang ditemukan/sesuai kriteria.\n");
        printf(" Tekan [Enter] untuk kembali..."); getchar(); return;
    }
    printf("\n =========================================================================\n");
    printf(" %-4s %-25s %-12s %-10s %s\n", "No", "Judul Materi", "Sulit(/100)", "Waktu(m)", "Keterangan Singkat");
    printf(" -------------------------------------------------------------------------\n");
    for(int i = 0; i < count; i++) {
        printf(" %-4d %-25s %-12d %-10d %s\n", i+1, arr[i]->nama, arr[i]->tingkatKesulitan, arr[i]->durasiMenit, arr[i]->deskripsi);
    }
    printf(" =========================================================================\n");
    while (true) {
        int pilihan; printf("\n Masukkan No materi untuk ditambah (0 untuk kembali): ");
        scanf("%d", &pilihan); bersihkanBuffer();
        if (pilihan == 0) break;
        if (pilihan >= 1 && pilihan <= count) {
            tambahMateri(playlist, *(arr[pilihan-1])); printf(" [+] '%s' masuk ke Daftar Belajar!\n", arr[pilihan-1]->nama);
        } else { printf(" [-] Nomor tidak valid.\n"); }
    }
}

// ========================================================
// PROGRAM UTAMA
// ========================================================
int main() {
    PlaylistLinkedList daftarBelajar; initLinkedList(&daftarBelajar);
    BSTNode* rootBST = NULL;

    TreeNode* menuRoot = buatNodeTree(0, "Katalog Ilmu Pengetahuan");
    TreeNode* sains = buatNodeTree(0, "Sains & Teknologi (SAINTEK)");
    TreeNode* soshum = buatNodeTree(0, "Sosial & Humaniora (SOSHUM)");
    addChild(menuRoot, sains); addChild(menuRoot, soshum);
    addChild(sains, buatNodeTree(1, "Informatika")); addChild(sains, buatNodeTree(2, "Matematika"));
    addChild(sains, buatNodeTree(3, "Biologi")); addChild(sains, buatNodeTree(4, "Fisika"));
    addChild(sains, buatNodeTree(6, "Kimia")); addChild(soshum, buatNodeTree(5, "Sejarah"));

    // --- SETUP BST MATERI (Data disuntikkan ke memori) ---
    // 1: Informatika
    rootBST = insertBST(rootBST, buatMateri(1, "Tree & BST", "Hirarki data non-linear.", 50, 45));
    rootBST = insertBST(rootBST, buatMateri(1, "Logika Dasar", "Fondasi algoritma IF-ELSE.", 10, 30));
    rootBST = insertBST(rootBST, buatMateri(1, "Array 1 Dimensi", "Penyimpanan memori sekuensial.", 20, 25));
    rootBST = insertBST(rootBST, buatMateri(1, "Linked List", "Pointer data dinamis.", 30, 60));
    rootBST = insertBST(rootBST, buatMateri(1, "Graph Theory", "Rute terpendek Dijkstra.", 80, 90));
    // 2: Matematika
    rootBST = insertBST(rootBST, buatMateri(2, "Trigonometri", "Sin, Cos, Tan.", 45, 40));
    rootBST = insertBST(rootBST, buatMateri(2, "Aritmatika Dasar", "Penjumlahan & Pengurangan.", 15, 20));
    rootBST = insertBST(rootBST, buatMateri(2, "Aljabar Linear", "Matriks dan Vektor.", 35, 60));
    rootBST = insertBST(rootBST, buatMateri(2, "Kalkulus Lanjut", "Limit dan Integral.", 60, 90));
    rootBST = insertBST(rootBST, buatMateri(2, "Probabilitas", "Peluang & Statistik.", 70, 75));
    // 3: Biologi
    rootBST = insertBST(rootBST, buatMateri(3, "Genetika Kromosom", "Pewarisan sifat gen.", 45, 50));
    rootBST = insertBST(rootBST, buatMateri(3, "Anatomi Sel", "Bagian-bagian sel.", 15, 30));
    rootBST = insertBST(rootBST, buatMateri(3, "Ekosistem", "Rantai makanan.", 30, 40));
    rootBST = insertBST(rootBST, buatMateri(3, "Evolusi Manusia", "Teori asal usul.", 75, 60));
    rootBST = insertBST(rootBST, buatMateri(3, "Sistem Saraf", "Otak dan impuls.", 85, 80));
    // 4: Fisika
    rootBST = insertBST(rootBST, buatMateri(4, "Hukum Newton", "Gaya dan gerak lurus.", 25, 45));
    rootBST = insertBST(rootBST, buatMateri(4, "Kinematika", "Kecepatan & Percepatan.", 35, 50));
    rootBST = insertBST(rootBST, buatMateri(4, "Optik Geometri", "Cermin dan Lensa.", 55, 60));
    rootBST = insertBST(rootBST, buatMateri(4, "Termodinamika", "Suhu dan Kalor.", 65, 80));
    rootBST = insertBST(rootBST, buatMateri(4, "Fisika Kuantum", "Partikel sub-atomik.", 95, 120));
    // 5: Sejarah
    rootBST = insertBST(rootBST, buatMateri(5, "Perang Dingin", "Blok Barat vs Timur.", 50, 40));
    rootBST = insertBST(rootBST, buatMateri(5, "Manusia Purba", "Zaman batu dan logam.", 15, 25));
    rootBST = insertBST(rootBST, buatMateri(5, "Perang Dunia II", "Sejarah eropa 1940an.", 20, 30));
    rootBST = insertBST(rootBST, buatMateri(5, "Kemerdekaan RI", "Proklamasi 1945.", 30, 35));
    rootBST = insertBST(rootBST, buatMateri(5, "Revolusi Industri", "Eropa abad ke-18.", 40, 45));
    // 6: Kimia
    rootBST = insertBST(rootBST, buatMateri(6, "Asam & Basa", "Skala pH dan titrasi.", 50, 45));
    rootBST = insertBST(rootBST, buatMateri(6, "Tabel Periodik", "Unsur-unsur dasar.", 20, 30));
    rootBST = insertBST(rootBST, buatMateri(6, "Ikatan Kimia", "Kovalen dan Ionik.", 40, 40));
    rootBST = insertBST(rootBST, buatMateri(6, "Stoikiometri", "Perhitungan mol.", 60, 70));
    rootBST = insertBST(rootBST, buatMateri(6, "Kimia Organik", "Rantai Karbon.", 80, 90));

    bool running = true;
    while (running) {
        int pilihanUtama;
        printf("\n======================================================\n");
        printf("         SISTEM ASISTEN BELAJAR EDUGRAPH              \n");
        printf("======================================================\n");
        printf(" 1. Katalog & Silabus Pelajaran\n");
        printf(" 2. Sistem Rekomendasi Belajar (Filter Cerdas)\n");
        printf(" 3. Lihat Daftar Belajarku\n");
        printf(" 0. Keluar Aplikasi\n");
        printf("======================================================\n");
        printf(" Pilih menu (0-3): ");
        scanf("%d", &pilihanUtama); bersihkanBuffer();

        switch (pilihanUtama) {
            case 1: printf("\n [-] Fitur Katalog masih dalam pengembangan.\n"); break;
            case 2: printf("\n [-] Fitur Rekomendasi masih dalam pengembangan.\n"); break;
            case 3: printf("\n=== DAFTAR BELAJARKU ===\n"); tampilkanPlaylist(&daftarBelajar); break;
            case 0: printf("\n Terima kasih telah menggunakan EduGraph. Sampai jumpa!\n"); running = false; break;
            default: printf("\n [-] Pilihan tidak valid. Silakan coba lagi.\n");
        }
    }
    return 0;
}