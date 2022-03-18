//Codigo utilizando matriz...
#include<stdio.h>

int main(){
    int tam = 12, i, j, n;    //Valor pré-definido na questão
    float mat[tam][tam], soma;
    char op[1];
    
    scanf("%s", &op[0]);    //Vai ser sempre 1 letra maiúscula (S ou M)
    
    for(i = 0; i < tam; i++){
        for(j = 0; j < tam; j++){
            scanf("%f", &mat[i][j]);
        }
    }

    soma = 0.0;
    n = 0;  //Vai ser sempre 66 --> 11+10+9+8+7+6+5+4+3+2+1 ou ((12*12)-12)/2
    for (i = 0; i < tam-1; i++){
        for (j = 0; j < tam-1-i; j++){
            n+=1;
            soma += mat[i][j];
        }
    }

    if(op[0] == 'M'){
        soma /= n;
    }

    printf("%.1f\n", soma);

    return 0;
}