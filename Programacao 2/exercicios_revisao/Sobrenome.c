#include <stdio.h>

int retorna_sobrenome(char nome[100], char sobrenome[100]){
    int i, k, ult;
    for (i = 0; nome[i] != '\0'; i++){
        if(nome[i] == ' '){ ult = i; }
    }
    for (i = (ult+1), k = 0; nome[i] != '\0'; i++, k++){
        sobrenome[k] = nome[i];
    }
    sobrenome[i] = '\0';
    
}

int main(){
    char nome_completo[100] = "Paulo da Silva Coelho Júnior";
    char sobrenome[100];

    retorna_sobrenome(nome_completo, sobrenome);
    printf("%s\n", sobrenome);
}