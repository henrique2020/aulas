#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*-------------------------------------------------*/
char *ultimo_nome(char *nome_completo){

    char *sbr = NULL;
    int k, i, u, t;
    
    t = 0;
    for(i=0; nome_completo[i] != '\0'; i++){
        if (nome_completo[i] == ' '){
            u = i;
        }
        t++;
    }

    printf("Tamanho: %d\n", t-u);

    sbr = (char *)malloc( (t-u) * sizeof(char));

    for( k=0, i=u+1; i<t; k++, i++){
        sbr[k] = nome_completo[i];
    }
    sbr[k] = '\0';

    return sbr;    
}
/*-------------------------------------------------*/
int main(){
    char nome[100];
    int i;

    for( i=0; i<5; i++ ){
        printf("Digite o nome:\n");
        gets(nome);
        char *sbr = ultimo_nome(nome);
        printf("Sobrenome: %s\n", sbr);
        free(sbr);
    }
    

}

/*-------------------------------------------------*/
