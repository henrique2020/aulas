#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ID 9
#define APP_NAME 150
#define RATING 3
#define INSTALLS 9

int caracteres = ID+APP_NAME+RATING+INSTALLS;
int caracteres_id = ID*2+3;
int caracteres_name = APP_NAME+ID+3;

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


//Leitura e criação do arquivo de dados binário
void text_to_binary(char *texto, char *binario){
    FILE *arquivo_csv = fopen(texto, "r");
    FILE *arquivo_binario = fopen(binario, "wb");

    if (arquivo_csv == NULL) {
        perror("Erro ao abrir o arquivo CSV");
        return 1;
    }

    if (arquivo_binario == NULL) {
        perror("Erro ao criar o arquivo binário");
        return 1;
    }

    char linha[caracteres];
    while (fgets(linha, sizeof(linha), arquivo_csv)) {
        int tamanho_linha = strlen(linha);
        if (tamanho_linha > 0 && linha[tamanho_linha - 1] == '\n') {
            linha[tamanho_linha - 1] = ' ';
        }

        if (tamanho_linha < caracteres) {
            memset(linha + tamanho_linha, ' ', caracteres - tamanho_linha);
        }

        if (tamanho_linha > 0) {
            linha[caracteres - 1] = '\n';
        }
        fwrite(linha, sizeof(char), caracteres, arquivo_binario);
    }

    fclose(arquivo_csv);
    fclose(arquivo_binario);
}


void indice_id_bin(char *texto, char *indice) {
    FILE *arquivo_texto = fopen(texto, "r");
    FILE *arquivo_indice = fopen(indice, "wb");

    if (arquivo_texto == NULL) {
        perror("Erro ao abrir o arquivo de dados");
        return 1;
    }

    if (arquivo_indice == NULL) {
        perror("Erro ao criar o arquivo de indices (id)");
        return 1;
    }

    int n_linha = 0;
    char linha[caracteres];
    while (fgets(linha, sizeof(linha), arquivo_texto)) {
        REGISTRO *reg = le(linha);
        sprintf(linha, "%d;%d", reg->id, n_linha);
        //printf("%s\n", linha);

        int tamanho_linha = strlen(linha);
        if (tamanho_linha > 0 && linha[tamanho_linha - 1] == '\n') {
            linha[tamanho_linha - 1] = ' ';
        }

        if (tamanho_linha < caracteres_id) {
            memset(linha + tamanho_linha, ' ', caracteres_id - tamanho_linha);
        }

        if (tamanho_linha > 0) {
            linha[caracteres_id - 1] = '\n';
        }
        fwrite(linha, sizeof(char), caracteres_id, arquivo_indice);
        n_linha++;
    }

    fclose(arquivo_texto);
    fclose(arquivo_indice);
}


void indice_name_bin(char *texto, char *indice) {
    FILE *arquivo_texto = fopen(texto, "rb");
    FILE *arquivo_indice = fopen(indice, "wb");

    if (arquivo_texto == NULL) {
        perror("Erro ao abrir o arquivo de dados");
        return 1;
    }

    if (arquivo_indice == NULL) {
        perror("Erro ao criar o arquivo de indices (name)");
        return 1;
    }

    int n_linha = 0;
    char linha[caracteres];
    while (fgets(linha, sizeof(linha), arquivo_texto)) {
        REGISTRO *reg = le(linha);
        sprintf(linha, "%s;%d", reg->app_name, n_linha);
        //printf("%s\n", linha);

        int tamanho_linha = strlen(linha);
        if (tamanho_linha > 0 && linha[tamanho_linha - 1] == '\n') {
            linha[tamanho_linha - 1] = ' ';
        }

        if (tamanho_linha < caracteres_name) {
            memset(linha + tamanho_linha, ' ', caracteres_name - tamanho_linha);
        }

        if (tamanho_linha > 0) {
            linha[caracteres_name - 1] = '\n';
        }
        fwrite(linha, sizeof(char), caracteres_name, arquivo_indice);
        n_linha++;
    }

    fclose(arquivo_texto);
    fclose(arquivo_indice);
}


int main() {
    char texto[] = "data.csv";
    char bin[] = "./bins/data.bin";

    printf("CONVERTENDO O ARQUIVO DE TEXTO PARA ARQUIVO BINARIO...\n");
    text_to_binary(texto, bin);
    printf("FUNCAO text_to_binary EXECUTADA COM EXITO\n\n\n");

    printf("CRIANDO ARQUIVO DE INDICE BASEADO NO ID...\n");
    indice_id_bin(texto, "./bins/id.bin");
    printf("FUNCAO indice_id_bin EXECUTADA COM EXITO\n\n\n");

    printf("CRIANDO ARQUIVO DE INDICE BASEADO NO APP NAME...\n");
    indice_name_bin(texto, "./bins/name.bin");
    printf("FUNCAO indice_name_bin EXECUTADA COM EXITO\n\n\n");

    return 0;
}
