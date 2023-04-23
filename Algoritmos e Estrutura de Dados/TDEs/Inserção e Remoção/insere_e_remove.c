#include <stdio.h>
#include <stdlib.h>

struct elemento {
    int info;
    struct elemento *prox;
};

typedef struct elemento Elemento;

Elemento *inicio;

void insere(int valor){
    Elemento *aux=inicio,*novo;
    novo = (Elemento*) malloc(sizeof(Elemento));
    novo->info = valor;
    novo->prox = NULL;

    if(inicio == NULL) {
        inicio = novo;
    } else {
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = novo;
    }
}


void insere_ordenado(int valor){
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


void conta_repetidos(){
    Elemento *aux1 = inicio, *aux2;
    int valor_ant, repeticoes;
    int nao_repetiu = 1;

    while(aux1 != NULL){
        valor_ant = aux1->info;
        repeticoes = 0;
        aux2 = aux1->prox;

        while(aux2 != NULL){
            if(aux2->info == valor_ant){
                repeticoes++;
                nao_repetiu = 0;
            }
            aux2 = aux2->prox;
        }

        if(repeticoes > 0){
            printf("O valor %d tem %d repeticoes.\n", valor_ant, repeticoes + 1);
        }

        aux1 = aux1->prox;
    }

    if(nao_repetiu){
        printf("Nenhum valor repetido na listagem.\n");
    }

    printf("\n");
}


void remove_repetidos(){
    Elemento *aux1 = inicio, *aux2, *ant;
    int valor_ant, repeticoes;

    while(aux1 != NULL){
        valor_ant = aux1->info;
        repeticoes = 0;
        aux2 = aux1->prox;
        ant = aux1;

        while(aux2 != NULL){
            if(aux2->info == valor_ant){
                repeticoes++;
                ant->prox = aux2->prox;
                free(aux2);
                aux2 = ant->prox;
            }
            else {
                ant = aux2;
                aux2 = aux2->prox;
            }
        }

        aux1 = aux1->prox;
    }
}


void remove_valor(int valor){
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

void escreve(){
    Elemento *aux=inicio;
    printf("Lista:\n");
    while(aux!=NULL){
        printf("%d ",aux->info);
        aux=aux->prox;
    }
    printf("\n\n");
}


int main(){
    inicio=NULL;
    /*
    insere_ordenado(5);
    insere_ordenado(1);
    insere_ordenado(1);
    insere_ordenado(3);
    insere_ordenado(5);
    insere_ordenado(10);
    */
    insere(5);
    insere(1);
    insere(1);
    insere(3);
    insere(5);
    insere(10);
    escreve();

    conta_repetidos();
    remove_valor(1);
    escreve();

    conta_repetidos();
    remove_repetidos();
    conta_repetidos();
    escreve();
}
