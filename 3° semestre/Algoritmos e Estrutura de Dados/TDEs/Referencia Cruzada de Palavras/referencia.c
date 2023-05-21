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
    char palavra[50];             // Palavra inserida
    int ocorrencias;          // Número de vezes que a palavra aparece
    struct ELEMENTO *proxDic; // Próxima palavra do dicionario
    struct ELEMENTO *antDic;  // Palavra anterior do dicionario
    struct ELEMENTO *proxOco; // Próxima palavra
    struct ELEMENTO *antOco;  // Palavra anterior
} ELEMENTO;

ELEMENTO *dicionario[ALF];  // Dicionário para as letras iniciais [a-z]
ELEMENTO *ocorrencias[OCO]; // Dicionário para o número de ocorrencias [1-100]
int totalPalavras = 0;
int totalOcorrencias = 0;

ELEMENTO *procura(ELEMENTO *inicio, char *palavra) {
    ELEMENTO *aux = inicio;
    while (aux != NULL && strcasecmp(aux->palavra, palavra) != 0) {
        if(aux->proxDic == NULL) { break; }
        aux = aux->proxDic;
    }

    if (aux != NULL && strcasecmp(aux->palavra, palavra) == 0){
        return aux;
    }

    return NULL;
}


void atualizaOcorrencias(int rem, int add, ELEMENTO *nodo){
    char *palavra = nodo->palavra;
    ELEMENTO *oco;

    if(rem == -1 && add == 0 && ocorrencias[add] == NULL){
        ocorrencias[add] = nodo;
        return;
    }

    if(rem >= 0 && rem < 100){
        oco = ocorrencias[rem];
        ELEMENTO *aux = oco;
        while (aux->proxOco != NULL && strcasecmp(aux->palavra, palavra) != 0) {
            aux = aux->proxOco;
        }

        if(oco == aux && strcasecmp(aux->palavra, palavra) == 0){
            ocorrencias[rem] = aux->proxOco;
        } else {
            if(aux->antOco != NULL) {
                ELEMENTO *ant = aux->antOco;
                ant->proxOco = aux->proxOco;
            }
            if(aux->proxOco != NULL) {
                ELEMENTO *prox = aux->proxOco;
                prox->antOco = aux->antOco;
            }
        }

        nodo->proxOco = NULL;
        nodo->antOco = NULL;
    }

    if(add >= 0 && add < 100){
        oco = ocorrencias[add];
        if(oco == NULL){
            ocorrencias[add] = nodo;
        } else {
            ELEMENTO *aux = oco;
            while (aux->proxOco != NULL && strcasecmp(aux->palavra, palavra) < 0) {
                aux = aux->proxOco;
            }

            if(oco == aux && strcasecmp(aux->palavra, palavra) > 0){
                nodo->proxOco = oco;
                oco->antOco = nodo;
                ocorrencias[add] = nodo;
            } else if(strcasecmp(aux->palavra, palavra) < 0) {
                if(aux->proxOco != NULL){
                    ELEMENTO *prox = aux->proxOco;
                    nodo->proxOco = prox;
                    prox->antOco = nodo;
                }
                aux->proxOco = nodo;
                nodo->antOco = aux;
            } else {
                if(aux->antOco != NULL){
                    ELEMENTO *ant = aux->antOco;
                    nodo->antOco = ant;
                    ant->proxOco = nodo;
                }
                aux->antOco = nodo;
                nodo->proxOco = aux;
            }
        }
    }
}


int removePalavra(char *palavra){
    char letra = palavra[0];
    int pos = letra - ((letra <= 'Z') ? 'A' : 'a');
    ELEMENTO *oco, *dic, *nodo;
    nodo = procura(dicionario[pos], palavra);
    if (nodo != NULL){
        //atualizando a lista de OCORRENCIAS
        int rem = nodo->ocorrencias - 1;
        oco = ocorrencias[rem];
        if(oco == nodo && strcasecmp(nodo->palavra, palavra) == 0){
            ocorrencias[rem] = nodo->proxOco;
        } else {
            if(nodo->antOco != NULL) {
                ELEMENTO *ant = nodo->antOco;
                ant->proxOco = nodo->proxOco;
            }
            if(nodo->proxOco != NULL) {
                ELEMENTO *prox = nodo->proxOco;
                prox->antOco = nodo->antOco;
            }
        }

        //atualizando a lista do DICIONARIO
        dic = dicionario[pos];
        if(dic == nodo && strcasecmp(nodo->palavra, palavra) == 0){
            dicionario[pos] = nodo->proxDic;
        } else {
            if(nodo->antDic != NULL) {
                ELEMENTO *ant = nodo->antDic;
                ant->proxDic = nodo->proxDic;
            }
            if(nodo->proxDic != NULL) {
                ELEMENTO *prox = nodo->proxDic;
                prox->antDic = nodo->antDic;
            }
        }

        totalPalavras--;
        totalOcorrencias -= nodo->ocorrencias;

        free(nodo);

        return 1;
    } else {
        return -1;
    }
}


