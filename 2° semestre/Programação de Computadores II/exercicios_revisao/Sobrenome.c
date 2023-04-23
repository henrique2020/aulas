#include <stdio.h>

int retorna_sobrenome(char nome[100], char sobrenome[100]){
    int i, k, ult;
    for (i = 0; nome[i] != '\0'; i++){
        if(nome[i] == ' '){ ult = i; }
    }
    for (i = (ult+1), k = 0; nome[i-1] != '\0'; i++, k++){
        sobrenome[k] = nome[i];
    }
    
}

int main(){
    char nome_completo[100] = "Paulo da Silva Coelho Júnior";
    char sobrenome[100];

    retorna_sobrenome(nome_completo, sobrenome);
    printf("Sobrenome: %s\n", sobrenome);
}