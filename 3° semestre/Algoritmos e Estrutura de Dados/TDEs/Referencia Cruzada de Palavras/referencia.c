#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
+-------------------------+
| ALF: [A-Z] -> 26 letras |
| OCO: [1-100] -> 100 rep |
+-------------------------+
*/
#define ALF 26
#define OCO 100

typedef struct {
    char palavra[50];      // Palavra inserida
    int ocorrencias;       // Número de vezes que a palavra aparece
    struct ELEMENTO *prox; // Próxima palavra
    struct ELEMENTO *ant;  // Palavra anterior
} ELEMENTO;

ELEMENTO *dicionario[ALF];  // Dicionário para as letras iniciais [a-z]
ELEMENTO *ocorrencias[OCO]; // Dicionário para o número de ocorrencias [1-100]

void removeOco(ELEMENTO *inicio, char *palavra) {
    ELEMENTO *aux = inicio;

    while (aux != NULL && strcasecmp(aux->palavra, palavra) != 0) {
        aux = aux->prox;
    }
    if (aux == inicio) {
        inicio = inicio->prox;
    } else {
        ELEMENTO *ant = aux->ant, *prox = aux->prox;
        ant->prox = prox;
        prox->ant = ant;
    }
}


void insereOco(ELEMENTO *inicio, ELEMENTO *novo) {
    ELEMENTO *ant = inicio, *aux = inicio;
    while (aux != NULL && strcasecmp(aux->palavra, novo->palavra) < 0) {
        ant = aux;
        aux = aux->prox;
    }

    if (aux != NULL) {
        novo->prox = aux;
        aux->ant = novo;
    }
    if (ant != NULL) {
        novo->ant = ant;
        ant->prox = novo;
    }
}


void insereDicOrdenado(ELEMENTO *inicio, ELEMENTO *novo) {
    ELEMENTO *ant = inicio, *aux = inicio;
    while (aux != NULL && strcasecmp(aux->palavra, novo->palavra) < 0) {
        ant = aux;
        aux = aux->prox;
    }

    if (aux != NULL && strcasecmp(aux->palavra, novo->palavra) == 0) {
        removeOco(ocorrencias[aux->ocorrencias - 1], novo->palavra);
        aux->ocorrencias += 1;
        novo->ocorrencias += 1;
    } else {
        if (aux != NULL) {
            novo->prox = aux;
            aux->ant = novo;
        }
        if (ant != NULL) {
            novo->ant = ant;
            ant->prox = novo;
        }
    }

    if (ocorrencias[aux->ocorrencias - 1] == NULL) {
        //ocorrencias[aux->ocorrencias - 1] = novo;
    } else {
        //insereOco(ocorrencias[aux->ocorrencias-1], novo);
    }
}


void insere(char *p) {
    int pos;
    ELEMENTO *dic, *oco, *novo;
    novo = (ELEMENTO *)malloc(sizeof(ELEMENTO));
    strcpy(novo->palavra, p);
    novo->ocorrencias = 1;
    novo->prox = NULL;
    novo->ant = NULL;

    /*
    if (p[0] <= 'Z') {
        pos = p[0] - 'A';
    } else {
        pos = p[0] - 'a';
    }
    */

    //if ternarnio -> (condicao) ? ret_ver : ret_fal
    pos = p[0] - ((p[0] <= 'Z') ? 'A' : 'a');

    if (dicionario[pos] == NULL) {
        dicionario[pos] = novo;
        if (ocorrencias[novo->ocorrencias - 1] == NULL) {
            //ocorrencias[novo->ocorrencias - 1] = novo;
        } else {
            insereOco(ocorrencias[novo->ocorrencias-1], novo);
        }
    } else {
        insereDicOrdenado(dicionario[pos], novo);
    }
}


void escreveOcorrencias(char ordecacao) {
    int i;
    ELEMENTO *aux, *ant;
    if (ordecacao == 'c') {
        for (i = 0; i < OCO; i++) {
            printf("%d: \n", i + 1);
            if (ocorrencias[i] != NULL) {
                aux = ocorrencias[i];

                while (aux != NULL) {
                    printf("| - %s (%i)\n", aux->palavra, aux->ocorrencias);
                    aux = aux->prox;
                }
            }
        }
    } else {
        for (i = OCO - 1; i >= 0; i--) {
            printf("%d: \n", i + 1);
            if (ocorrencias[i] != NULL) {
                aux = ocorrencias[i];

                while (aux != NULL) {
                    ant = aux;
                    aux = aux->prox;
                }
                while (ant != NULL) {
                    printf("| - %s (%i)\n", ant->palavra, ant->ocorrencias);
                    ant = ant->ant;
                }
            }
        }
    }
}


void escrevePalavras(char ordecacao) {
    int i;
    ELEMENTO *aux, *ant;
    if (ordecacao == 'c') {
        for (i = 0; i < ALF; i++) {
            printf("%c: \n", i + 'A');
            if (dicionario[i] != NULL) {
                aux = dicionario[i];

                while (aux != NULL) {
                    printf("| - %s (%i)\n", aux->palavra, aux->ocorrencias);
                    aux = aux->prox;
                }
            }
        }
    } else {
        for (i = ALF - 1; i >= 0; i--) {
            printf("%c: \n", i + 'A');
            if (dicionario[i] != NULL) {
                aux = dicionario[i];

                while (aux != NULL) {
                    ant = aux;
                    aux = aux->prox;
                }
                while (ant != NULL) {
                    printf("| - %s (%i)\n", ant->palavra, ant->ocorrencias);
                    ant = ant->ant;
                }
            }
        }
    }
}


int main() {
    int i;
    for (i = 0; i < ALF; i++) {
        dicionario[i] = NULL;
    }
    for (i = 0; i < OCO; i++) {
        ocorrencias[i] = NULL;
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
    escreveOcorrencias('c');
    printf("\n\n\n\n");
    //escrevePalavras('d');
    //escreveOcorrencias('d');
    return 0;
}
