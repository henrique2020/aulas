#include <stdio.h>

#define N 5
int main(void){
    int mat[N][N];
    int i, j;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if(i > 0 && i%2 != 0){
                scanf("%d", &mat[N-i][j]);
            }
            else{
                scanf("%d", &mat[i][j]);
            }
        }
    }
    
    printf("\n");

    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            printf("%d ", mat[i][j]);
        }           
      printf("\n");
    }

    return 0;
}