void inserePalavra(char *palavra) {
    int pos, rem = -1, add = -1;
    ELEMENTO *dic, *nodo;
    char letra = palavra[0];
    // if ternarnio -> (condicao) ? ret_ver : ret_fal
    pos = letra - ((letra <= 'Z') ? 'A' : 'a');
    dic = dicionario[pos];

    nodo = procura(dic, palavra);
    if (nodo != NULL){
        rem = nodo->ocorrencias - 1;
        nodo->ocorrencias++;
        totalOcorrencias++;
    } else {
        nodo = (ELEMENTO *)malloc(sizeof(ELEMENTO));
        strcpy(nodo->palavra, palavra);
        nodo->ocorrencias = 1;
        nodo->proxDic = NULL;
        nodo->antDic = NULL;

        if (dic == NULL) {
            dicionario[pos] = nodo;
        } else {
            ELEMENTO *aux = dic;
            while (aux->proxDic != NULL && strcasecmp(aux->palavra, palavra) < 0) {
                aux = aux->proxDic;
            }

            if(dic == aux && strcasecmp(aux->palavra, palavra) > 0){
                nodo->proxDic = dic;
                dic->antDic = nodo;
                dicionario[pos] = nodo;
            } else if(strcasecmp(aux->palavra, palavra) < 0) {
                if(aux->proxDic != NULL){
                    ELEMENTO *prox = aux->proxDic;
                    nodo->proxDic = prox;
                    prox->antDic = nodo;
                }
                aux->proxDic = nodo;
                nodo->antDic = aux;
            } else {
                if(aux->antDic != NULL){
                    ELEMENTO *ant = aux->antDic;
                    nodo->antDic = ant;
                    ant->proxDic = nodo;
                }
                aux->antDic = nodo;
                nodo->proxDic = aux;
            }
        }
        totalPalavras++;
        totalOcorrencias++;
    }

    add = nodo->ocorrencias - 1;
    atualizaOcorrencias(rem, add, nodo);
}


