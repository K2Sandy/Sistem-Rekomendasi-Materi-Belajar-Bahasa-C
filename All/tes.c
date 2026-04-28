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

// SORTING 1: Berdasarkan Waktu Tercepat
void insertionSortByDurasi(PlaylistLinkedList* list) {
    if (list->head == NULL || list->head->next == NULL) return;
    ListNode* sorted = NULL; ListNode* current = list->head; 
    while (current != NULL) {
        ListNode* nextNode = current->next; 
        if (sorted == NULL || sorted->data.durasiMenit >= current->data.durasiMenit) {
            current->next = sorted; sorted = current;
        } else {
            ListNode* temp = sorted;
            while (temp->next != NULL && temp->next->data.durasiMenit < current->data.durasiMenit) temp = temp->next;
            current->next = temp->next; temp->next = current;
        }
        current = nextNode; 
    }
    list->head = sorted; 
}

// SORTING 2: Berdasarkan Tingkat Kesulitan Terendah
void insertionSortByKesulitan(PlaylistLinkedList* list) {
    if (list->head == NULL || list->head->next == NULL) return;
    ListNode* sorted = NULL; ListNode* current = list->head; 
    while (current != NULL) {
        ListNode* nextNode = current->next; 
        if (sorted == NULL || sorted->data.tingkatKesulitan >= current->data.tingkatKesulitan) {
            current->next = sorted; sorted = current;
        } else {
            ListNode* temp = sorted;
            while (temp->next != NULL && temp->next->data.tingkatKesulitan < current->data.tingkatKesulitan) temp = temp->next;
            current->next = temp->next; temp->next = current;
        }
        current = nextNode; 
    }
    list->head = sorted; 
}

// ========================================================
// 2. BINARY SEARCH TREE & INORDER TRAVERSAL
// ========================================================
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

void kumpulkanMateriInorder(BSTNode* node, int filterKatId, int maxDurasi, int maxSulit, Materi* arr[], int* count) {
    if (node == NULL) return;
    kumpulkanMateriInorder(node->left, filterKatId, maxDurasi, maxSulit, arr, count);     
    if (node->data.kategoriId == filterKatId && node->data.durasiMenit <= maxDurasi && node->data.tingkatKesulitan <= maxSulit) {
        arr[*count] = &(node->data); (*count)++;
    }
    kumpulkanMateriInorder(node->right, filterKatId, maxDurasi, maxSulit, arr, count);    
}

// ========================================================
// 3. GENERAL TREE (Sistem Kategori)
// ========================================================
typedef struct TreeNode { int idKategori; char namaKategori[100]; int numChildren; struct TreeNode* children[MAX_CHILDREN]; } TreeNode;
TreeNode* buatNodeTree(int id, const char* nama) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->idKategori = id; strcpy(newNode->namaKategori, nama); newNode->numChildren = 0; return newNode;
}
void addChild(TreeNode* parent, TreeNode* child) {
    if (parent->numChildren < MAX_CHILDREN) { parent->children[parent->numChildren++] = child; }
}

