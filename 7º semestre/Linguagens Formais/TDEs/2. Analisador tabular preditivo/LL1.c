#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_PROD 100
#define MAX_SIMBOLOS 100
#define MAX_SENTENCAS 100
#define MAX_SENTENCAS_TAM 100

// Estrutura para armazenar as produções
typedef struct {
    char cabeca;                // Símbolo Não Terminal do Lado Esquerdo
    char corpo[MAX_SIMBOLOS];   // Símbolos do Lado Direito
    int corpo_tam;
} PRODUCAO;

// Array de Gramática
PRODUCAO producoes[MAX_PROD];
int num_producoes = 0;

// Array de Sentenças
char sentencas[MAX_SENTENCAS][MAX_SENTENCAS_TAM];
int num_sentencas = 0;

// Matrizes do Parser Preditivo
int tabela[26][26];
int conjunto_first[26][26];


void ler_arquivo(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro: Nao foi possivel abrir o arquivo '%s'.\n", filename);
        exit(1);
    }

    int ch;

    // Lê as linhas que formam a gramática
    int linhas_gramatica;
    fscanf(file, "%d", &linhas_gramatica);
    while ((ch = fgetc(file)) != '\n' && ch != EOF);
    for (int i = 0; i < linhas_gramatica; i++) {
        char linha[256];
        fgets(linha, sizeof(linha), file);

        int p = 0;
        char cabeca_atual = linha[p++];

        // Pula até o símbolo "->"
        while (linha[p] != '-' && linha[p] != '\0') p++;
        if (linha[p] == '-') p += 2;

        producoes[num_producoes].cabeca = cabeca_atual;
        producoes[num_producoes].corpo_tam = 0;

        while (linha[p] != '\0' && linha[p] != '\n') {
            if (isalpha(linha[p])) {
                //printf("CHAR: %c\n", linha[p]);
                producoes[num_producoes].corpo[producoes[num_producoes].corpo_tam++] = linha[p];
            }
            else if (linha[p] == '|') {
                //printf("OU (|)\n");
                num_producoes++;
                producoes[num_producoes].cabeca = cabeca_atual;
                producoes[num_producoes].corpo_tam = 0;
            }
            p++;
        }
        num_producoes++;
    }

    // Lê as sentenças que serão avaliadas
    fscanf(file, "%d", &num_sentencas);
    printf("%d\n", num_sentencas);
    while ((ch = fgetc(file)) != '\n' && ch != EOF);
    for (int i = 0; i < num_sentencas; i++) {
        fscanf(file, "%s", sentencas[i]);
    }

    fclose(file);
}

void construir_tabela() {
    memset(conjunto_first, 0, sizeof(conjunto_first));
    memset(tabela, -1, sizeof(tabela));

    int atualizado = 1;
    while (atualizado) {
        atualizado = 0;
        for (int i = 0; i < num_producoes; i++) {
            int cabeca_idx = producoes[i].cabeca - 'A';    // Índice da tabela ASCII
            char simbolo = producoes[i].corpo[0];

            if (islower(simbolo)) {                     // Terminal
                int t_ix = simbolo - 'a';
                if (!conjunto_first[cabeca_idx][t_ix]) {
                    conjunto_first[cabeca_idx][t_ix] = 1;
                    atualizado = 1;
                }
            } else if (isupper(simbolo)) {              // Não Terminal
                int nt_idx = simbolo - 'A';
                for (int t = 0; t < 26; t++) {
                    if (conjunto_first[nt_idx][t] && !conjunto_first[cabeca_idx][t]) {
                        conjunto_first[cabeca_idx][t] = 1;
                        atualizado = 1;
                    }
                }
            }
        }
    }

    for (int i = 0; i < num_producoes; i++) {
        int cabeca_idx = producoes[i].cabeca - 'A';
        char simbolo = producoes[i].corpo[0];

        if (islower(simbolo)) {
            tabela[cabeca_idx][simbolo - 'a'] = i;
        } else if (isupper(simbolo)) {
            int nt_idx = simbolo - 'A';
            for (int t = 0; t < 26; t++) {
                if (conjunto_first[nt_idx][t]) {
                    tabela[cabeca_idx][t] = i;
                }
            }
        }
    }
}

void analisar_sentenca(const char *sentenca) {
    char pilha[MAX_SENTENCAS_TAM * 2];
    int top = 0;

    pilha[top++] = '$';
    pilha[top++] = 'S';

    int ip = 0;
    int len = strlen(sentenca);
    int reconheceu = 0;

    while (top > 0) {
        char valor = pilha[--top];
        char simbolo = (ip < len) ? sentenca[ip] : '$';

        if (valor == '$' && simbolo == '$') {
            reconheceu = 1;
            break;
        }

        if (islower(valor) || valor == '$') {
            if (valor == simbolo) ip++;
            else break; // Erro de correspondência
        } else if (isupper(valor)) {
            if (simbolo == '$') break;

            int prod_idx = tabela[valor - 'A'][simbolo - 'a'];
            if (prod_idx == -1) break; // Erro de transição inválida

            // Empilha (em ordem reversa)
            for (int j = producoes[prod_idx].corpo_tam - 1; j >= 0; j--) {
                pilha[top++] = producoes[prod_idx].corpo[j];
            }
        }
    }

    printf("%s\n", reconheceu ? "Reconheceu" : "Nao reconheceu");
}

int main() {
    // 1. Lê o arquivo e popula os arrays de gramática e sentenças
    ler_arquivo("entrada.txt");

    // 2. Converte a gramática para a Tabela LL(1)
    construir_tabela();

    // 3. Avalia as sentenças
    for (int i = 0; i < num_sentencas; i++) {
        analisar_sentenca(sentencas[i]);
    }

    return 0;
}
