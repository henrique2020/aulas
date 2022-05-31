#include <stdio.h>
#include <stdlib.h>

#define N 5


void escreve(int *vet, int n){
    int i;
    for (i = 0; i < n; i++){
        printf("%d\n", vet[i]);
    }
    printf("\n");
}


int *interseccao(int *v1, int n1, int *v2, int n2, int *n3){
    int count = 0;
    int i, j, k = 0;
    for (i = 0; i < n1; i++){
        for (j = 0; j < n2; j++){
            if (v1[i] == v2[j]){
                count++;
            }
        }
    }

    int *vet3 = (int *)malloc(count * sizeof(int));
    *n3 = count;
    for (i = 0; i < n1; i++){
        for (j = 0; j < n2; j++){
            if (v1[i] == v2[j]){
                vet3[k++] = v1[i];
            }
        }
    }
    return vet3;
}


int main(){
    int vet1[N] = {1, 3, 5, 7, 9};
    int vet2[N] = {1, 2, 3, 4, 5};
    int n3;

    escreve(vet1, N);
    escreve(vet2, N);    

    int *vet3 = interseccao(vet1, N, vet2, N, &n3);
    escreve(vet3, n3);

    free(vet3);
    return 0;
}