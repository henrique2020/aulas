#include <stdio.h>

int main(void){
    int tam;
    printf("Digite o tamanho da matrix: ");
    scanf("%d", &tam);
    printf("\n");
    int mat[tam][tam];
    int i, j;
    for (int i = 0; i < tam; i++){
        for (int j = 0; j < tam; j++){
            if((i > 0 && i%2 != 0) && tam%2 != 0){
                scanf("%d", &mat[(tam-1)-i][j]);
            }
            else{
                scanf("%d", &mat[i][j]);
            }
        }
    }
    
    printf("\n");

    for(i = 0; i < tam; i++){
        for(j = 0; j < tam; j++){
            printf("%d ", mat[i][j]);
        }           
      printf("\n");
    }

    return 0;
}