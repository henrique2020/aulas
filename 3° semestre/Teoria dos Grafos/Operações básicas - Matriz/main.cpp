#include <stdlib.h>
#include <stdio.h>

#define N 10

typedef int ** grafo;

void insere(grafo G,int origem,int destino)
{
    G[origem][destino]=1;
}

void mostra(grafo G)
{
    printf("   |");
    for (int i=0;i<N;i++){
        printf(" %2d ", i);
    }
    printf("\n");

    printf("---|");
    for (int i=0;i<N;i++){
        printf("----");
    }
    printf("\n");

    for (int i=0;i<N;i++){
        printf("%2d |", i);
        for (int j=0;j<N;j++){
            printf(" %2d ",G[i][j]);
        }
        printf("\n");
    }
}

grafo cria_grafo()
{
    grafo M=(int**)malloc(N*sizeof(int*));
    for (int i=0;i<N;i++)
        M[i]=(int*)calloc(N,sizeof(int));
    return M;
}

int main()
{
    grafo M;
    M=cria_grafo();

    insere(M, 3, 7);
    insere(M, 5, 2);
    insere(M, 1, 8);
    insere(M, 0, 4);
    insere(M, 6, 9);
    insere(M, 2, 3);
    insere(M, 7, 5);
    insere(M, 4, 6);
    insere(M, 8, 1);
    insere(M, 9, 0);


    mostra(M);
}
