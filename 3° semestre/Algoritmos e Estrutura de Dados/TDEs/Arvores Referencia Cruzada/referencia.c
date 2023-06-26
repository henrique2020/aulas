#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALF 26  //[A-Z] -> 26 letras 

typedef struct elemento{
    char palavra[100];
    int ocorrencias;
    struct elemento *pai;
    struct elemento *esq;
    struct elemento *dir;
} ELEMENTO;

ELEMENTO *dicionario[ALF];
int totalPalavras = 0;
int totalOcorrencias = 0;

ELEMENTO *criaNodo(char *palavra) {
    ELEMENTO *novo;
    novo = (ELEMENTO *) malloc(sizeof(ELEMENTO));
    strcpy(novo->palavra, palavra);
    novo->ocorrencias = 1;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}
ELEMENTO *inserePalavra(ELEMENTO *no, char *palavra, ELEMENTO *pai) {
    if (no == NULL){
        no = criaNodo(palavra);
        no->pai = pai;
    } else if (strcasecmp(palavra, no->palavra) > 0) {
        no->dir = inserePalavra(no->dir, palavra, no);
    } else if (strcasecmp(palavra, no->palavra) < 0) {
        no->esq = inserePalavra(no->esq, palavra, no);
    }

    return no;
}
ELEMENTO *procura(ELEMENTO *no, char *palavra){
    while(no != NULL){
        if(strcasecmp(no->palavra, palavra) == 0){
            break;
        } else if (strcasecmp(palavra, no->palavra) > 0) {
            no = no->dir;
        } else if (strcasecmp(palavra, no->palavra) < 0) {
            no = no->esq;
        }
    }

    return no;
}
ELEMENTO *removeArvore(ELEMENTO *no){
    ELEMENTO *substituto = NULL;
    if(no->esq != NULL && no->dir != NULL) {
        substituto = no->esq;

        while (substituto->dir != NULL) {
            substituto = substituto->dir;
        };

        if(substituto->pai != NULL){ substituto->dir = no->dir; }
        if(substituto->esq != NULL){ substituto->esq->pai = substituto->pai; }

        if(no->pai != NULL){
            no->pai->esq = substituto;
            substituto->pai = no->pai;
        } else { substituto->pai = NULL; }

        if(no->dir != NULL){ substituto->dir = no->dir; }
        else { substituto->dir = NULL; }
    } else {
        if(no->esq != NULL)
            substituto = no->esq;  
        else if (no->dir != NULL)
            substituto = no->dir;
        
        if(no->pai != NULL && substituto->pai != NULL){
            substituto->pai = no->pai;
            if(strcmp(no->pai->palavra, no->palavra) < 0){
                no->pai->esq = substituto;
            } else if(strcmp(no->pai->palavra, no->palavra) > 0) { 
                no->pai->dir = substituto;
            }
        }
    }

    free(no);
    return substituto;
}


void insere(char *palavra){
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
        nodo = criaNodo(palavra);
        if (dic == NULL) {
            dicionario[pos] = nodo;
        } else {
            dicionario[pos] = inserePalavra(dicionario[pos], palavra, NULL);
        }
        totalPalavras++;
        totalOcorrencias++;
    }
}
void removePalavra(char *palavra, ELEMENTO *nodo){
    totalPalavras--;
    totalOcorrencias -= nodo->ocorrencias;
    
    char letra = palavra[0];
    int pos = letra - ((letra <= 'Z') ? 'A' : 'a');
    ELEMENTO *oco, *dic;
    
    dic = dicionario[pos];
    if(dic == nodo){
        dicionario[pos] = removeArvore(nodo);
    } else {
        removeArvore(nodo);
    }
}

void imprimeNodo(ELEMENTO *no){
    printf(" +------------------------------------\n");
    printf(" | Cidade: %s\n", no->palavra);
    printf(" | Cidade (PAI): %s\n", no->pai->palavra);
    printf(" | Cidade (FILHO DIR.): %s\n", no->dir->palavra);
    printf(" | Cidade (FILHO ESQ.): %s\n", no->esq->palavra);
    printf(" +------------------------------------");
    printf("\n\n\n");
}
void escrevePalavras(ELEMENTO *no, char d){
    //E -> CRESCENTE
    //D -> DECRESCENTE
    if (no != NULL){
        if(d == 'e'){
            escrevePalavras(no->esq, d);
            printf("| %s (%03d)\n", no->palavra, no->ocorrencias);
            escrevePalavras(no->dir, d);
        } else if (d == 'd'){
            escrevePalavras(no->dir, d);
            printf("| %s (%03d)\n", no->palavra, no->ocorrencias);
            escrevePalavras(no->esq, d);
        }
    }
}
void escrevePalavrasNOcorrencia(ELEMENTO *no, int ocorrencias){
    if (no != NULL){
        escrevePalavrasNOcorrencia(no->esq, ocorrencias);
        if(no->ocorrencias == ocorrencias)
            printf("| %s\n", no->palavra);
        escrevePalavrasNOcorrencia(no->dir, ocorrencias);
    }
}