void escreveOcorrencias(char ordecacao) {
    int i;
    ELEMENTO *aux, *ant;
    if (ordecacao == 'c') {
        for (i = 0; i < OCO; i++) {
        printf("%02.d: \n", i + 1);
            if (ocorrencias[i] != NULL) {
                aux = ocorrencias[i];

                while (aux != NULL) {
                    printf("| - %s (%i)\n", aux->palavra, aux->ocorrencias);
                    aux = aux->proxOco;
                }
            }
        }
    } else {
        for (i = OCO - 1; i >= 0; i--) {
            printf("%02.d: \n", i + 1);
            if (ocorrencias[i] != NULL) {
                aux = ocorrencias[i];

                while (aux != NULL) {
                    ant = aux;
                    aux = aux->proxOco;
                }
                while (ant != NULL) {
                    printf("| - %s (%i)\n", ant->palavra, ant->ocorrencias);
                    ant = ant->antOco;
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
                int c = 0;
                while (aux != NULL) {
                    c++;
                    printf("| - %s\n", aux->palavra, aux->ocorrencias);
                    aux = aux->proxDic;
                    if (c == 10)
                        break;
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
                    aux = aux->proxDic;
                }
                while (ant != NULL) {
                    printf("| - %s\n", ant->palavra);
                    ant = ant->antDic;
                }
            }
        }
    }
}


void insereTextosExmplo(int t){
    char t1[1000] = {"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nulla sit amet bibendum metus. Nulla auctor justo et risus ullamcorper, ut interdum est consectetur. Suspendisse fringilla, nunc et lacinia feugiat, ex erat convallis felis, vel ultricies tortor ligula at neque. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia curae; Nunc eu velit et orci venenatis efficitur. In hac habitasse platea dictumst. Nullam non orci ac est iaculis pulvinar. Aenean non dui ut ipsum interdum tincidunt id eget nisl. Mauris viverra justo vel erat tempor, eget euismod sapien euismod. Proin facilisis facilisis semper. Donec in metus id turpis ullamcorper pharetra sed nec nulla."};
    char t2[1000] = {"Curabitur tincidunt eleifend facilisis. Sed eleifend tortor vitae orci lacinia, sed commodo arcu aliquam. Ut dictum sapien eros, ac varius tortor gravida in. Vestibulum vel tincidunt elit. Nunc consectetur lorem ac nibh malesuada semper. In eu nulla condimentum, suscipit justo et, condimentum eros. Phasellus vitae convallis nunc. Sed iaculis elit nec risus congue, eget consectetur erat euismod. Praesent quis nibh non orci eleifend aliquam. Fusce varius, purus sit amet volutpat semper, massa nunc elementum massa, eget malesuada libero metus vitae ipsum. Integer dignissim semper enim in consectetur. Nunc posuere tincidunt neque, vitae feugiat elit fringilla non."};
    char t3[1000] = {"Pellentesque aliquet tincidunt odio, id consectetur justo laoreet vel. Fusce ullamcorper lobortis velit. Nulla facilisi. Maecenas iaculis sem sed orci bibendum pellentesque. Curabitur id nibh ac mi consectetur consequat eu ac libero. Donec faucibus iaculis leo, non vulputate arcu molestie id. Quisque venenatis erat vel massa fermentum fringilla. Sed gravida auctor neque, eu sollicitudin ante lobortis at. Integer malesuada, neque ac finibus cursus, sapien nulla tristique enim, ut vulputate justo tellus sit amet orci. Aliquam erat volutpat. Mauris efficitur viverra dui, ut interdum orci pellentesque id. Nulla sed est vitae dolor consequat pretium. Aenean eu ligula vel justo facilisis egestas."};

    char texto[1000];
    if (t == 1)
        strcpy(texto, t1);
    else if (t == 2)
        strcpy(texto, t2);
    else
        strcpy(texto, t3);

    char *pt = strtok(texto, " ,;.!?");
    while(pt != NULL){
        pt[strcspn(pt, "\n")] = 0;
        inserePalavra(pt);
        pt = strtok(NULL, " ,;.!?");
    }
}



int main() {
    int i, op;
    ELEMENTO *nodo;
    char *pt, palavra[50], texto[1000], letra;
    for (i = 0; i < ALF; i++) {
        dicionario[i] = NULL;
    }

    do {
        printf("SELECIONE UMA DAS OPCOES ABAIXO\n");
        printf("1. INSERIR\n");
        printf("2. CONSULTAR PALAVRA\n");
        printf("3. EXIBIR QTDE PALAVRAS CADASTRADAS\n");
        printf("4. EXIBIR QTDE DE OCORRENCIAS\n");
        printf("5. LISTAR PALAVRAS\n");
        printf("6. LISTAR OCORRENCIAS\n");
        printf("7. REMOVER PALAVRA\n");
        printf("0. SAIR\n");
        printf("OPCAO DESEJADA? ");
        scanf("%d", &op);
        getchar();

        printf("\n\n");

        switch(op) {
            case 0:
                printf("SAINDO\n");
                exit(0);
                break;

            case 1:
                printf("FORNCECA UMA PALAVRA OU TEXTO (PALAVRAS) PARA SER INSERIDA: ");
                fgets(texto, 1000, stdin);

                pt = strtok(texto, " ,;.!?");
                while(pt != NULL){
                    pt[strcspn(pt, "\n")] = 0;
                    inserePalavra(pt);
                    pt = strtok(NULL, " ,;.!?");
                }

                printf("| AS PALAVRAS DO TEXTO FORAM INSERIDAS COM SUSCESSO\n");
                break;

            case 2:
                printf("| DIGITE A PALAVRA QUE DESEJA CONSULTAR: ");
                fgets(palavra, 50, stdin);
                palavra[strcspn(palavra, "\n")] = 0;

                letra = palavra[0];
                i = letra - ((letra <= 'Z') ? 'A' : 'a');

                nodo = procura(dicionario[i], palavra);
                if(nodo == NULL)
                    printf("| PALAVRA NAO ENCONTRADA!\n");
                else
                    printf("| A PALAVRA '%s' CONTEM %d OCORRENCIAS\n", nodo->palavra, nodo->ocorrencias);
                break;

            case 3:
                printf("| FORAM CADASTRADAS %d PALAVRAS!\n", totalPalavras);
                break;

            case 4:
                printf("| FORAM CADASTRADAS %d PALAVRAS (OCORRENCIAS)!\n", totalOcorrencias);
                break;

            case 5:
                printf("| SELECIONE A ORDENACAO DESEJADA\n");
                printf("| 1. CRESCENTE [A-Z]\n");
                printf("| 2. DECRESCENTE [Z-A]\n");
                printf("OPCAO DESEJADA? ");
                scanf("%d", &op);
                getchar();

                if(op == 1)
                    escrevePalavras('c');
                else if (op == 2)
                    escrevePalavras('d');
                else
                    printf("| OPCAO INVALIDA! RETORNANDO AO MENU\n");
                break;

            case 6:
                printf("| SELECIONE A ORDENACAO DESEJADA\n");
                printf("| 1. CRESCENTE [0-100]\n");
                printf("| 2. DECRESCENTE [100-0]\n");
                printf("OPCAO DESEJADA? ");
                scanf("%d", &op);
                getchar();

                if(op == 1)
                    escreveOcorrencias('c');
                else if (op == 2)
                    escreveOcorrencias('d');
                else
                    printf("| OPCAO INVALIDA! RETORNANDO AO MENU\n");
                break;

            case 7:
                printf("| DIGITE A PALAVRA QUE DESEJA REMOVER: ");
                fgets(palavra, 50, stdin);
                palavra[strcspn(palavra, "\n")] = 0;

                if(removePalavra(palavra) == 1)
                    printf("| PALAVRA REMOVIDA COM SUCESSO!\n");
                else
                    printf("| PALAVRA NAO ENCONTRADA!\n");
                break;

            case 8:
                insereTextosExmplo(1);
                break;

            case 9:
                insereTextosExmplo(2);
                break;

            case 10:
                insereTextosExmplo(3);
                break;

            default:
                printf("OPCAO INVALIDA! TENTE NOVAMENTE\n");
                break;
        }
        printf("\n\n");
    } while (op != 0);

    return 0;
}
