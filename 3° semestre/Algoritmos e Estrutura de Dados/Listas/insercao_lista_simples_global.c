//Exemplo com inicio como variavel global:
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

struct nodo{
  int info;
  struct nodo *prox;
};

typedef struct nodo Elemento;

Elemento *inicio;

void insereinicio(int valor){
    Elemento *novo;
    
    novo=(Elemento*) malloc(sizeof(Elemento));
    novo->info=valor;
    novo->prox=NULL;
    
    if(inicio==NULL)
        inicio=novo;
    else{
        novo->prox=inicio;
        inicio=novo;
    }    
}

void exibelista(){
    Elemento *aux=inicio;

    printf("\nLista:\n");    
    while(aux!=NULL){
        printf("%d ",aux->info);
        aux=aux->prox;
    }
    printf("\n\n");
}

int main(){
    inicio=NULL;
    
    insereinicio(5);
    insereinicio(2);
    exibelista();
    insereinicio(7);
    insereinicio(10);
    insereinicio(1);
    insereinicio(3);
    exibelista();
}