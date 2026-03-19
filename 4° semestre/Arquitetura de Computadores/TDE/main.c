#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_VETOR 5

int somaVetor(int vetor[], int elementos){
    int j, acum = 0;
    for (j = 0; j < elementos; j++)
        acum += vetor[j];
    return acum ;
}

int main() {
    int i, soma, numeros[TAM_VETOR];
    srand(time(NULL));
    for (i = 0; i < TAM_VETOR; i++)
        numeros[i] = rand();
    soma = somaVetor(numeros, TAM_VETOR);
    printf("%d", soma);
    return 0;
}
