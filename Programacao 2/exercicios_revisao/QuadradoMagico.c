#include <stdio.h>

#define N 4

int quadrado(int mat[N][N]){
    int v1, v2, soma, soma_diagonal_principal = 0;

    for (v1 = 0; v1 < N; v1++){
        for (v2 = 0; v2 < N; v2++){
            printf("%0 3d", mat[v1][v2]);
        }
        printf("\n");
    }
    printf("\n\n");

    for (v1 = 0, v2 = 0; v1 < N; v1++, v2++){
        soma_diagonal_principal += mat[v1][v2];
    }

    soma = 0;
    for (v1 = 0, v2 = N-1; v1 < N; v1++, v2--){
        soma += mat[v1][v2];
    }
    
    if (soma_diagonal_principal != soma){ return 0; }

    for (v1 = 0; v1 < N; v1++){
        soma = 0;
        for (v2 = 0; v2 < N; v2++){
            soma += mat[v2][v1];
        }
        if (soma_diagonal_principal != soma){ return 0; }
    }

    for (v1 = 0; v1 < N; v1++){
        soma = 0;
        for (v2 = 0; v2 < N; v2++){
            soma += mat[v1][v2];
        }
        if (soma_diagonal_principal != soma){ return 0; }
    }

    return 1;
}

int main(){
    /*
    //Modelo 5x5
    int quadrado[N][N] = {{0, 1, 2, 3, 4}, 
                        {1, 2, 3, 4, 0}, 
                        {2, 3, 4, 0, 1}, 
                        {3, 4, 0, 1, 2}, 
                        {4, 0, 1, 2, 3}};
    */

   int mat[N][N] = {{1, 14, 15, 4}, 
                    {12, 7, 6, 9}, 
                    {8, 11, 10, 5}, 
                    {13, 2, 3, 16}};

    
    /*
    int v1, v2;
    for (v1 = 0; v1 < N; v1++){
        for (v2 = 0; v2 < N; v2++){
            scanf("%d", quadrado[v1][v2]);
        }
    }
    */
    if (quadrado(mat) == 1){ printf("É um quadrado mágico!\n"); }
    else{ printf("Não é um quadrado mágico!\n"); }
    
    return 0;
}