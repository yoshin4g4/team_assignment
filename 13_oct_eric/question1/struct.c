#include <stdio.h>
#include <string.h>

// Union untuk menyimpan detail Buku atau Majalah
union Media {
    char buku[50];     // contoh: kategori buku
    char majalah[50];  // contoh: edisi majalah
};

// Struct utama untuk item koleksi
struct Koleksi {
    char judul[100];   // Judul koleksi
    int tahunTerbit;   // Tahun terbit
    int jenisMedia;    // 1 = Buku, 2 = Majalah
    union Media media; // Union untuk detail
};


// Kenapa Union lebih hemat memori, karena Union menyimpan salah satu field(buku atau majalah), bukan keduanya
// Jika pakai struct biasa, setiap item akan menyimpan ruang untuk buku + majalah meski hanya salah satunya yang dipakai.

// Fungsi untuk menampilkan data
void tampilkan(struct Koleksi k) {
    printf("Judul       : %s\n", k.judul);
    printf("Tahun Terbit: %d\n", k.tahunTerbit);
    if (k.jenisMedia == 1) {
        printf("Jenis Media : Buku\n");
        printf("Kategori    : %s\n", k.media.buku);
    } else if (k.jenisMedia == 2) {
        printf("Jenis Media : Majalah\n");
        printf("Edisi       : %s\n", k.media.majalah);
    }
    printf("-----------------------------\n");
}

// Fungsi bubble sort berdasarkan tahun terbit
void urutkan(struct Koleksi arr[], int n) {
    int i, j;
    struct Koleksi temp;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (arr[j].tahunTerbit > arr[j+1].tahunTerbit) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main() {
    int n, i;
    printf("Masukkan jumlah koleksi: ");
    scanf("%d", &n);
    getchar(); // buang newline

    struct Koleksi koleksi[n];

    // Input data
    for (i = 0; i < n; i++) {
        printf("\nData ke-%d\n", i+1);
        printf("Judul: ");
        fgets(koleksi[i].judul, sizeof(koleksi[i].judul), stdin);
        koleksi[i].judul[strcspn(koleksi[i].judul, "\n")] = 0;

        printf("Tahun Terbit: ");
        scanf("%d", &koleksi[i].tahunTerbit);
        getchar();

        printf("Jenis Media (1 = Buku, 2 = Majalah): ");
        scanf("%d", &koleksi[i].jenisMedia);
        getchar();

        if (koleksi[i].jenisMedia == 1) {
            printf("Kategori Buku: ");
            fgets(koleksi[i].media.buku, sizeof(koleksi[i].media.buku), stdin);
            koleksi[i].media.buku[strcspn(koleksi[i].media.buku, "\n")] = 0;
        } else {
            printf("Edisi Majalah: ");
            fgets(koleksi[i].media.majalah, sizeof(koleksi[i].media.majalah), stdin);
            koleksi[i].media.majalah[strcspn(koleksi[i].media.majalah, "\n")] = 0;
        }
    }

    // Urutkan berdasarkan tahun
    urutkan(koleksi, n);

    // Tampilkan hasil
    printf("\n=== Koleksi Perpustakaan (Urut Tahun) ===\n");
    for (i = 0; i < n; i++) {
        tampilkan(koleksi[i]);
    }

    return 0;
}