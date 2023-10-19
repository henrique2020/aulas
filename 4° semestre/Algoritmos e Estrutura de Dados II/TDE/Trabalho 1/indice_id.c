#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ID 9
#define APP_NAME 150
#define RATING 3
#define INSTALLS 9

int caracteres = ID+APP_NAME+RATING+INSTALLS;
int caracteres_indice = ID*2+3;

// Estrutura para o índice de campo chave
typedef struct indice_id {
    int index;
    int offset;
} INDICE_ID;

// Estrutura para os registros
typedef struct registro {
    int id;
    char app_name[APP_NAME];
    double rating;
    int installs;
} REGISTRO;


INDICE_ID *le_indice(char *linha){
    INDICE_ID *ind = (INDICE_ID *)malloc(sizeof(INDICE_ID));

    ind->index = atoi(strtok(linha, ";"));
    ind->offset = atoi(strtok(NULL, ";"));

    return ind;
}

REGISTRO *le_registro(char *linha){
    REGISTRO *reg = (REGISTRO *)malloc(sizeof(REGISTRO));

    reg->id = atoi(strtok(linha, ";"));
    strcpy(reg->app_name, strtok(NULL, ";"));
    reg->rating = atof(strtok(NULL, ";"));
    reg->installs = atoi(strtok(NULL, ";"));

    return reg;
}


int quantidade_indices(char *indice){
    FILE *arquivo_indice = fopen(indice, "rb");
    fseek(arquivo_indice, 0, SEEK_END);
    int tamanho = ftell(arquivo_indice) / caracteres_indice;

    fclose(arquivo_indice);
    return tamanho;
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

void busca_indice(char *indice, char *binario, int index) {
    FILE *arquivo_indice = fopen(indice, "rb");
    FILE *arquivo_binario = fopen(binario, "rb");

    if (arquivo_indice == NULL || arquivo_binario == NULL) {
        perror("Erro ao abrir os arquivos");
        return;
    }

    int tam = quantidade_indices(indice);
    if(index > tam || index < 1){
        printf("VALOR FORA DOS LIMITES!\n");
        return;
    }

    char linha_indice[caracteres_indice], linha_registro[caracteres];

    fseek(arquivo_indice, (index-1)*caracteres_indice, SEEK_SET);
    fread(linha_indice, caracteres_indice, 1, arquivo_indice);

    INDICE_ID *ind = le_indice(linha_indice);

    fseek(arquivo_binario, ind->offset*caracteres, SEEK_SET);
    fread(linha_registro, caracteres, 1, arquivo_binario);

    REGISTRO *reg = le_registro(linha_registro);

    exibeApp(reg);

    fclose(arquivo_indice);
    fclose(arquivo_binario);
}


int main() {
    char bin[] = "./bins/data.bin";
    char indice[] = "./bins/id.bin";

    int op, id, tam;

    do {
        printf("SELECIONE UMA DAS OPCOES ABAIXO\n");
        printf("01. EXIBIR QUANTIDADE DE INDICES\n");
        printf("02. BUSCAR APP ATRAVES DE INDICE\n");
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
                tam = quantidade_indices(indice);
                printf("O INDICE POSSUI %d REGISTROS!\n", tam);
                break;

            case 2:
                printf("INFORME O INDICE DO QUAL DESEJA BUSCAR O APP\n");
                scanf("%d", &id);
                getchar();
                busca_indice(indice, bin, id);
                break;

            default:
                printf("OPCAO INVALIDA! TENTE NOVAMENTE\n");
                break;
        }
        printf("\n\n");
    } while (op != 0);

    return 0;
}
