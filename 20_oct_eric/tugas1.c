#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NAMA 50
#define MAX_NOMOR_REG 15
#define FILENAME "siswa.txt"
#define DELIMITER "|"

// Struktur data siswa
typedef struct {
    char nomor_registrasi[MAX_NOMOR_REG];
    char nama[MAX_NAMA];
    int umur;
} Siswa;

// Fungsi untuk membersihkan newline character
void clean_input(char *str) {
    int len = strlen(str);
    if (len > 0 && str[len-1] == '\n') {
        str[len-1] = '\0';
    }
}

// Fungsi untuk menampilkan menu
void tampilkan_menu() {
    printf("\n=== SISTEM MANAJEMEN DATABASE SISWA ===\n");
    printf("1. Tambah Data Siswa\n");
    printf("2. Hapus Data Siswa\n");
    printf("3. Cari Data Siswa\n");
    printf("4. Tampilkan Semua Data\n");
    printf("5. Keluar\n");
    printf("Pilihan Anda: ");
}

// Fungsi untuk validasi nomor registrasi (harus unik)
int is_nomor_registrasi_unik(const char *nomor_reg) {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        return 1; // File tidak ada, jadi nomor dianggap unik
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char stored_nomor[MAX_NOMOR_REG];
        sscanf(line, "%[^|]", stored_nomor);

        if (strcmp(stored_nomor, nomor_reg) == 0) {
            fclose(file);
            return 0; // Nomor sudah ada
        }
    }

    fclose(file);
    return 1; // Nomor unik
}

// Fungsi menambah data siswa
void tambah_siswa() {
    Siswa siswa;

    printf("\n--- TAMBAH DATA SISWA ---\n");

    // Input nomor registrasi
    printf("Nomor Registrasi: ");
    fgets(siswa.nomor_registrasi, MAX_NOMOR_REG, stdin);
    clean_input(siswa.nomor_registrasi);

    // Validasi nomor registrasi unik
    if (!is_nomor_registrasi_unik(siswa.nomor_registrasi)) {
        printf("Error: Nomor registrasi sudah ada!\n");
        return;
    }

    // Input nama
    printf("Nama: ");
    fgets(siswa.nama, MAX_NAMA, stdin);
    clean_input(siswa.nama);

    // Input umur
    printf("Umur: ");
    char umur_str[10];
    fgets(umur_str, sizeof(umur_str), stdin);
    siswa.umur = atoi(umur_str);

    // Validasi umur
    if (siswa.umur <= 0 || siswa.umur > 100) {
        printf("Error: Umur tidak valid!\n");
        return;
    }

    // Buka file untuk append
    FILE *file = fopen(FILENAME, "a");
    if (file == NULL) {
        printf("Error: Gagal membuka file!\n");
        return;
    }

    // Tulis data ke file
    fprintf(file, "%s%s%s%s%d\n",
            siswa.nomor_registrasi, DELIMITER,
            siswa.nama, DELIMITER,
            siswa.umur);

    fclose(file);
    printf("Data siswa berhasil ditambahkan!\n");
}

