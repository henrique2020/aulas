//Codigo utilizando matriz...
#include<stdio.h>

int main(){
    int tam = 12, i, j;    //Valor pré-definido na questão
    float mat[tam][tam]; 
    
    int line;    //vai ser sempre entre 0 e 11 
    scanf("%d", &line);
    char op[2];    //Vai ser sempre 1 letra maiúscula (S ou M)
    scanf("%s", &op[0]);
    
    for(i = 0; i < tam; i++){
        for(j = 0; j < tam; j++){
            scanf("%f", &mat[i][j]);
        }
    }
    
    float soma = 0.0;
    for(j = 0; j < tam; j++){
        soma += mat[line][j];
    }
    
    if(op[0] == 'M'){
        soma = soma/tam;
    }
    
    printf("%.1f\n", soma);
    
    return 0;
}