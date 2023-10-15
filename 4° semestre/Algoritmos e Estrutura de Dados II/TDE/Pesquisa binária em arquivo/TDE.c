#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void pesquisaBinaria(FILE *binFile, char *palavra, int tamB) {
    char registro[100];
    int inicio = 0, comparacoes = 0, fim, cmp;

    clock_t start_time, end_time;
    start_time = clock();

    fseek(binFile, 0, SEEK_END);
    fim = tamB / 100 - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;

        fseek(binFile, meio * 100, SEEK_SET);
        fread(registro, sizeof(char), 100, binFile);

        char *tnome = strtok(registro, ";");
        char *tgen = strtok(NULL, ";");


        comparacoes++;
        cmp = strcasecmp(tnome, palavra);
        if (cmp == 0) {
            end_time = clock();
            double tempo = (double)(end_time - start_time) / CLOCKS_PER_SEC;
            printf("+-----------------------------------------------+ \n");
            printf("| Informacoes encontradas: \n");
            printf("| Nome: %s\n", tnome);
            printf("| Sexo: %s\n", tgen);
            printf("| \n");
            printf("| Tempo: %.9f segundos\n", tempo);
            printf("| Comparacoes: %d\n", comparacoes);
            printf("+-----------------------------------------------+ \n");
            return;
        } else if (cmp < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    printf("Nome nao encontrado.\n");
}

int main() {
    FILE *in = fopen("names.csv", "r");
    FILE *out = fopen("arquivo.bin", "wb");
    char linha[100], palavra[100];
    int tamanho = 0, tamanho_linha;

    while (fgets(linha, sizeof(linha), in)) {
        int tamanho_linha = strlen(linha);
        if (tamanho_linha > 0 && linha[tamanho_linha - 1] == '\n') {
            linha[tamanho_linha - 1] = '\0';
        }

        if (tamanho_linha < 100) {
            memset(linha + tamanho_linha, ' ', 100 - tamanho_linha);
        }

        fwrite(linha, sizeof(char), 100, out);
    }

    fclose(in);
    fclose(out);


    in = fopen("arquivo.bin", "rb");
    fseek(in, 0, SEEK_END);
    tamanho = ftell(in);

    printf("Digite o nome: ");
    scanf("%s",palavra);
    pesquisaBinaria(in, palavra, tamanho);

    fclose(in);
    return 0;
}