// Fungsi menghapus data siswa
void hapus_siswa() {
    char nomor_hapus[MAX_NOMOR_REG];

    printf("\n--- HAPUS DATA SISWA ---\n");
    printf("Nomor Registrasi yang akan dihapus: ");
    fgets(nomor_hapus, MAX_NOMOR_REG, stdin);
    clean_input(nomor_hapus);

    // Buka file sumber untuk dibaca
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Error: File tidak ditemukan atau gagal dibuka!\n");
        return;
    }

    // Buka file sementara untuk menulis
    FILE *temp_file = fopen("temp.txt", "w");
    if (temp_file == NULL) {
        printf("Error: Gagal membuat file sementara!\n");
        fclose(file);
        return;
    }

    char line[256];
    int ditemukan = 0;
    int data_count = 0;

    // Alokasi memori dinamis untuk menyimpan data
    Siswa *data_siswa = NULL;
    int kapasitas = 10;
    data_siswa = (Siswa*)malloc(kapasitas * sizeof(Siswa));

    if (data_siswa == NULL) {
        printf("Error: Alokasi memori gagal!\n");
        fclose(file);
        fclose(temp_file);
        return;
    }

    // Baca semua data dari file
    while (fgets(line, sizeof(line), file)) {
        Siswa s;
        sscanf(line, "%[^|]|%[^|]|%d",
               s.nomor_registrasi, s.nama, &s.umur);

        // Jika data tidak sama dengan yang akan dihapus, simpan
        if (strcmp(s.nomor_registrasi, nomor_hapus) != 0) {
            // Perluas array jika diperlukan
            if (data_count >= kapasitas) {
                kapasitas *= 2;
                Siswa *new_data = (Siswa*)realloc(data_siswa, kapasitas * sizeof(Siswa));
                if (new_data == NULL) {
                    printf("Error: Alokasi memori ulang gagal!\n");
                    free(data_siswa);
                    fclose(file);
                    fclose(temp_file);
                    return;
                }
                data_siswa = new_data;
            }

            // Simpan data ke array
            strcpy(data_siswa[data_count].nomor_registrasi, s.nomor_registrasi);
            strcpy(data_siswa[data_count].nama, s.nama);
            data_siswa[data_count].umur = s.umur;
            data_count++;
        } else {
            ditemukan = 1;
        }
    }

    fclose(file);

    // Tulis data yang tersisa ke file sementara
    for (int i = 0; i < data_count; i++) {
        fprintf(temp_file, "%s%s%s%s%d\n",
                data_siswa[i].nomor_registrasi, DELIMITER,
                data_siswa[i].nama, DELIMITER,
                data_siswa[i].umur);
    }

    fclose(temp_file);
    free(data_siswa);

    // Hapus file lama dan ganti dengan yang baru
    if (ditemukan) {
        remove(FILENAME);
        rename("temp.txt", FILENAME);
        printf("Data dengan nomor registrasi %s berhasil dihapus!\n", nomor_hapus);
    } else {
        remove("temp.txt");
        printf("Data dengan nomor registrasi %s tidak ditemukan!\n", nomor_hapus);
    }
}

// Fungsi untuk menampilkan data siswa
void tampilkan_siswa(const Siswa *s) {
    printf("Nomor Registrasi: %s\n", s->nomor_registrasi);
    printf("Nama: %s\n", s->nama);
    printf("Umur: %d\n", s->umur);
    printf("----------------------------\n");
}

// Fungsi mencari data siswa
void cari_siswa() {
    int pilihan;
    char kata_kunci[100];

    printf("\n--- CARI DATA SISWA ---\n");
    printf("1. Berdasarkan Nomor Registrasi\n");
    printf("2. Berdasarkan Nama\n");
    printf("3. Berdasarkan Umur\n");
    printf("Pilihan: ");

    char pilihan_str[10];
    fgets(pilihan_str, sizeof(pilihan_str), stdin);
    pilihan = atoi(pilihan_str);

    if (pilihan < 1 || pilihan > 3) {
        printf("Pilihan tidak valid!\n");
        return;
    }

    printf("Kata kunci: ");
    fgets(kata_kunci, sizeof(kata_kunci), stdin);
    clean_input(kata_kunci);

    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Error: File tidak ditemukan!\n");
        return;
    }

    char line[256];
    int ditemukan = 0;

    printf("\n--- HASIL PENCARIAN ---\n");

    while (fgets(line, sizeof(line), file)) {
        Siswa s;
        sscanf(line, "%[^|]|%[^|]|%d",
               s.nomor_registrasi, s.nama, &s.umur);

        int cocok = 0;

        switch (pilihan) {
            case 1: // Nomor registrasi
                if (strcmp(s.nomor_registrasi, kata_kunci) == 0) {
                    cocok = 1;
                }
                break;

            case 2: // Nama (case insensitive partial match)
                {
                    char nama_lower[MAX_NAMA];
                    char kata_kunci_lower[100];

                    // Convert to lowercase untuk pencarian case insensitive
                    for (int i = 0; s.nama[i]; i++) {
                        nama_lower[i] = tolower(s.nama[i]);
                    }
                    nama_lower[strlen(s.nama)] = '\0';

                    for (int i = 0; kata_kunci[i]; i++) {
                        kata_kunci_lower[i] = tolower(kata_kunci[i]);
                    }
                    kata_kunci_lower[strlen(kata_kunci)] = '\0';

                    if (strstr(nama_lower, kata_kunci_lower) != NULL) {
                        cocok = 1;
                    }
                }
                break;

            case 3: // Umur
                if (s.umur == atoi(kata_kunci)) {
                    cocok = 1;
                }
                break;
        }

        if (cocok) {
            tampilkan_siswa(&s);
            ditemukan = 1;
        }
    }

    fclose(file);

    if (!ditemukan) {
        printf("Data tidak ditemukan!\n");
    }
}

