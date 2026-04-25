# 🎓 EduGraph: Smart Learning Path Recommendation System

![C Programming](https://img.shields.io/badge/Language-C-blue.svg)
![Data Structure](https://img.shields.io/badge/Topic-Data%20Structures%20%26%20Algorithms-orange.svg)
![Status](https://img.shields.io/badge/Status-UTS%20Project-green.svg)
![Environment](https://img.shields.io/badge/Environment-Linux%20%2F%20Windows-lightgrey.svg)

**EduGraph** adalah aplikasi berbasis konsol yang dirancang untuk membantu mahasiswa mengelola alur belajar secara cerdas dan terstruktur. Menggunakan pendekatan **Struktur Data Hibrida**, aplikasi ini mampu memberikan rekomendasi materi yang dipersonalisasi berdasarkan ketersediaan waktu dan tingkat kesulitan yang diinginkan.

---

## 🚀 Fitur Utama

- **Katalog Pelajaran Bertingkat**: Menampilkan hirarki ilmu pengetahuan (Saintek/Soshum) menggunakan *General Tree*.
- **Rekomendasi Cerdas**: Memfilter ribuan materi di database menggunakan *Binary Search Tree* (BST) untuk hasil yang cepat dan otomatis terurut.
- **Daftar Belajar Dinamis (Playlist)**: Menyimpan antrean belajar pengguna menggunakan *Linked List*.
- **Multi-Sorting**: Mengurutkan daftar belajar berdasarkan durasi tercepat atau kesulitan terendah menggunakan algoritma *Insertion Sort*.
- **Mode Admin (Visualisasi Memori)**: Melihat susunan asli data di dalam RAM menggunakan *Preorder Traversal*.

---

## 🛠 Arsitektur Struktur Data

Proyek ini mengintegrasikan tiga struktur data utama untuk efisiensi maksimal:

1.  **General Tree**: Digunakan untuk mengelola kategori dan sub-kategori mata pelajaran.
2.  **Binary Search Tree (BST)**: Digunakan sebagai *Search Engine* materi. Memungkinkan pencarian dengan kompleksitas waktu **O(log n)**.
3.  **Linked List**: Digunakan untuk manajemen *playlist* karena sifatnya yang dinamis dalam penambahan data.

### Algoritma yang Digunakan:
- **Inorder Traversal**: Untuk mengekstraksi data dari BST agar otomatis urut (Ascending).
- **Preorder Traversal**: Untuk visualisasi hirarki dan kebutuhan *Data Serialization*.
- **Insertion Sort**: Untuk pengurutan ulang data pada *Linked List* berdasarkan input pengguna.

---

## 💻 Cara Menjalankan

### Prasyarat
Pastikan Anda sudah menginstal GCC Compiler (MinGW untuk Windows atau build-essential untuk Linux).

### Langkah-langkah
1. **Clone Repository**
   ```bash
   git clone [https://github.com/username/UTS-PRAK-SDA-KELOMPOK-1.git](https://github.com/username/UTS-PRAK-SDA-KELOMPOK-1.git)