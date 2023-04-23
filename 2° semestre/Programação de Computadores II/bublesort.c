#include <stdio.h>
#define N 5

void ord_1(){
    int vet[N] = {2, 8, 3, 7, 1};
    int i, j, aux;
    for (i = 0; i < N-1; i++){
        for (j = 0; j < N-1-i; j++){
            if(vet[j] < vet[j+1]){   //Ordem decrescente
            //if(vet[j] > vet[j+1])   //Ordem crescente
                aux = vet[j];
                vet[j] = vet[j+1];
                vet[j+1] = aux;
            }
        }
    }

    printf("Ordenado: ");
    for (i = 0; i < N; i++){
        printf("%5d", vet[i]);
    }
    printf("\n");
}

void ord_2(){
    int vet[N] = {8, 3, 2, 9, 7};
    int p_m;    //Posição menor
    int i, j, aux;
    
    for (i = 0; i < N-1; i++){
        p_m = i;
        for (j = i; j < N; j++){
            if(vet[p_m] > vet[j]){   //Ordem crescente
                p_m = j;
            }
        }
        aux = vet[i];
        vet[i] = vet[p_m];
        vet[p_m] = aux;
    }

    printf("Ordenado: ");
    for (i = 0; i < N; i++){
        printf("%5d", vet[i]);
    }
    printf("\n");
}


int main(){
    ord_1();
    ord_2();
}