// Fungsi menampilkan semua data
void tampilkan_semua_data() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Error: File tidak ditemukan!\n");
        return;
    }

    char line[256];
    int count = 0;

    printf("\n--- SEMUA DATA SISWA ---\n");

    while (fgets(line, sizeof(line), file)) {
        Siswa s;
        sscanf(line, "%[^|]|%[^|]|%d",
               s.nomor_registrasi, s.nama, &s.umur);

        tampilkan_siswa(&s);
        count++;
    }

    fclose(file);

    if (count == 0) {
        printf("Tidak ada data siswa.\n");
    } else {
        printf("Total data: %d\n", count);
    }
}

// Fungsi utama
int main() {
    int running = 1;

    printf("SISTEM MANAJEMEN DATABASE SISWA\n");
    printf("File database: %s\n", FILENAME);

    while (running) {
        tampilkan_menu();

        char input[10];
        fgets(input, sizeof(input), stdin);
        int pilihan = atoi(input);

        switch (pilihan) {
            case 1:
                tambah_siswa();
                break;
            case 2:
                hapus_siswa();
                break;
            case 3:
                cari_siswa();
                break;
            case 4:
                tampilkan_semua_data();
                break;
            case 5:
                running = 0;
                printf("Terima kasih! Program dihentikan.\n");
                break;
            default:
                printf("Pilihan tidak valid! Silakan coba lagi.\n");
        }
    }

    return 0;
}

BEGIN TambahSiswa
    INPUT nama, umur, nomor_registrasi
    BUAT string data = nomor_registrasi + "|" + nama + "|" + umur + "\n"
    BUKA file "siswa.txt" dalam mode APPEND
    IF file berhasil dibuka THEN
        TULIS data ke file
        TUTUP file
        TAMPILKAN "Data berhasil ditambahkan"
    ELSE
        TAMPILKAN "Error: Gagal membuka file"
    END IF
END

BEGIN HapusSiswa
    INPUT nomor_registrasi_hapus
    BUKA file "siswa.txt" dalam mode READ
    BUAT array sementara data_siswa[]

    WHILE belum EOF DO
        BACA baris dari file
        SPLIT baris dengan delimiter "|"
        IF nomor_registrasi ≠ nomor_registrasi_hapus THEN
            TAMBAH ke data_siswa[]
        END IF
    END WHILE
    TUTUP file

    BUKA file "siswa.txt" dalam mode WRITE
    FOR setiap data dalam data_siswa[] DO
        TULIS data ke file
    END FOR
    TUTUP file
    TAMPILKAN "Data berhasil dihapus"
END


BEGIN HapusSiswa
    INPUT nomor_registrasi_hapus
    BUKA file "siswa.txt" dalam mode READ
    BUAT array sementara data_siswa[]

    WHILE belum EOF DO
        BACA baris dari file
        SPLIT baris dengan delimiter "|"
        IF nomor_registrasi ≠ nomor_registrasi_hapus THEN
            TAMBAH ke data_siswa[]
        END IF
    END WHILE
    TUTUP file

    BUKA file "siswa.txt" dalam mode WRITE
    FOR setiap data dalam data_siswa[] DO
        TULIS data ke file
    END FOR
    TUTUP file
    TAMPILKAN "Data berhasil dihapus"
END
