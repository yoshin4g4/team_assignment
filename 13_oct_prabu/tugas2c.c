#include <stdio.h>
#include <math.h>

int main() {
    double total_pembelian;
    int jumlah_kupon;
    double nominal_diskon;
    double total_bayar;

    // Input total pembelian dengan validasi
    do {
        printf("Masukkan total pembelian (Rp): ");
        scanf("%lf", &total_pembelian);

        if (total_pembelian < 0) {
            printf("Error: Total pembelian tidak boleh negatif!\n");
        }
    } while (total_pembelian < 0);

    // Hitung jumlah kupon (floor untuk kelipatan 100.000)
    jumlah_kupon = (int)(total_pembelian / 100000);

    // Hitung diskon 5% jika minimal 100.000
    if (total_pembelian >= 100000) {
        nominal_diskon = total_pembelian * 0.05;
    } else {
        nominal_diskon = 0;
    }

    // Hitung total yang harus dibayar
    total_bayar = total_pembelian - nominal_diskon;

    // Tampilkan hasil
    printf("\n=== RINCIAN PEMBAYARAN ===\n");
    printf("Total pembelian awal: Rp%.2f\n", total_pembelian);
    printf("Jumlah kupon undian  : %d kupon\n", jumlah_kupon);
    printf("Nominal diskon       : Rp%.2f\n", nominal_diskon);
    printf("Total yang harus dibayar: Rp%.2f\n", total_bayar);

    return 0;
}