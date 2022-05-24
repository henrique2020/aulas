#include <stdio.h>
#include <stdlib.h>
#define N 5

int *cria_vetor(int n){
    int i;
    int *vet = (int *)malloc(n * sizeof(int));
    for (i = 0; i < n; i++){
        vet[i] = i*3;
    }
    return vet;
}


void escreve(int *vet, int n){
    int i;
    for (i = 0; i < n; i++){
        printf("%d\n", vet[i]);
    }
    
}


int main(){
    int n;
    printf("Digite o tamanho do vetor: ");
    scanf("%d", &n);
    
    int *v = cria_vetor(n);
    escreve(v, n);

    free(v); //Desaloca o ponteiro do malloc
    return 0;
}