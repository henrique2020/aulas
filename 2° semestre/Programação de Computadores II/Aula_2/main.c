#include <stdio.h>

int main(void){
    int tam;
    printf("Digite o tamanho da matriz: ");
    scanf("%d", &tam);
    printf("\n");
    int mat[tam][tam];
    int i, j;
    for (int i = 0; i < tam; i++){
        for (int j = 0; j < tam; j++){
            // if((i > 0 && i%2 != 0) && tam%2 != 0){
            //     scanf("%d", &mat[(tam-1)-i][j]);
            // }
            // else{
            //     scanf("%d", &mat[i][j]);
            // }
            scanf("%d", &mat[i][j]);
        }
    }

    int sum[tam];
    int resto = 0;
    for (j = tam-1; j >= 0; j--){
        int quociente = 0;
        for (i = 0; i < tam; i++){
            quociente += mat[i][j];
            //printf("%d, %d\n", quociente, mat[i][j]);

        }
        quociente += resto;
        resto = quociente/10;
        quociente %= 10;
        //printf("\n%d %d\n\n", resto, quociente);
        sum[i] = quociente;
    }
    for (i = 0; i < tam; i++){
        printf("%d ", sum[i]);
    }
    
    printf("\n");

    // for(i = 0; i < tam; i++){
    //     for(j = 0; j < tam; j++){
    //         printf("%d ", mat[i][j]);
    //     }           
    //   printf("\n");
    // }

    return 0;
}