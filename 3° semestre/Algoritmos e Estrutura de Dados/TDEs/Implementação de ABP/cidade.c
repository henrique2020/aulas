#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodo{
    char cidade[100];
    struct nodo *pai;
    struct nodo *esq;
    struct nodo *dir;
} NODO;

void imprime_no(NODO *no){
    printf(" +------------------------------------\n");
    printf(" | Cidade: %s\n", no->cidade);
    printf(" | Cidade (PAI): %s\n", no->pai->cidade);
    printf(" | Cidade (FILHO DIR.): %s\n", no->dir->cidade);
    printf(" | Cidade (FILHO ESQ.): %s\n", no->esq->cidade);
    printf(" +------------------------------------");
    printf("\n\n\n");
}


void lista_cidade(NODO *no, char d){
  if (no != NULL){
    if(d == 'e'){
      lista_cidade(no->esq, d);
      printf("-> %s\n", no->cidade);
      lista_cidade(no->dir, d);
    } else if (d == 'd'){
      lista_cidade(no->dir, d);
      printf("-> %s\n", no->cidade);
      lista_cidade(no->esq, d);
    }
  }
}


NODO *criaNodo(char *cidade) {
  NODO *novo;
  novo = (NODO *) malloc(sizeof(NODO));
  strcpy(novo->cidade, cidade);
  novo->esq = NULL;
  novo->dir = NULL;
  return novo;
}


NODO *procura_cidade(NODO *no, char *cidade){
    while(no != NULL){
        if(strcasecmp(no->cidade, cidade) == 0){
            break;
        } else if (strcasecmp(cidade, no->cidade) > 0) {
            no = no->dir;
        } else if (strcasecmp(cidade, no->cidade) < 0) {
            no = no->esq;
        }
    }

    return no;
}


NODO *insere_cidade(NODO *no, char *cidade, NODO *pai){
    if (no == NULL){
        no = criaNodo(cidade);
        no->pai = pai;
    } else if (strcasecmp(cidade, no->cidade) > 0) {
        no->dir = insere_cidade(no->dir, cidade, no);
    } else if (strcasecmp(cidade, no->cidade) < 0) {
        no->esq = insere_cidade(no->esq, cidade, no);
    }

    return no;
}


void remove_cidade(NODO *no){
    if(no->esq != NULL && no->dir != NULL){
        NODO *substituto = no->esq;

        while (substituto->dir != NULL) {
            substituto = substituto->dir;
        };

        if(substituto->pai != NULL){
            substituto->dir = no->dir;
        }

        if(substituto->esq != NULL){
            substituto->esq->pai = substituto->pai;
        }


        if(no->pai != NULL){
            no->pai->esq = substituto;
            substituto->pai = no->pai;
        } else {
            substituto->pai = NULL;
        }

        if(no->dir != NULL){
            substituto->dir = no->dir;
        } else {
            substituto->dir = NULL;
        }

        free(no);

    } else {
        if(no->pai != NULL){
            NODO *aux = no->pai;
            if(strcmp(aux->esq->cidade, no->cidade) == 0){
                if(no->esq != NULL)
                    aux->esq = no->esq;
                else
                    aux->esq = no->dir;
            } else if(strcmp(aux->dir->cidade, no->cidade) == 0) {
                if(no->dir != NULL)
                    aux->dir = no->esq;
                else
                    aux->dir= no->dir;
            }
        }
        free(no);
    }

}


int main(void) {
    NODO *raiz = NULL, *no;
    int op;
    char cidade[100];

    raiz = insere_cidade(raiz, "Caxias", NULL);
    raiz = insere_cidade(raiz, "Feliz", NULL);
    raiz = insere_cidade(raiz, "Aelgrete", NULL);
    raiz = insere_cidade(raiz, "barao", NULL);
    raiz = insere_cidade(raiz, "alto feliz", NULL);
    raiz = insere_cidade(raiz, "alagoas", NULL);
    raiz = insere_cidade(raiz, "palhoca", NULL);

    do {
        printf("SELECIONE UMA DAS OPCOES ABAIXO\n");
        printf("1. INSERIR CIDADE\n");
        printf("2. CONSULTAR CIDADE\n");
        printf("3. LISTAR CIDADES\n");
        printf("4. REMOVER CIDADE\n");
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
                printf("INFORME O NOME DA CIDADE: ");
                fgets(cidade, 100, stdin);
                cidade[strlen(cidade)-1] = '\0';

                no = procura_cidade(raiz, cidade);
                if(no == NULL) {
                    raiz = insere_cidade(raiz, cidade, NULL);
                    printf("CIDADE CADASTRADA COM SUCESSO!\n");
                } else {
                    printf("CIDADE JA CADASTRADA!\n");
                }

                break;

            case 2:
                printf("| DIGITE A CIDADE QUE DESEJA CONSULTAR: ");
                fgets(cidade, 100, stdin);
                cidade[strlen(cidade)-1] = '\0';

                no = procura_cidade(raiz, cidade);
                if(no == NULL) {
                    printf("| CIDADE NAO ENCONTRADA!\n");
                } else {
                    imprime_no(no);
                }

                break;

            case 3:
                printf("| SELECIONE A ORDENACAO DESEJADA\n");
                printf("| 1. CRESCENTE [A-Z]\n");
                printf("| 2. DECRESCENTE [Z-A]\n");
                printf("OPCAO DESEJADA? ");
                scanf("%d", &op);
                getchar();

                if(op == 1) {
                    lista_cidade(raiz, 'e');
                } else if (op == 2) {
                    lista_cidade(raiz, 'd');
                } else {
                    printf("| OPCAO INVALIDA! RETORNANDO AO MENU\n");
                }

                break;

            case 4:
                printf("| DIGITE A CIDADE QUE DESEJA REMOVER: ");
                fgets(cidade, 100, stdin);
                cidade[strlen(cidade)-1] = '\0';

                no = procura_cidade(raiz, cidade);
                if(no == NULL) {
                    printf("| CIDADE NAO ENCONTRADA!\n");
                } else {
                    remove_cidade(no);
                    printf("| CIDADE REMOVIDA!\n");
                }

                break;

            default:
                printf("OPCAO INVALIDA! TENTE NOVAMENTE\n");
                break;
        }
        printf("\n\n");
    } while (op != 0);

    return 0;
}