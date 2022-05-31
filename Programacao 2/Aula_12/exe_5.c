#include <stdio.h>
#include <stdlib.h>

#define M 5
#define N 2

typedef struct candidato{
    char nome[50];
    int pontos;
} CANDIDATO;


void bublesort(CANDIDATO *c, int m){
    int i, j;
    CANDIDATO aux;

    for (i = 0; i < m-1; i++){
        for (j = 0; j < m-1-i; j++){
            if(c[j].pontos < c[j+1].pontos){
                aux = c[j];
                c[j] = c[j+1];
                c[j+1] = aux;
            }
        }        
    }
}


void le_candidatos(CANDIDATO *c, int m){
    int i;
    for (i = 0; i < m; i++){
        printf("Digite o nome: ");
        gets(c[i].nome);

        printf("Digite o número de pontos: ");
        scanf("%d", &c[i].pontos);

        getchar();
        printf("\n");
    }
}


void escreve_candidatos(CANDIDATO *c, int m){
    int i;
    for (i = 0; i < m; i++){
        printf("Candidato %s fez %d pontos\n", c[i].nome, c[i].pontos);
    }
    printf("\n");
}


CANDIDATO *maiores_pontuadores(CANDIDATO *c, int m, int n){
    int i;
    CANDIDATO *mp = (CANDIDATO *)malloc(n * sizeof(CANDIDATO));

    bublesort(c, m);
    for(i = 0; i < n; i++){
        mp[i] = c[i];
    }

    return mp;
}


int main(){
    CANDIDATO c[M];

    le_candidatos(c, M);
    escreve_candidatos(c, M);

    CANDIDATO *mp = maiores_pontuadores(c, M, N);
    escreve_candidatos(mp, N);

    return 0;
}