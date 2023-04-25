#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Nodo {
    char palavra[25];
    struct Nodo *prox;
};

struct Nodo *vet[26];

//void inserePalavra(char p[]){ == (char *p)
void inserePalavra(char *p){
    int pos;
    struct Nodo *inicio, *novo;
    if(p != NULL){
        novo = (struct Nodo*)malloc(sizeof(struct Nodo));
        strcpy(novo->palavra, p);
        novo->prox = NULL;
        if(p[0] <= 'Z'){
            pos = p[0] - 'A';
        } else {
            pos = p[0] - 'a';
        }
        inicio = vet[pos];

        if(inicio == NULL){
            vet[pos] = novo;
        } else {
            novo->prox = inicio;
            vet[pos] = novo;
        }
    }
}

void escrevePalavras(){
    int i;
    struct Nodo *aux;
    for (i = 0; i < 26; i++){
        printf("%c: ", i+'a');
        if(vet[i] != NULL){
            aux = vet[i];

            while(aux != NULL){
                printf("%s ", aux->palavra);
                aux = aux->prox;
            }
        }
        printf("\n");
    }
}

int main (){
    int i;
    for (i = 0; i < 26; i++){
        vet[i] = NULL;
    }

    inserePalavra("ALEMAO");
    inserePalavra("horta");
    inserePalavra("rato");
    inserePalavra("aula");
    inserePalavra("amigo");
    inserePalavra("casa");
    inserePalavra("zebra");
    inserePalavra("LEITURA");
    //inserePalavra("Água");    //Não reconhece os acentos

    escrevePalavras();
}
