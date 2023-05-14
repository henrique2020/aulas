#include <stdio.h>
#include <stdlib.h>

struct elemento {
    int info;
    struct elemento *prox;
};

typedef struct elemento Elemento;

Elemento *inicio;

void insereordenado(int valor){
    Elemento *aux=inicio,*ant=inicio,*novo;
    novo = (Elemento*) malloc(sizeof(Elemento));
    novo->info = valor;
    novo->prox = NULL;
    if(inicio==NULL)
        inicio=novo;
    else {
        if(valor<=inicio->info){
            novo->prox=inicio;
            inicio=novo;
        }
        else {
            while(aux!=NULL && (aux->info)<valor){
                ant=aux;
                aux=aux->prox;
            }
            ant->prox=novo;
            if(aux!=NULL)
                novo->prox=aux;
        }
    }

}

void escreve(){
    Elemento *aux=inicio;
    printf("Lista:\n");
    while(aux!=NULL){
        printf("%d ",aux->info);
        aux=aux->prox;
    }
    printf("\n\n");
}

void removevalor(int valor){
    Elemento *aux=inicio, *ant=inicio;
    
    if(inicio!=NULL){
        while(aux!=NULL && aux->info!=valor){
            ant=aux;
            aux=aux->prox;
        }
        if(aux==inicio){
            inicio=inicio->prox;
            free(aux);
        }
        else{
            if(aux!=NULL){
                ant->prox=aux->prox;
                free(aux);
            }
            else
                printf("\nvalor nao encontrado: %d\n\n",valor);
        }
    }
}

int main(){
    inicio=NULL;
    insereordenado(5);
    insereordenado(1);
    insereordenado(1);
    insereordenado(3);
    insereordenado(5);
    insereordenado(10);
    escreve();
    removevalor(3);
    removevalor(1);
    removevalor(10);
    removevalor(3);
    removevalor(1);

    escreve();
}