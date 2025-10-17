#include <stdio.h>
#include <string.h>

struct Pegawai
{
    char nip[20];
    char nama[50];
    char alamat[100];
    char no_hp[25];
    char jabatan[20];
    int golongan;
};

int gajiPokok(int golongan)
{
    switch (golongan)
    {
    case 1:
        return 2000000;
    case 2:
        return 3000000;
    case 3:
        return 4000000;
    default:
        return 0;
    }
}

int Lembur(int golongan)
{
    switch (golongan)
    {
    case 1:
        return 10000;
    case 2:
        return 15000;
    case 3:
        return 20000;
    default:
        return 0;
    }
}

void createPegawai()
{
    struct Pegawai p;
    // input

    printf("--- Input Data Pegawai ---\n");
    printf("NIP: ");
    scanf("%s", p.nip);
    printf("Nama: ");
    scanf(" %[^\n]", p.nama);
    printf("Alamat: ");
    scanf(" %[^\n]", p.alamat);
    printf("No HP: ");
    scanf("%s", p.no_hp);
    printf("Jabatan: ");
    scanf(" %[^\n]", p.jabatan);
    printf("Golongan (1/2/3): ");
    scanf("%d", &p.golongan);

    int gaji = gajiPokok(p.golongan);
    // output
    printf("\n--- Data Pegawai ---\n");
    printf("NIP      : %s\n", p.nip);
    printf("Nama     : %s\n", p.nama);
    printf("Alamat   : %s\n", p.alamat);
    printf("No HP    : %s\n", p.no_hp);
    printf("Jabatan  : %s\n", p.jabatan);

    // print golongan pegawai
    if (p.golongan >= 1 && p.golongan <= 3)
        printf("Golongan : D%d\n", p.golongan);
    else
        printf("Golongan : Tidak valid, mohon input golongan yang valid (1/2/3)\n");

    printf("Gaji Pokok: Rp %d\n", gaji);
}

int main()
{
    createPegawai();
    return 0;
}
