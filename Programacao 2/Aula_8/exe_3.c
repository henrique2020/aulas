#include <stdio.h>
#include <stdlib.h>
#define N 5

void gera_matriz(int mat[N][N]){
    int i, j;
    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            mat[i][j] = rand()%100;
        }
    }
}

void escreve_matriz(int mat[N][N]){
    int i, j;
    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            printf("%4d", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void minmax(int mat[N][N], int *m, int *lin, int *col){
    int maior, l, c, i, j;
    maior = mat[0][0];
    l = c = 0;

    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            if(mat[i][j] > maior){
                maior = mat[i][j];
                l = i;
                c = j;
            }
        }
    }

    *m = maior;
    *lin = l;
    *col = c;
    
    for (j = 0; j < N; j++){
        if(mat[*lin][j] < *m){
            *m = mat[*lin][j];
            *col = j;
        }
    }
    
}

int main(){
    int mat[N][N], m, lin, col;
    gera_matriz(mat);
    escreve_matriz(mat);
    
    minmax(mat, &m, &lin, &col);
    printf("MinMax: %d\nLinha: %d\nColuna: %d\n", m, lin, col);
    return 0;
}