// ========================================================
// FUNGSI UI UX BERSAMA (Tabel Pilihan)
// ========================================================
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
void preorderTraversalBST(BSTNode* node, const char* prefix) {
    if (node == NULL) return;
    printf(" %s|-- %s (Kesulitan: %d)\n", prefix, node->data.nama, node->data.tingkatKesulitan);
    char newPrefix[100]; strcpy(newPrefix, prefix); strcat(newPrefix, "    ");
    preorderTraversalBST(node->left, newPrefix);
    preorderTraversalBST(node->right, newPrefix);
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
    addChild(soshum, buatNodeTree(10, "Ekonomi")); addChild(soshum, buatNodeTree(11, "Sosiologi"));

    // --- SETUP BST MATERI ---
    rootBST = insertBST(rootBST, buatMateri(1, "Tree & BST", "Hirarki data non-linear.", 50, 45)); rootBST = insertBST(rootBST, buatMateri(1, "Logika Dasar", "Fondasi algoritma.", 10, 30)); rootBST = insertBST(rootBST, buatMateri(1, "Array 1 Dimensi", "Memori sekuensial.", 20, 25)); rootBST = insertBST(rootBST, buatMateri(1, "Linked List", "Pointer data dinamis.", 30, 60)); rootBST = insertBST(rootBST, buatMateri(1, "Graph Theory", "Rute Dijkstra.", 80, 90));
    rootBST = insertBST(rootBST, buatMateri(2, "Trigonometri", "Sin, Cos, Tan.", 45, 40)); rootBST = insertBST(rootBST, buatMateri(2, "Aritmatika Dasar", "Plus & Minus.", 15, 20)); rootBST = insertBST(rootBST, buatMateri(2, "Aljabar Linear", "Matriks.", 35, 60)); rootBST = insertBST(rootBST, buatMateri(2, "Kalkulus Lanjut", "Integral.", 60, 90)); rootBST = insertBST(rootBST, buatMateri(2, "Probabilitas", "Peluang.", 70, 75));
    rootBST = insertBST(rootBST, buatMateri(3, "Genetika Kromosom", "Pewarisan sifat.", 45, 50)); rootBST = insertBST(rootBST, buatMateri(3, "Anatomi Sel", "Bagian sel.", 15, 30)); rootBST = insertBST(rootBST, buatMateri(3, "Ekosistem", "Rantai makanan.", 30, 40)); rootBST = insertBST(rootBST, buatMateri(3, "Evolusi Manusia", "Asal usul.", 75, 60)); rootBST = insertBST(rootBST, buatMateri(3, "Sistem Saraf", "Otak & impuls.", 85, 80));
    rootBST = insertBST(rootBST, buatMateri(4, "Hukum Newton", "Gaya & gerak.", 25, 45)); rootBST = insertBST(rootBST, buatMateri(4, "Kinematika", "Kecepatan.", 35, 50)); rootBST = insertBST(rootBST, buatMateri(4, "Optik Geometri", "Cermin.", 55, 60)); rootBST = insertBST(rootBST, buatMateri(4, "Termodinamika", "Kalor.", 65, 80)); rootBST = insertBST(rootBST, buatMateri(4, "Fisika Kuantum", "Sub-atomik.", 95, 120));
    rootBST = insertBST(rootBST, buatMateri(5, "Perang Dingin", "Blok Barat Timur.", 50, 40)); rootBST = insertBST(rootBST, buatMateri(5, "Manusia Purba", "Zaman batu.", 15, 25)); rootBST = insertBST(rootBST, buatMateri(5, "Perang Dunia II", "Eropa 1940an.", 20, 30)); rootBST = insertBST(rootBST, buatMateri(5, "Kemerdekaan RI", "1945.", 30, 35)); rootBST = insertBST(rootBST, buatMateri(5, "Revolusi Industri", "Eropa abad 18.", 40, 45));
    rootBST = insertBST(rootBST, buatMateri(6, "Asam & Basa", "Skala pH.", 50, 45)); rootBST = insertBST(rootBST, buatMateri(6, "Tabel Periodik", "Unsur dasar.", 20, 30)); rootBST = insertBST(rootBST, buatMateri(6, "Ikatan Kimia", "Kovalen Ionik.", 40, 40)); rootBST = insertBST(rootBST, buatMateri(6, "Stoikiometri", "Mol.", 60, 70)); rootBST = insertBST(rootBST, buatMateri(6, "Kimia Organik", "Karbon.", 80, 90));

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
        printf(" Pilih menu (0-3): "); scanf("%d", &pilihanUtama); bersihkanBuffer();

        switch (pilihanUtama) {
case 1: { 
                bool inKatalog = true;
                while (inKatalog) {
                    printf("\n=== KATALOG PELAJARAN ===\n");
                    for (int i = 0; i < menuRoot->children[0]->numChildren; i++) printf(" %d. %s\n", menuRoot->children[0]->children[i]->idKategori, menuRoot->children[0]->children[i]->namaKategori);
                    for (int i = 0; i < menuRoot->children[1]->numChildren; i++) printf(" %d. %s\n", menuRoot->children[1]->children[i]->idKategori, menuRoot->children[1]->children[i]->namaKategori);
                    printf(" 7. [Mode Admin] Visualisasi Struktur Memori BST (Preorder)\n");
                    printf(" 0. Kembali ke menu utama\n Pilih (0-7): ");
                    int pilKat; scanf("%d", &pilKat); bersihkanBuffer();

                    if (pilKat == 0) inKatalog = false;
                    else if (pilKat == 7) {
                        printf("\n=== VISUALISASI STRUKTUR DATABASE (PREORDER) ===\n Menampilkan susunan asli memori BST untuk keperluan Data Serialization.\n --------------------------------------------------------\n");
                        preorderTraversalBST(rootBST, "");
                        printf("\n Tekan [Enter] untuk kembali..."); getchar();
                    }
                    else if (pilKat >= 1 && pilKat <= 6) {
                        Materi* arrTemp[50]; int count = 0;
                        kumpulkanMateriInorder(rootBST, pilKat, 9999, 9999, arrTemp, &count);
                        printf("\n Menampilkan materi terpilih:"); prosesPilihMateri(arrTemp, count, &daftarBelajar);
                    } else printf(" [-] Pilihan tidak valid!\n");
                }
                break;
            }
            case 2: { 
                bool inRekomendasi = true;
                while (inRekomendasi) {
                    printf("\n=== SISTEM REKOMENDASI ===\n");
                    for (int i = 0; i < menuRoot->children[0]->numChildren; i++) {
                        printf(" %d. %s\n", menuRoot->children[0]->children[i]->idKategori, menuRoot->children[0]->children[i]->namaKategori);
                    }
                    for (int i = 0; i < menuRoot->children[1]->numChildren; i++) {
                        printf(" %d. %s\n", menuRoot->children[1]->children[i]->idKategori, menuRoot->children[1]->children[i]->namaKategori);
                    }
                    printf(" 0. Kembali\n Pelajaran apa yang ingin dicari? (0-6): ");
                    int pilPelajaran; scanf("%d", &pilPelajaran); bersihkanBuffer();

                    if (pilPelajaran == 0) inRekomendasi = false;
                    else if (pilPelajaran >= 1 && pilPelajaran <= 6) {
                        int batasWaktu, batasSulit;
                        printf(" Maksimal waktu belajar (menit) : "); scanf("%d", &batasWaktu);
                        printf(" Maksimal kesulitan (1-100)     : "); scanf("%d", &batasSulit); bersihkanBuffer();

                        Materi* arrTemp[50]; int count = 0;
                        kumpulkanMateriInorder(rootBST, pilPelajaran, batasWaktu, batasSulit, arrTemp, &count);
                        printf("\n Rekomendasi materi untukmu:");
                        prosesPilihMateri(arrTemp, count, &daftarBelajar);
                    } else printf(" [-] Pilihan tidak valid!\n");
                }
                break;
            }
            case 3: { 
                bool inDaftar = true;
                while (inDaftar) {
                    printf("\n=== DAFTAR BELAJARKU ===\n");
                    tampilkanPlaylist(&daftarBelajar);
                    
                    if (daftarBelajar.head == NULL) {
                        printf("\n Tekan [Enter] untuk kembali..."); getchar();
                        inDaftar = false;
                        break;
                    }

                    printf("\n Aksi:\n");
                    printf(" 1. Urutkan berdasarkan waktu tercepat\n");
                    printf(" 2. Urutkan berdasarkan tingkat kesulitan terendah\n");
                    printf(" 0. Kembali ke menu sebelumnya\n");
                    printf(" Pilih (0-2): ");
                    
                    int aksi; scanf("%d", &aksi); bersihkanBuffer();

                    if (aksi == 0) {
                        inDaftar = false;
                    } else if (aksi == 1) {
                        insertionSortByDurasi(&daftarBelajar);
                        printf("\n [+] Diurutkan berdasarkan WAKTU!\n");
                    } else if (aksi == 2) {
                        insertionSortByKesulitan(&daftarBelajar);
                        printf("\n [+] Diurutkan berdasarkan KESULITAN!\n");
                    } else {
                        printf(" [-] Pilihan tidak valid!\n");
                    }
                }
                break;
            }
            case 0: printf("\n Terima kasih telah menggunakan EduGraph. Sampai jumpa!\n"); running = false; break;
            default: printf("\n [-] Pilihan tidak valid. Silakan coba lagi.\n");
        }
    }
    return 0;
}