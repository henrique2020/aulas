#include <stdio.h>
#define TAM 4

typedef struct Pessoa{
    int nro;
    char nome[20];
} Pessoa;

void escreva(Pessoa pes[]){
    int i;
    for(i=0;i<TAM;i++){
        printf("nro: %d\n",pes[i].nro);
        printf("nome: %s\n",pes[i].nome);
    }
}

int main(){
    Pessoa p[10], aux;
    int i,j;

    printf("\nEntrada dos dados:\n");    
    for(i=0;i<TAM;i++){
        printf("nro: ");
        scanf("%d",&p[i].nro);
        printf("nome: ");
        scanf("%s",p[i].nome);
    }
    
    printf("\nDados digitados:\n");
    escreva(p);

    printf("\n\nInversão\n");
    for(i=0,j=TAM-1;i<j;i++,j--){
        aux=p[i];
        p[i]=p[j];
        p[j]=aux;
    }
    
    escreva(p);

}