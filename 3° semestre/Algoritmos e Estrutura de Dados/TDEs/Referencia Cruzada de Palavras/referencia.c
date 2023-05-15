#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ELEMENTO{
    char palavra[50];       //Palavra inserida
    int ocorrencias;        //Número de vezes que a palavra aparece
    struct ELEMENTO *prox;  //Próxima palavra
    struct ELEMENTO *ant;
};

struct ELEMENTO *dicionario[26];    //Dicionário para as letras iniciais

void insere(char *p){
    int pos;
    struct ELEMENTO *inicio, *novo;

    if(p != NULL){
        novo = (struct ELEMENTO*)malloc(sizeof(struct ELEMENTO));
        novo->ocorrencias = 1;
        novo->prox = NULL;
        novo->ant = NULL;
        strcpy(novo->palavra, p);

        if(p[0] <= 'Z'){ pos = p[0] - 'A'; }
        else { pos = p[0] - 'a'; }
        inicio = dicionario[pos];

        if(inicio == NULL){
            dicionario[pos] = novo;

        } else {
            struct ELEMENTO *ant = inicio, *aux = inicio;
            while(aux != NULL && strcasecmp(aux->palavra, p) < 0){
                ant = aux;
                aux = aux->prox;
            }

            if(strcasecmp(p, aux->palavra) == 0){
                aux->ocorrencias += 1;
            } else {
                if(aux!=NULL)
                    aux->ant = novo;
                    novo->prox = aux;
                if(ant!=NULL)
                    novo->ant = ant;
                ant->prox = novo;
            }
        }
    }
}

/*
void escrevePalavras(){
    int i;
    struct ELEMENTO *aux;
    for (i = 0; i < 26; i++){

        printf("%c: \n", i+'A');
        if(dicionario[i] != NULL){
            aux = dicionario[i];
            while(aux != NULL){
                printf(" - %s (%i)\n", aux->palavra, aux->ocorrencias);
                aux = aux->prox;
            }
        }
    }
}
*/

void escrevePalavras(char ordecacao){
    int i;
    struct ELEMENTO *aux, *ant;
    for (i = 0; i < 26; i++){
        printf("%c: \n", i+'A');
        if(dicionario[i] != NULL){
            aux = dicionario[i];

            if(ordecacao == 'c'){
                while(aux != NULL){
                    printf(" - %s (%i)\n", aux->palavra, aux->ocorrencias);
                    aux = aux->prox;
                }
            } else {
               while(aux != NULL){
                    ant = aux;
                    aux = aux->prox;
                }
                while(ant != NULL){
                    printf(" - %s (%i)\n", ant->palavra, ant->ocorrencias);
                    ant = ant->ant;
                }
            }
        }
    }
}

int main (){
    int i;
    for (i = 0; i < 26; i++){
        dicionario[i] = NULL;
    }

    insere("ALEMAO");
    insere("ALEMAO");
    insere("horta");
    insere("rato");
    insere("rinha");
    insere("aula");
    insere("ALEMAO");
    insere("amigo");
    insere("casa");
    insere("casar");
    insere("zebra");
    insere("LEITURA");

    escrevePalavras('c');
    printf("\n\n\n\n");
    escrevePalavras('d');
}
