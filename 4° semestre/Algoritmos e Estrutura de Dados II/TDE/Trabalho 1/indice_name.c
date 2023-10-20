#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ID 9
#define APP_NAME 150
#define RATING 3
#define INSTALLS 9

int caracteres = ID+APP_NAME+RATING+INSTALLS;
int caracteres_name = APP_NAME+ID+3;

// Estrutura para o índice de campo app name
typedef struct indice_app_name {
    char name[APP_NAME];
    int offset;
} INDICE_APP_NAME;

// Estrutura para os registros
typedef struct registro {
    int id;
    char app_name[APP_NAME];
    double rating;
    int installs;
} REGISTRO;


INDICE_APP_NAME *le_indice(char *linha){
    INDICE_APP_NAME *ind = (INDICE_APP_NAME *)malloc(sizeof(INDICE_APP_NAME));

    strcpy(ind->name, strtok(linha, ";"));
    ind->offset = atoi(strtok(NULL, ";"));

    return ind;
}

int quantidade_indices(char *indice){
    FILE *arquivo_indice = fopen(indice, "rb");
    fseek(arquivo_indice, 0, SEEK_END);
    int tamanho = ftell(arquivo_indice) / caracteres_name;

    fclose(arquivo_indice);
    return tamanho;
}

REGISTRO *le_registro(char *linha){
    REGISTRO *reg = (REGISTRO *)malloc(sizeof(REGISTRO));

    reg->id = atoi(strtok(linha, ";"));
    strcpy(reg->app_name, strtok(NULL, ";"));
    reg->rating = atof(strtok(NULL, ";"));
    reg->installs = atoi(strtok(NULL, ";"));

    return reg;
}

INDICE_APP_NAME *pesquisaBinaria(char *indice, char *palavra, int tam) {
    FILE *arquivo_indice = fopen(indice, "rb");
    char linha[caracteres_name];
    int inicio = 0, comparacoes = 0, fim, cmp;

    fseek(arquivo_indice, 0, SEEK_END);
    fim = tam;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;

        fseek(arquivo_indice, meio*caracteres_name, SEEK_SET);
        fread(linha, caracteres_name, 1, arquivo_indice);

        INDICE_APP_NAME *ind = le_indice(linha);
        //printf("%s\n", ind->name);

        cmp = strcasecmp(ind->name, palavra);
        if (cmp == 0) {
            return ind;
        } else if (cmp < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    return NULL;
}

void exibeApp(REGISTRO *reg){
    if (reg != NULL) {
        printf("+-----------------------------------------------+ \n");
        printf("| Aplicativo: %s\n", reg->app_name);
        printf("| Nota: %.1f\n", reg->rating);
        printf("| Instalacoes: %d+\n", reg->installs);
        printf("+-----------------------------------------------+ \n");
    } else {
        printf("App nao encontrado\n");
    }
}

void exibe_indice(char *binario, int index) {
    FILE *arquivo_binario = fopen(binario, "rb");

    if (arquivo_binario == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    char linha[caracteres];

    fseek(arquivo_binario, index*caracteres, SEEK_SET);
    fread(linha, caracteres, 1, arquivo_binario);

    REGISTRO *reg = le_registro(linha);

    exibeApp(reg);

    fclose(arquivo_binario);
}

int main() {
    char bin[] = "./bins/data.bin";
    char indice[] = "./bins/name.bin";

    int op, id, tam;
    tam = quantidade_indices(indice);
    char app[APP_NAME];

    do {
        printf("SELECIONE UMA DAS OPCOES ABAIXO\n");
        printf("01. BUSCAR APP ATRAVES DO NOME\n");
        //printf("02. EXIBIR QUANTIDADE DE INDICES\n");
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
                printf("INFORME O NOME DO APP QUE DESEJA BUSCAR: ");
                fgets(app, APP_NAME+2, stdin);
                app[strcspn(app, "\n")] = 0;

                INDICE_APP_NAME *ind = pesquisaBinaria(indice, app, tam);
                if(ind != NULL){
                    exibe_indice(bin, ind->offset);
                } else {
                    printf("NENHUM VALOR RETORNADO PARA ESSE NOME DE APP\n");
                }
                break;

            case 2:
                printf("INFORME O INDICE DO QUAL DESEJA BUSCAR O APP\n");
                scanf("%d", &id);
                getchar();
                //busca_indice(indice, bin, id);
                break;

            default:
                printf("OPCAO INVALIDA! TENTE NOVAMENTE\n");
                break;
        }
        printf("\n\n");
    } while (op != 0);

    return 0;
}
