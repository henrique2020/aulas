#include <stdio.h>
#include <stdlib.h>

#define INF 10000000

int main() {
    int cidades, rodovias, custoTotal = 0;
    scanf("%d %d", &cidades, &rodovias);

    cidades = cidades+1; //Para poder utilizar a posição direto no array
    int estradas[cidades][cidades];
    for(int i = 0; i < cidades; i++)
        for(int j = 0; j < cidades; j++)
            estradas[i][j] = INF;

    for(int i = 0; i < rodovias; i++){
        int c1, c2, distancia;
        scanf("%d %d %d", &c1, &c2, &distancia);

        estradas[c1][c2] = distancia;
        estradas[c2][c1] = distancia;
    }

    for (int k = 1; k < cidades; k++)
        for (int i = 1; i < cidades; i++)
            for (int j = 1; j < cidades; j++)
                if(estradas[i][j] > estradas[i][k] + estradas[k][j])
                    estradas[i][j] = estradas[i][k] + estradas[k][j];

    printf("\n");
    for(int i = 1; i < cidades; i++){
        for(int j = 1; j < cidades; j++)
            printf("%d ", estradas[i][j]);

        printf("\n");
    }

    int somas[cidades];
    memset(somas, 0, cidades);
    for(int i = 1; i < cidades; i++)
        for(int j = 1; j < cidades; j++)
            somas[i] += estradas[i][j];

    printf("\n");
    for(int i = 1; i < cidades; i++)
        printf("%d ", somas[i]);


    //printf("%d\n", 7); //retorno das cidades com menor distância (que ficam no centro)


    return 0;
}
