#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_CHILDREN 10

// ========================================================
// 0. STRUKTUR DATA UTAMA
// ========================================================
typedef struct {
    int kategoriId; 
    char nama[50];
    char deskripsi[50];
    int tingkatKesulitan; 
    int durasiMenit;      
} Materi;

Materi buatMateri(int katId, const char* nama, const char* desk, int kesulitan, int durasi) {
    Materi m;
    m.kategoriId = katId;
    strcpy(m.nama, nama);
    strcpy(m.deskripsi, desk);
    m.tingkatKesulitan = kesulitan;
    m.durasiMenit = durasi;
    return m;
}

void bersihkanBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// ========================================================
// 1. LINKED LIST (Daftar Belajarku)
// ========================================================
typedef struct ListNode {
    Materi data;
    struct ListNode* next;
} ListNode;

typedef struct {
    ListNode* head;
} PlaylistLinkedList;

void initLinkedList(PlaylistLinkedList* list) { list->head = NULL; }

void tambahMateri(PlaylistLinkedList* list, Materi m) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->data = m;
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
        return;
    }
    ListNode* temp = list->head;
    while (temp->next != NULL) temp = temp->next;
    temp->next = newNode;
}

void tampilkanPlaylist(PlaylistLinkedList* list) {
    if (list->head == NULL) {
        printf("\n [-] Daftar belajarmu masih kosong.\n");
        return;
    }
    ListNode* temp = list->head;
    int no = 1;
    printf("\n =========================================================================\n");
    printf(" %-4s %-25s %-12s %-10s %s\n", "No", "Judul Materi", "Sulit(/100)", "Waktu", "Keterangan");
    printf(" -------------------------------------------------------------------------\n");
    while (temp != NULL) {
        printf(" %-4d %-25s %-12d %-10d %s\n", no++, temp->data.nama, 
               temp->data.tingkatKesulitan, temp->data.durasiMenit, temp->data.deskripsi);
        temp = temp->next;
    }
    printf(" =========================================================================\n");
}

// ========================================================
// PROGRAM UTAMA
// ========================================================
int main() {
    // Inisialisasi Linked List untuk Playlist
    PlaylistLinkedList daftarBelajar; 
    initLinkedList(&daftarBelajar);

    bool running = true;
    
    // --- MAIN LOOP ---
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
        scanf("%d", &pilihanUtama);
        bersihkanBuffer();

        switch (pilihanUtama) {
            case 1:
                printf("\n [-] Fitur Katalog masih dalam pengembangan.\n");
                break;
            case 2:
                printf("\n [-] Fitur Rekomendasi masih dalam pengembangan.\n");
                break;
            case 3:
                // Mengaktifkan Menu 3
                printf("\n=== DAFTAR BELAJARKU ===\n");
                tampilkanPlaylist(&daftarBelajar);
                break;
            case 0:
                printf("\n Terima kasih telah menggunakan EduGraph. Sampai jumpa!\n");
                running = false;
                break;
            default:
                printf("\n [-] Pilihan tidak valid. Silakan coba lagi.\n");
        }
    }
    return 0;
}