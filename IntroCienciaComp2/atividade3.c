#include <stdio.h>
#include <stdlib.h>

void merge(int arr[], int l, int m, int r, int *trocas, int *comparacoes)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
 
    int L[n1], R[n2];
 
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
 

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        *comparacoes = *comparacoes + 1;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
            
        }
        *trocas = *trocas + 1;
        k++;
        
    }
 
    while (i < n1) {
        arr[k] = L[i];
        *trocas = *trocas + 1;
        i++;
        k++;
    }
 
    
    while (j < n2) {
        arr[k] = R[j];
      *trocas = *trocas + 1;
        j++;
        k++;
    }

    k = 0;
    for(int z = l; z <= r; z++, k++) {
      *trocas = *trocas + 1;
      R[z] = arr[z];
      
    }
    
  
}

void mergeSort(int arr[], int l, int r, int *trocas, int *comparacoes)
{   
    
    if (l < r) {
        int m = l + (r - l) / 2;
 
        // Sort first and second halves
        mergeSort(arr, l, m, trocas, comparacoes);
        mergeSort(arr, m + 1, r, trocas, comparacoes);
 
        merge(arr, l, m, r, trocas, comparacoes);
    }
    
    
}

void insertionSort(int arr[], int n)
{
    int trocas = 0, comparacoes = 0;
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        trocas++;
 
        
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
            trocas++;
            comparacoes++;
        }
        if(j >= 0 && key >= arr[j]){
          comparacoes++;
        }
        arr[j + 1] = key;
        trocas++;
    }
    printf("I %d %d %d\n", n, trocas, comparacoes);
}

int main () {
  int q;
  scanf("%d", &q);

  int* sizes = (int*) malloc(q * sizeof(int));
  int** arrays = (int**) malloc(q * sizeof(int*));


  for (int i = 0; i < q; i++) {
        scanf("%d", &sizes[i]);
        arrays[i] = (int*) malloc(sizes[i] * sizeof(int));
    }

  for(int i = 0; i < q; i++) {
    for(int j = 0; j < sizes[i]; j++) {
        scanf("%d", &arrays[i][j]);
      }
    }

    for(int i = 0; i < q; i++) {
        int* arrayTemp = (int*) malloc(sizes[i] * sizeof(int));
        for(int j = 0; j < sizes[i]; j++) {
            arrayTemp[j] = arrays[i][j];
        }

        insertionSort(arrays[i], sizes[i]);

        int mergeTrocas = 0, mergeComparacoes = 0;
        mergeSort(arrayTemp, 0, sizes[i] - 1, &mergeTrocas, &mergeComparacoes);
        printf("M %d %d %d\n", sizes[i], mergeTrocas, mergeComparacoes);
    }



}