int procuraMaxOcorrencias(ELEMENTO *no, int max){
    if (no != NULL){
        if(max < no->ocorrencias)
            max = no->ocorrencias;
        procuraMaxOcorrencias(no->esq, max);
        procuraMaxOcorrencias(no->dir, max);
    }

    return max;
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
        insere(pt);
        pt = strtok(NULL, " ,;.!?");
    }
}


int main() {
    int i, op, maxOcorrencias;
    ELEMENTO *nodo;
    char *pt, palavra[50], texto[1000], letra;
    for (i = 0; i < ALF; i++) {
        dicionario[i] = NULL;
    }

    do {
        printf("SELECIONE UMA DAS OPCOES ABAIXO\n");
        printf("01. INSERIR\n");
        printf("02. CONSULTAR PALAVRA\n");
        printf("03. EXIBIR QTDE DE PALAVRAS CADASTRADAS\n");
        printf("04. EXIBIR QTDE DE OCORRENCIAS\n");
        printf("05. LISTAR PALAVRAS\n");
        printf("06. LISTAR PALAVRAS (INICIAL)\n");
        printf("07. LISTAR PALAVRAS (UMA OCORRENCIA)\n");
        printf("08. LISTAR PALAVRAS ('N' OCORRENCIAS)\n");
        printf("09. LISTAR PALAVRAS (MAXIMO DE OCORRENCIAS)\n");
        printf("10. REMOVER PALAVRA\n");
        printf("00. SAIR\n");
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
                    insere(pt);
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
                if(nodo != NULL)
                    printf("| A PALAVRA '%s' CONTEM %d OCORRENCIAS\n", nodo->palavra, nodo->ocorrencias);
                else
                    printf("| PALAVRA NAO ENCONTRADA!\n");
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

                if(op == 1){
                    for(i = 0; i < ALF; i++){
                        printf("------------------------------------------------\n");
                        printf("| INICIAL: %c\n", ('A' + i));
                        escrevePalavras(dicionario[i], 'e'); 
                    }
                } else if (op == 2){
                    for(i = ALF-1; i >=0; i--){ 
                        printf("------------------------------------------------\n");
                        printf("| INICIAL: %c\n", ('A' + i));
                        escrevePalavras(dicionario[i], 'D'); 
                    }
                }
                else
                    printf("| OPCAO INVALIDA! RETORNANDO AO MENU\n");
                
                break;

            case 6:
                printf("INFORME A LETRA INICIAL DO DICIONARIO [A-Z] QUE DESEJA LISTAR: ");
                scanf("%c", &letra);
                printf("| SELECIONE A ORDENACAO DESEJADA\n");
                printf("| 1. CRESCENTE [A-Z]\n");
                printf("| 2. DECRESCENTE [Z-A]\n");
                printf("OPCAO DESEJADA? ");
                scanf("%d", &op);
                getchar();

                i = letra - ((letra <= 'Z') ? 'A' : 'a');
                if(op == 1)
                    escrevePalavras(dicionario[i], 'e');
                else if (op == 2)
                    escrevePalavras(dicionario[i], 'd');
                else
                    printf("| OPCAO INVALIDA! RETORNANDO AO MENU\n");
                break;

            case 7:
                printf("| PALAVRAS COM APENAS 1 OCORRENCIA: \n");
               for (i = 0; i < ALF; i++) {
                   if (dicionario[i] != NULL) {
                       escrevePalavrasNOcorrencia(dicionario[i], 1);
                   }
               }
                break;

            case 8:
                printf("INFORME O NUMERO DE OCORRENCIAS [0-100] QUE DESEJA LISTAR: ");
                scanf("%d", &op);
                getchar();

                for (i = 0; i < ALF; i++) {
                   if (dicionario[i] != NULL) {
                       escrevePalavrasNOcorrencia(dicionario[i], op);
                   }
               }
                break;

            case 9:
                maxOcorrencias = 0;
                for(i = 0; i < ALF; i++){
                    maxOcorrencias = procuraMaxOcorrencias(dicionario[i], maxOcorrencias); 
                }

                printf("O MAIOR NUMERO DE OCORRENCIAS DE UMA PALAVRA E: %d\n", maxOcorrencias);
                for (i = 0; i < ALF; i++) {
                   if (dicionario[i] != NULL) {
                       escrevePalavrasNOcorrencia(dicionario[i], maxOcorrencias);
                   }
               }
                
                break;

            case 10:
                printf("| DIGITE A PALAVRA QUE DESEJA REMOVER: ");
                fgets(palavra, 50, stdin);
                palavra[strcspn(palavra, "\n")] = 0;

                letra = palavra[0];
                i = letra - ((letra <= 'Z') ? 'A' : 'a');

                nodo = procura(dicionario[i], palavra);
                if(nodo != NULL) {
                    removePalavra(palavra, nodo);
                    printf("| PALAVRA REMOVIDA COM SUCESSO!\n");
                } else { printf("| PALAVRA NAO ENCONTRADA!\n"); }
                break;


            case 11:
                insereTextosExmplo(1);
                break;

            case 12:
                insereTextosExmplo(2);
                break;

            case 13:
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
