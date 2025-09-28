// Pada kode di atas, bagian arr[j] > arr[i] membandingkan elemen pada indeks j dengan indeks i, tanpa memperhatikan urutan yang benar.
// Karena j selalu dimulai dari 0 hingga n, maka akan ada perbandingan terbalik yang menyebabkan hasil akhir tidak konsisten dan bukan urutan terurut.

#include <stdio.h>

void sort(int arr[], int n)
{
  int i, j, temp;
  for (i = 0; i < n - 1; i++)
  {
    for (j = 0; j < n - i - 1; j++)
    { // j < n-i-1
      if (arr[j] > arr[j + 1])
      { // swap jika urutan salah
        temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
}

int main()
{
  int arr[] = {64, 34, 25, 12, 22};
  int n = sizeof(arr) / sizeof(arr[0]);
  sort(arr, n);
  for (int i = 0; i < n; i++)
  {
    printf("%d ", arr[i]);
  }
  return 0;
}
