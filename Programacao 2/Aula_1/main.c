#include <stdio.h>

#define N 4
int main(void){
    int mat_bi[N][N];
    int i, j;
    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            scanf("%d", &mat_bi[i][j]);
        }
    }
    printf("\n");
    
    int soma_diagonal_principal, soma_diagonal_secundaria;
    int soma_acima_principal, soma_abaixo_principal;
    int soma_acima_secundaria, soma_abaixo_secundaria;

    /*
    soma_diagonal_principal = 0, soma_diagonal_secundaria = 0;
    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            if(i == j){
                soma_diagonal_principal += mat_bi[i][j];
            }
            else if ((i+j) == (N-1)){
                soma_diagonal_secundaria += mat_bi[i][j];
            }
            printf("%d ", mat_bi[i][j]);
        }           
      printf("\n");
    }
    */
    
    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            printf("%d ", mat_bi[i][j]);
        }           
      printf("\n");
    }

    soma_diagonal_principal = 0, soma_diagonal_secundaria = 0;
    // Calculando a diagonal principal
    for (i = 0; i < N; i++){
        soma_diagonal_principal += mat_bi[i][i];
    }
    
    // Calculando a diagonal secundária
    for (i = 0, j = N-1; i < N; i++, j--){
        soma_diagonal_secundaria += mat_bi[i][j];
    }

    soma_acima_principal = 0, soma_abaixo_principal = 0;
    // Calculando os valores acima da diagonal principal
    for (i = 0; i < N-1; i++){
        for (j = i+1; j < N; j++){
            soma_acima_principal += mat_bi[i][j];
        }
    }

    // Calculando os valores abaixo da diagonal principal
    for (i = 0; i < N-1; i++){
        for (j = i+1; j < N; j++){
            soma_abaixo_principal += mat_bi[j][i];
        }
    }

    soma_acima_secundaria = 0, soma_abaixo_secundaria = 0;
    // Calculando os valores acima da diagonal secundária
    for (i = 0; i < N-1; i++){
        for (j = 0; j < N-1-i; j++){
            soma_acima_secundaria += mat_bi[i][j];
        }
    }

    // Calculando os valores abaixo da diagonal secundária
    for (i = 1; i < N; i++){
        for (j = N-i; j < N; j++){
            soma_abaixo_secundaria += mat_bi[i][j];
        }
    }

    printf("\n");
    printf("Soma da diagonal principal: %d\n", soma_diagonal_principal);
    printf("Soma da diagonal secundária: %d\n", soma_diagonal_secundaria);
    printf("\n");
    printf("Soma acima da diagonal principal: %d\n", soma_acima_principal);
    printf("Soma abaixo da diagonal principal: %d\n", soma_abaixo_principal);
    printf("\n");
    printf("Soma acima da diagonal secundária: %d\n", soma_acima_secundaria);
    printf("Soma abaixo da diagonal secundária: %d\n", soma_abaixo_secundaria);
    return 0;
}