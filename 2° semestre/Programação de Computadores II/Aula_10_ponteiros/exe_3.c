#include <stdio.h>
#include <stdlib.h>

int *seqFibonacci(int n){
    int i;
    int *fibonacci = (int *)malloc(n * sizeof(int));
    fibonacci[0] = 0;
    fibonacci[1] = 1;
    for (i = 2; i < n; i++){
        fibonacci[i] = fibonacci[i-2] + fibonacci[i-1];
    }
    return fibonacci;
}

void escreve(int *fibonacci, int n){
    int i;
    for (i = 0; i < n; i++){
        printf("%d ", fibonacci[i]);
    }
    printf("\n");
}

int main(){
    int n;
    int *fib;

    printf("Quantos valores de fibonacci? ");
    scanf("%d", &n);

    fib = seqFibonacci(n);
    escreve(fib, n);

    free(fib);
    return 0;
}