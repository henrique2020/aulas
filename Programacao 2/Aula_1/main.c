#include <stdio.h>

#define N 4
int m_4(void){
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
    
   for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            printf("%d ", mat_bi[i][j]);
        }           
      printf("\n");
    }
    
    // M00000100
    // Calculando a diagonal principal
    printf("\n");
    soma_diagonal_principal = 0;
    for (i = 0; i < N; i++){
        soma_diagonal_principal += mat_bi[i][i];
    }
    printf("Soma da diagonal principal: %d\n", soma_diagonal_principal);

    /* ------------------------------------------------------------------- */
    
    // M00000150
    // Calculando a diagonal secundária
    printf("\n");
    soma_diagonal_secundaria = 0;
    for (i = 0, j = N-1; i < N; i++, j--){
        soma_diagonal_secundaria += mat_bi[i][j];
    }
    printf("Soma da diagonal secundária: %d\n", soma_diagonal_secundaria);

    /* ------------------------------------------------------------------- */
    
    // M00000200
    // Calculando os valores acima da diagonal principal
    printf("\n");
    soma_acima_principal = 0;
    for (i = 0; i < N-1; i++){
        for (j = i+1; j < N; j++){
            soma_acima_principal += mat_bi[i][j];
        }
    }
    printf("Soma acima da diagonal principal: %d\n", soma_acima_principal);

    /* ------------------------------------------------------------------- */
    
    // Calculando os valores abaixo da diagonal principal
    printf("\n");
    soma_abaixo_principal = 0;
    for (i = 0; i < N-1; i++){
        for (j = i+1; j < N; j++){
            soma_abaixo_principal += mat_bi[j][i];
        }
    }
    printf("Soma abaixo da diagonal principal: %d\n", soma_abaixo_principal);

    /* ------------------------------------------------------------------- */
    
    soma_acima_secundaria = 0;
    // M00000300
    // Calculando os valores acima da diagonal secundária
    printf("\n");
    for (i = 0; i < N-1; i++){
        for (j = 0; j < N-1-i; j++){
            soma_acima_secundaria += mat_bi[i][j];
        }
    }
    printf("Soma acima da diagonal secundária: %d\n", soma_acima_secundaria);

    /* ------------------------------------------------------------------- */
    
    // Calculando os valores abaixo da diagonal secundária
    printf("\n");
    soma_abaixo_secundaria = 0;
    for (i = 1; i < N; i++){
        for (j = N-i; j < N; j++){
            soma_abaixo_secundaria += mat_bi[i][j];
        }
    }
    printf("Soma abaixo da diagonal secundária: %d\n", soma_abaixo_secundaria);
    
    return 0;
}

#define N 5
int m_5(void){
    int mat_bi[N][N];
    int i, j;
    for (i = 0; i < N; i++)    {
        for (j = 0; j < N; j++)        {
            scanf("%d", &mat_bi[i][j]);
        }
    }
    
    // M00000700
    printf("\n");
    int value = 1;
    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            if (i == j){ // Verificando se faz parte da diagonal principal
                if (mat_bi[i][j] == 1){
                    continue;
                }
                else{
                    value = 0;
                    break;
                }
            }
            else{ // Se não fizer parte da diagonal principal
                if (mat_bi[i][j] == 0){
                    continue;
                }
                else{
                    value = 0;
                    break;
                }
            }
        }
    }

    printf("1 - É uma matriz identidade\n0 - Não é uma matriz identidade\n");
    printf("Resultado: %d\n", value);

    /* ------------------------------------------------------------------- */
    
    // M00001000
    printf("\n");
    int somaL[N] = {}, somaC[N] = {};
    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            somaL[i]+=mat_bi[i][j];
            somaC[j]+=mat_bi[i][j];
        }
    }

    printf("------------------\n");
    printf("| Sum L -- Sum C |\n");
    printf("------------------\n");
    for (i = 0; i < N; i++){
        printf("| L%d: %d -- C%d: %d |\n", (i+1), somaL[i], (i+1), somaC[i]);
    }
    printf("------------------\n");

    /* ------------------------------------------------------------------- */

    
    return 0;
}

int main(){
    printf("Matriz 4x4\n");
    m_4();
    printf("\n\n|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|\n\n");
    
    printf("Matriz 5x5\n");
    m_5();
    printf("\n\n|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|\n\n");
    return 0;
}