// File: tugas2b.c
#include <stdio.h>
#include <string.h>

int main() {
    // Deklarasi variabel yang dibutuhkan
    char nip[15];
    char golongan[3];
    int jam_lembur;
    long int gaji_pokok = 0;
    long int tarif_lembur = 0;
    long int total_gaji;

    // --- PROSES INPUT ---
    // Menerima input NIP, Golongan, dan Jam Lembur 
    printf("Masukkan NIP Pegawai   : ");
    scanf("%s", nip);

    printf("Masukkan Golongan (D1/D2/D3) : ");
    scanf("%s", golongan);

    printf("Masukkan Jumlah Jam Lembur   : ");
    scanf("%d", &jam_lembur);

    // --- PROSES PERHITUNGAN ---
    // Menentukan Gaji Pokok dan Tarif Lembur berdasarkan Golongan
    // Menggunakan if-else untuk percabangan kondisi
    if (strcmp(golongan, "D1") == 0) {
        gaji_pokok = 3000000;   // Sesuai tabel 
        tarif_lembur = 15000;  // Sesuai tabel 
    } else if (strcmp(golongan, "D2") == 0) {
        gaji_pokok = 2500000;   // Sesuai tabel 
        tarif_lembur = 10000;  // Sesuai tabel 
    } else if (strcmp(golongan, "D3") == 0) {
        gaji_pokok = 2000000;   // Sesuai tabel 
        tarif_lembur = 5000;   // Sesuai tabel 
    } else {
        printf("\nGolongan tidak valid!\n");
        return 1; // Keluar dari program jika golongan salah
    }

    // Menghitung total gaji sesuai rumus yang diberikan 
    total_gaji = gaji_pokok + (jam_lembur * tarif_lembur);

    // --- TAMPILAN OUTPUT ---
    // Menampilkan rincian gaji bulan ini 
    printf("\n--- Rincian Gaji Bulan Ini ---\n");
    printf("NIP                : %s\n", nip);
    printf("Golongan           : %s\n", golongan);
    printf("Jam Lembur         : %d jam\n", jam_lembur);
    printf("Gaji Pokok         : Rp%ld\n", gaji_pokok);
    printf("Upah Lembur        : Rp%ld\n", jam_lembur * tarif_lembur);
    printf("----------------------------------\n");
    printf("Total Gaji Bulan Ini = Rp%ld\n", total_gaji);

    return 0;
}
