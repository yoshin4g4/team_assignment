// Online C compiler to run C program online
#include <stdio.h>
#include <string.h>

    

// Struktur data pegawai
struct Pegawai {
    char nip[20];
    char nama[50];
    char alamat[100];
    char no_hp[20];
    char jabatan[30];
    char golongan[3]; // D1, D2, D3
};

// Fungsi gaji pokok sesuai golongan
int gajiPokok(char golongan[]) {
    if (strcmp(golongan, "D1") == 0) return 2000000;
    if (strcmp(golongan, "D2") == 0) return 3000000;
    if (strcmp(golongan, "D3") == 0) return 4000000;
    return 0;
}

// Fungsi tarif lembur sesuai golongan
int tarifLembur(char golongan[]) {
    if (strcmp(golongan, "D1") == 0) return 10000;
    if (strcmp(golongan, "D2") == 0) return 15000;
    if (strcmp(golongan, "D3") == 0) return 20000;
    return 0;
}

void modul2A() {
    struct Pegawai p;
    printf("=== Input Data Pegawai ===\n");
    printf("NIP: "); scanf("%s", p.nip);
    printf("Nama: "); scanf(" %[^\n]", p.nama);
    printf("Alamat: "); scanf(" %[^\n]", p.alamat);
    printf("No HP: "); scanf("%s", p.no_hp);
    printf("Jabatan: "); scanf(" %[^\n]", p.jabatan);
    printf("Golongan (D1/D2/D3): "); scanf("%s", p.golongan);

    int gaji = gajiPokok(p.golongan);

    printf("\n=== Data Pegawai ===\n");
    printf("NIP      : %s\n", p.nip);
    printf("Nama     : %s\n", p.nama);
    printf("Alamat   : %s\n", p.alamat);
    printf("No HP    : %s\n", p.no_hp);
    printf("Jabatan  : %s\n", p.jabatan);
    printf("Golongan : %s\n", p.golongan);
    printf("Gaji Pokok: Rp %d\n", gaji);
}

// Modul 2B - Hitung gaji total dengan lembur
void modul2B() {
    char golongan[3];
    int jamLembur;
    printf("Golongan (D1/D2/D3): "); scanf("%s", golongan);

    int gaji = gajiPokok(golongan);
    int tarif = tarifLembur(golongan);

    printf("Masukkan jumlah jam lembur: ");
    scanf("%d", &jamLembur);

    int totalLembur = tarif * jamLembur;
    int totalGaji = gaji + totalLembur;

    printf("\n=== Perhitungan Gaji ===\n");
    printf("Gaji Pokok : Rp %d\n", gaji);
    printf("Upah Lembur: Rp %d\n", totalLembur);
    printf("Total Gaji : Rp %d\n", totalGaji);
}

// Modul 2C - Hitung hadiah belanja & diskon
void modul2C() {
    int totalBelanja;
    printf("Masukkan total pembelian: Rp ");
    scanf("%d", &totalBelanja);

    int kupon = totalBelanja / 100000;
    float diskon = 0;
    
    if (totalBelanja >= 100000) {
        diskon = 0.10 * totalBelanja; // pakai 10% supaya sama contoh
    }
    
    float totalBayar = totalBelanja - diskon;


    printf("\n=== Perhitungan Belanja ===\n");
    printf("Total Belanja : Rp %d\n", totalBelanja);
    printf("Jumlah Kupon  : %d lembar\n", kupon);
    printf("Diskon        : Rp %.0f\n", diskon);
    printf("Total Bayar   : Rp %.0f\n", totalBayar);
}

int main() {
    int pilihan;
    do {
        printf("\n=== Menu Program Supermarket Nusantara Sejahtera ===\n");
        printf("1. Modul 2A: Data Pegawai & Gaji Pokok\n");
        printf("2. Modul 2B: Hitung Gaji Bulanan\n");
        printf("3. Modul 2C: Hadiah Belanja & Diskon\n");
        printf("0. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);

        switch(pilihan) {
            case 1: modul2A(); break;
            case 2: modul2B(); break;
            case 3: modul2C(); break;
            case 0: printf("Terima kasih!\n"); break;
            default: printf("Pilihan tidak valid!\n");
        }
    } while(pilihan != 0);

    return 0;
}