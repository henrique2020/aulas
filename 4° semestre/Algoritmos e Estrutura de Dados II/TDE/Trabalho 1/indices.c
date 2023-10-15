#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ID 6
#define APP_NAME 150
#define RATING 3
#define INSTALLS 9


int caracteres = ID+APP_NAME+RATING+INSTALLS;


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


REGISTRO *pesquisaBinaria(FILE *arquivo, char *palavra, int tam) {
    char linha[caracteres];
    int inicio = 0, comparacoes = 0, fim, cmp;

    fseek(arquivo, 0, SEEK_END);
    fim = tam / caracteres;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;

        fseek(arquivo, meio*caracteres, SEEK_SET);
        fread(linha, caracteres, 1, arquivo);

        REGISTRO *reg = le(linha);

        cmp = strcasecmp(reg->app_name, palavra);
        if (cmp == 0) {
            return reg;
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


int main() {
    FILE *arquivo_csv, *arquivo_binario;
    REGISTRO *reg;
    char palavra[APP_NAME];

     //Leitura e criação do arquivo binário
    arquivo_csv = fopen("data.txt", "r");
    if (arquivo_csv == NULL) {
        perror("Erro ao abrir o arquivo CSV");
        return 1;
    }

    arquivo_binario = fopen("indice1.bin", "wb");
    if (arquivo_binario == NULL) {
        perror("Erro ao criar o arquivo binário");
        fclose(arquivo_csv);
        return 1;
    }

    char linha[caracteres];
    while (fgets(linha, sizeof(linha), arquivo_csv)) {
        int tamanho_linha = strlen(linha);
        if (tamanho_linha > 0 && linha[tamanho_linha - 1] == '\n') {
            linha[tamanho_linha - 1] = '\0';
        }

        if (tamanho_linha < caracteres) {
            memset(linha + tamanho_linha, ' ', caracteres - tamanho_linha);
        }

        fwrite(linha, sizeof(char), caracteres, arquivo_binario);
    }

    fclose(arquivo_csv);
    fclose(arquivo_binario);


    //Pesquisa Binária
    arquivo_binario = fopen("indice1.bin", "rb");
    fseek(arquivo_binario, 0, SEEK_END);
    int tamanho = ftell(arquivo_binario);
    
    printf("Digite o nome: ");
    fgets(palavra, APP_NAME, stdin);
    palavra[strcspn(palavra, "\n")] = 0;
    
    reg = pesquisaBinaria(arquivo_binario, palavra, tamanho);
    exibeApp(reg);

    fclose(arquivo_binario);

    return 0;
}
