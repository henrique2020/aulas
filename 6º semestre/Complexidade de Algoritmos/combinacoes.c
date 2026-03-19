#include <stdio.h>

void backtracking(int pos, int n, int soma, int somaAtual, int minimo, int vet[], int unico) {
    if (pos == n){
        if(somaAtual == soma) {
            for (int i = 0; i < n; i++)
                printf("%d ", vet[i]);
            printf("\n");
        }
        return;
    }

    for (int v = minimo + unico; v <= soma - somaAtual; v++) {
        vet[pos] = v;
        backtracking(pos + 1, n-1, soma, somaAtual + v, v, vet, unico);
    }
}

int main() {
    int n = 4;
    int soma = 5;

    int vet[n];
    backtracking(0, n, soma, 0, 1, vet, 0);

    return 0;
}
