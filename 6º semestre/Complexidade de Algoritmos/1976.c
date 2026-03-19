#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define MAX 1001

long long dp[MAX][MAX];   // tabela de custo mínimo
int split[MAX][MAX];      // posição do corte ótimo
int p[MAX];               // dimensões das matrizes

void imprimeOrdem(int i, int j) {
    if (i == j) {
        printf("A%d", i);
        return;
    }
    printf("(");
    imprimeOrdem(i, split[i][j]);
    imprimeOrdem(split[i][j] + 1, j);
    printf(")");
}

int main() {
    int N;
    while (scanf("%d", &N) == 1 && N != 0) {
        for (int i = 1; i <= N; i++) {
            int L, C;
            scanf("%d %d", &L, &C);
            if (i == 1) p[0] = L;
            p[i] = C;
        }

        for (int i = 1; i <= N; i++)
            dp[i][i] = 0;

        // calcula cadeias de tamanho 2 até N
        for (int tam = 2; tam <= N; tam++) {
            for (int i = 1; i <= N - tam + 1; i++) {
                int j = i + tam - 1;
                dp[i][j] = LLONG_MAX;
                for (int k = i; k < j; k++) {
                    long long custo = dp[i][k] + dp[k + 1][j] +
                                      (long long)p[i - 1] * p[k] * p[j];
                    if (custo < dp[i][j]) {
                        dp[i][j] = custo;
                        split[i][j] = k;
                    }
                }
            }
        }

        int temEmpate = 0;
        for (int i = 1; i < N && !temEmpate; i++) {
            for (int j = i + 1; j <= N && !temEmpate; j++) {
                long long melhor = dp[i][j];
                int cont = 0;
                for (int k = i; k < j; k++) {
                    long long custo = dp[i][k] + dp[k + 1][j] +
                                      (long long)p[i - 1] * p[k] * p[j];
                    if (custo == melhor) cont++;
                }
                if (cont > 1) temEmpate = 1;
            }
        }

        if (temEmpate)
            printf("%lld\n", dp[1][N]);
        else {
            imprimeOrdem(1, N);
            printf("\n");
        }
    }
    return 0;
}
