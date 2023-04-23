#include <stdio.h>

#define N 5

int matriz(int mat[N][N]){
    int acima_diag = 0, diag = 0, abaixo_diag = 0;
    int v1, v2;
    for (v1 = 0; v1 < N; v1++){
        for (v2 = 0; v2 < N; v2++){
            if (mat[v1][v2] != 0){
                if(v1 < v2){ acima_diag++; }
                else if(v1 == v2){ diag++; }
                else{ abaixo_diag++; }
            }
        }   
    }
    if((diag == 0 && abaixo_diag == 0) && acima_diag != 0){ return 1; }
    else if((acima_diag == 0 && abaixo_diag == 0) && diag != 0){ return 2; }
    else if((diag == 0 && acima_diag == 0) && abaixo_diag != 0){ return 3; }
    else{ return 0; }

}

int main(){
    //1 -- Mat superior, != 0 apenas acima da diagonal principal
    //2 -- Mat diagonal, != 0 apenas na diagonal principal
    //3 -- Mat inferior, != 0 apenas abaixo da diagonal principal
    //0 -- Todo o resto
    printf("1 -- Mat superior, != 0 apenas acima da diagonal principal\n"
           "2 -- Mat diagonal, != 0 apenas na diagonal principal\n"
           "3 -- Mat inferior, != 0 apenas abaixo da diagonal principal\n"
           "0 -- Todo o resto\n");

    int mat[N][N] = {{0, 1, 2, 3, 4},
                    {0, 0, 1, 2, 3},
                    {0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 4},
                    {0, 0, 0, 0, 0}};
    printf("Matriz: %d\n", matriz(mat));

    int mat2[N][N] = {{0, 0, 0, 0, 0},
                    {1, 0, 0, 0, 0},
                    {2, 1, 0, 0, 0},
                    {3, 2, 0, 0, 0},
                    {4, 3, 0, 4, 0}};
    printf("Matriz: %d\n", matriz(mat2));

    int mat3[N][N] = {{0, 0, 0, 0, 0},
                    {0, 2, 0, 0, 0},
                    {0, 0, 0, 0, 0},
                    {0, 0, 0, 4, 0},
                    {0, 0, 0, 0, 0}};
    printf("Matriz: %d\n", matriz(mat3));

    int mat4[N][N] = {{0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0}};
    printf("Matriz: %d\n", matriz(mat4));
    return 0;
}