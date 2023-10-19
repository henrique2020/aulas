#include <stdio.h>
#include <string.h>

// Estrutura para o índice em memória
struct MemoryIndex {
    char field3[64];  // Tamanho máximo do campo 3
    long offset;      // Offset no arquivo de dados
};

// Função para criar o índice em memória a partir do arquivo de dados
void createMemoryIndex(const char *dataFileName, struct MemoryIndex *memoryIndex, int *indexSize) {
    FILE *dataFile = fopen(dataFileName, "rb");

    if (dataFile == NULL) {
        perror("Erro ao abrir o arquivo de dados");
        return;
    }

    struct MemoryIndex indexEntry;

    *indexSize = 0;  // Tamanho inicial do índice

    while (fread(&indexEntry, sizeof(struct MemoryIndex), 1, dataFile) == 1) {
        memoryIndex[*indexSize] = indexEntry;
        (*indexSize)++;
    }

    fclose(dataFile);
}

// Função para pesquisar um registro no arquivo de dados usando o índice em memória
void searchByMemoryIndex(const struct MemoryIndex *memoryIndex, int indexSize, const char *searchField3, const char *dataFileName) {
    for (int i = 0; i < indexSize; i++) {
        if (strcmp(memoryIndex[i].field3, searchField3) == 0) {
            FILE *dataFile = fopen(dataFileName, "rb");
            if (dataFile == NULL) {
                perror("Erro ao abrir o arquivo de dados");
                return;
            }

            fseek(dataFile, memoryIndex[i].offset, SEEK_SET);  // Mova o cursor para o registro correspondente no arquivo de dados

            // Leia e imprima o registro
            struct MemoryIndex indexEntry;
            fread(&indexEntry, sizeof(struct MemoryIndex), 1, dataFile);
            printf("Registro encontrado: %s\n", indexEntry.field3);

            fclose(dataFile);
            return;  // Saia após encontrar o registro
        }
    }

    printf("Registro não encontrado.\n");
}
