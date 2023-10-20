#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ID 9
#define APP_NAME 150
#define RATING 3
#define INSTALLS 9

int caracteres = ID+APP_NAME+RATING+INSTALLS;

typedef struct lista_app {
    char name[APP_NAME];
    int offset;
    struct lista_app *prox;
} LISTA_APP;

typedef struct indice_rating {
    double rating;
    struct lista_app *lista;
    struct indice_rating *prox;
} INDICE_RATING;

INDICE_RATING *ind;

// Estrutura para os registros
typedef struct registro {
    int id;
    char app_name[APP_NAME];
    double rating;
    int installs;
} REGISTRO;

REGISTRO *le(char *linha){
    REGISTRO *reg = (REGISTRO *)malloc(sizeof(REGISTRO));

    reg->id = atoi(strtok(linha, ";"));
    strcpy(reg->app_name, strtok(NULL, ";"));
    reg->rating = atof(strtok(NULL, ";"));
    reg->installs = atoi(strtok(NULL, ";"));

    //printf("%d;%s;%.1f;%d\n", reg->id, reg->app_name, reg->rating, reg->installs);

    return reg;
}

LISTA_APP *insere_app(LISTA_APP *lista, LISTA_APP *app) {
    if (lista == NULL){
        lista = app;
    } else {
        lista->prox = insere_app(lista->prox, app);
    }

    return lista;
}

// Função para criar o índice em memória a partir do arquivo de dados
void indexa(char *binario) {
    FILE *arquivo_binario = fopen(binario, "rb");

    if (arquivo_binario == NULL) {
        perror("Erro ao abrir o arquivo de dados");
        return;
    }

    REGISTRO *reg;
    INDICE_RATING *aux = ind, *ant = ind, *novo;
    LISTA_APP *app;

    char linha[caracteres];
    int n_linha = 0;
    while (fread(linha, caracteres, 1, arquivo_binario) == 1) {
        //printf("%d\n", n_linha);
        reg = le(linha);

        app = (LISTA_APP *) malloc(sizeof(LISTA_APP));
        strcpy(app->name, reg->app_name);
        app->offset = n_linha;
        app->prox = NULL;

        novo = (INDICE_RATING *) malloc(sizeof(INDICE_RATING));
        novo->rating = reg->rating;

        if (ind == NULL) {
            novo->lista = app;
            novo->prox = NULL;
            ind = novo;
        } else {
            if (novo->rating < ind->rating) {
                novo->lista = app;
                novo->prox = ind;
                ind = novo;
            } else {
                aux = ind;
                ant = ind;
                while (aux != NULL && (aux->rating < novo->rating)) {
                    ant = aux;
                    aux = aux->prox;
                }
                if (aux != NULL && aux->rating == novo->rating) {
                    aux->lista = insere_app(aux->lista, app);
                } else {
                    novo->lista = app;
                    ant->prox = novo;
                    if (aux != NULL) {
                        novo->prox = aux;
                    } else {
                        novo->prox = NULL;
                    }
                }
            }
        }

        n_linha++;
    }

    fclose(arquivo_binario);
}

void lista_notas(INDICE_RATING *ind){
    INDICE_RATING *indice = ind;
    LISTA_APP *lista;
    printf("\n\n");
    printf("Notas:\n");
    while(indice != NULL){
        int rate = 0;
        lista = indice->lista;
        while(lista != NULL){
            rate++;
            lista = lista->prox;
        }

        printf("%.2f (%d APPS)\n", indice->rating, rate);
        indice = indice->prox;
    }

    printf("\n\n");
}

void lista_apps(INDICE_RATING *ind){
    INDICE_RATING *indice = ind;
    LISTA_APP *lista;
    printf("\n\n");
    printf("Lista:\n");
    while(indice != NULL){
        printf("Rating: %.2f\n", indice->rating);

        lista = indice->lista;
        while(lista != NULL){
            printf("\t| %s\n", lista->name);
            lista = lista->prox;
        }

        indice = indice->prox;
        printf("\n");
    }

    printf("\n\n");
}

int main(){
    char bin[] = "./bins/data.bin";
    ind = NULL;

    printf("PROCESSANDO INDICES. FAVOR AGUARDAR!");
    indexa(bin);
    int op, id, tam;
    char app[APP_NAME];

    do {
        printf("SELECIONE UMA DAS OPCOES ABAIXO\n");
        printf("01. LISTAR TODAS AS NOTAS\n");
        printf("02. EXIBIR APPS POR NOTA\n");
        //printf("03. EXIBIR APPS COM XX NOTA\n");
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
                lista_notas(ind);
                break;

            case 2:
                lista_apps(ind);
                break;

            default:
                printf("OPCAO INVALIDA! TENTE NOVAMENTE\n");
                break;
        }
        printf("\n\n");
    } while (op != 0);


    return 0;
}
