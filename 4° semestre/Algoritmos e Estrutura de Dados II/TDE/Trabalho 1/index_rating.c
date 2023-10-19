#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ID 6
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

// Estrutura para os registros
typedef struct registro {
    int id;
    char app_name[APP_NAME];
    double rating;
    int installs;
} REGISTRO;

INDICE_RATING *ind = NULL;

REGISTRO *le(char *linha){
    REGISTRO *reg = (REGISTRO *)malloc(sizeof(REGISTRO));

    reg->id = atoi(strtok(linha, ";"));
    strcpy(reg->app_name, strtok(NULL, ";"));
    reg->rating = atof(strtok(NULL, ";"));
    reg->installs = atoi(strtok(NULL, ";"));

    printf("%d;%s;%.1f;%d\n", reg->id, reg->app_name, reg->rating, reg->installs);

    return reg;
}

INDICE_RATING *insere_app(INDICE_RATING *indice, LISTA_APP *app) {
    printf("insere_app\n");
    if (indice->lista == NULL){
        indice->lista = app;
    } else {
        indice->lista = insere_app(indice->lista->prox, app);
    }

    return indice->lista;
}

// Função para criar o índice em memória a partir do arquivo de dados
void indexa(const char *binario) {
    FILE *arquivo_binario = fopen(binario, "rb");

    if (arquivo_binario == NULL) {
        perror("Erro ao abrir o arquivo de dados");
        return;
    }

    REGISTRO *reg;
    INDICE_RATING *aux, *ant, *novo;

    char linha[caracteres];
    int n_linha = 0;
    while (fread(linha, caracteres, 1, arquivo_binario) == 1) {
        printf("indexa\n");
        reg = le(linha);
        aux = ind;
        ant = ind;

        novo = (INDICE_RATING *) malloc(sizeof(INDICE_RATING));
        novo->rating = reg->rating;
        novo->prox = NULL;

        LISTA_APP *app = (LISTA_APP *) malloc(sizeof(LISTA_APP));
        strcpy(app->name, reg->app_name);
        app->prox = NULL;
        app->offset = n_linha;

        if(ind == NULL){
            novo->lista = app;
            ind = novo;
        } else {
            if(reg->rating < ind->rating){
                novo->prox = ind;
                novo->lista = app;
                ind = novo;
            }
            else {
                while(aux != NULL && (aux->rating) < ind->rating){
                        break;
                    ant = aux;
                    aux = aux->prox;
                }
                novo->lista = app;
                ant->prox = novo;
                if(aux != NULL){
                    novo->prox = aux;
                }
            }
        }

        n_linha++;

        aux = ind;
        printf("Lista:\n");
        while(aux != NULL){
            printf("Rating: %.2f\n",aux->rating);

            while(aux->lista != NULL){
                printf("\t| %s\n",aux->lista->name);
                aux->lista = aux->lista->prox;
            }

            break;
            aux = aux->prox;
        }
        printf("\n\n");
        }


    fclose(arquivo_binario);
}


int main(){
    char bin[] = "./bins/data.bin";

    indexa(bin);

    return 0;
}
