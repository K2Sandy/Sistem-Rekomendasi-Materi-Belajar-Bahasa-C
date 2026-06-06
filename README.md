<div align="center">

# 🎓 EduGraph
### Sistem Rekomendasi Alur Belajar Berbasis Struktur Data Hibrida

<br>

![C](https://img.shields.io/badge/Language-C11-00599C?style=for-the-badge&logo=c&logoColor=white)
![Status](https://img.shields.io/badge/Status-UTS%20Project-success?style=for-the-badge)
![License](https://img.shields.io/badge/License-Academic-orange?style=for-the-badge)
![Universitas](https://img.shields.io/badge/Universitas-Syiah%20Kuala-blueviolet?style=for-the-badge)

<br>

> **EduGraph** adalah aplikasi berbasis Command Line Interface (CLI) yang membantu pengguna menyusun materi belajar secara terstruktur berdasarkan kategori, tingkat kesulitan, dan durasi belajar. Sistem ini menggabungkan beberapa struktur data dalam satu implementasi untuk mensimulasikan proses pencarian, rekomendasi, dan pengelolaan materi pembelajaran. Pengguna dapat memilih materi dari katalog yang tersedia, menerima rekomendasi berdasarkan batas waktu dan tingkat kesulitan, serta menyusun daftar belajar pribadi yang dapat diurutkan sesuai kebutuhan.
<br>

</div>

---


## ✨ Fitur Utama

| # | Fitur | Deskripsi |
|:---:|---|---|
| 1 | 📚 **Katalog Silabus Bertingkat** | Navigasi hirarki 3 level: Rumpun Ilmu → Mata Pelajaran → Materi |
| 2 | 🤖 **Rekomendasi Cerdas** | Filter materi berdasarkan batas waktu & tingkat kesulitan secara otomatis |
| 3 | 📋 **Daftar Belajarku** | Daftar belajar dinamis berbasis Linked List untuk menyimpan materi pilihan pengguna |
| 4 | ⚡ **Smart Sorting** | Urutkan playlist berdasarkan durasi tercepat atau kesulitan termudah |
| 5 | 🗺️ **Mode Peta Silabus** | Visualisasi seluruh pohon materi BST secara *real-time* (Preorder) |

---

## 🛠 Arsitektur Sistem

Sistem mengintegrasikan **3 struktur data**
dan **3 algoritma utama** untuk mendukung
fitur katalog materi, rekomendasi belajar,
dan pengelolaan daftar belajar pengguna.

### 🌳 Struktur Data

| Struktur | Peran | Kompleksitas |
|---|---|:---:|
| **General Tree** | Mengelola kategori berjenjang (Root → Rumpun → Mapel) | O(n) |
| **Binary Search Tree** | Menyimpan materi berdasarkan tingkat kesulitan dan mendukung proses traversal | O(log n) |
| **Linked List** | Wadah Daftar Belajar dengan alokasi memori dinamis | O(1) |

### ⚙️ Algoritma

| Algoritma | Implementasi | Kegunaan |
|---|---|---|
| **Inorder Traversal** | BST → kiri, root, kanan | Menampilkan materi dari tingkat kesulitan terendah ke tertinggi |
| **Insertion Sort** | Linked List | Mengurutkan daftar belajar berdasarkan durasi |
| **Insertion Sort** | Linked List | Mengurutkan daftar belajar berdasarkan tingkat kesulitan |
| **Preorder Traversal** | BST → root, kiri, kanan | Visualisasi struktur BST pada Mode Admin |
---

## 💻 Cara Menjalankan

### Prasyarat

Pastikan *compiler* GCC telah terinstal: Windows (MinGW-w64), Linux (`build-essential`), atau macOS (`xcode-select --install`).

### Langkah Instalasi & Kompilasi

Proyek ini menyediakan dua versi kode: **allinone** (seluruh kode dalam satu file) dan **bagian** (kode modular yang dipisah dengan *header*). 

Jalankan perintah berikut di terminal secara berurutan:

```bash
# 1. Clone repositori
git clone https://github.com/username/UTS-PRAK-SDA-KELOMPOK-1.git
cd UTS-PRAK-SDA-KELOMPOK-1

# 2. Kompilasi (Pilih salah satu versi kode yang ingin digunakan)

# ---> Opsi A: Versi All-in-One (satu file)
cd code/allinone
gcc -Wall -std=c11 main.c -o edugraph

# ---> Opsi B: Versi Modular (banyak file)
cd code/bagian
gcc -Wall -std=c11 main.c materi.c linked_list.c bst.c tree.c ui.c -o edugraph

# 3. Jalankan program
./edugraph      # Untuk Linux / macOS
.\edugraph.exe  # Untuk Windows
```

---

---

## 🖥️ Tampilan Program

### Menu Utama

```text
======================================================
         SISTEM ASISTEN BELAJAR EDUGRAPH
======================================================
 1. Katalog & Silabus Pelajaran
 2. Sistem Rekomendasi Belajar (Filter Cerdas)
 3. Lihat Daftar Belajarku
 0. Keluar Aplikasi
======================================================
 Pilih menu (0-3):
```

## 👥 Tim Pengembang

EduGraph dikembangkan secara kolaboratif oleh Mahasiswa **S1 Informatika**, Fakultas Matematika dan Ilmu Pengetahuan Alam, **Universitas Syiah Kuala** sebagai proyek UTS Praktikum Struktur Data dan Algoritma.

<div align="center">

| Nama | Kontribusi Utama |
|--------|----------------|
| Muhammad Albharaka | Implementasi General Tree dan sistem menu |
| Putroe Zalfa | Implementasi BST dan Traversal |
| Al Aul Tsaqif | Implementasi Linked List |
| Imam As-Shadiq | Implementasi Sorting dan Sistem Rekomendasi |
| Hally Lubbaba | Dokumentasi, Pengujian Program, dan README |

</div>


<div align="center">

*Dibuat dengan ❤️ oleh Kelompok 1 — Informatika, Universitas Syiah Kuala*

</div>
