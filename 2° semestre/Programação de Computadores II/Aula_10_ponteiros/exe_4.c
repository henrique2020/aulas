#include <stdio.h>
#include <stdlib.h>


int *seqPrimos(int n){
    int i, k, p = 3, flag;
    int *numPrimos = (int *)malloc(n * sizeof(int));
    numPrimos[0] = 2;

    for (k = 1; k < n; ){
        flag = 0;
        for(i = 0; i < k; i++){
            if(p%numPrimos[i] == 0){
                flag = 1;
                break;
            }
        }
        if(!flag){
            numPrimos[k++] = p;
        }
        p+=2;
    }
    

    return numPrimos;
}


void escreve(int *primos, int n){
    int i;
    for (i = 0; i < n; i++){
        printf("%d ", primos[i]);
    }
    printf("\n");
}


int main(){
    int n, *primos;

    printf("Tamanho da sequencia? ");
    scanf("%d", &n);

    primos = seqPrimos(n);
    escreve(primos, n);

    free(primos);
    return 0;
}