#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Estrutura para os nós da árvore de pesquisa
struct TreeNode {
    char installs[10];  // Tamanho máximo do campo 4
    long offset;        // Offset no arquivo de dados
    struct TreeNode *left;
    struct TreeNode *right;
};

// Função para criar um nó da árvore de pesquisa
struct TreeNode *createNode(const char *installs, long offset) {
    struct TreeNode *node = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    if (node != NULL) {
        strcpy(node->installs, installs);
        node->offset = offset;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

// Função para inserir um nó na árvore de pesquisa
struct TreeNode *insertNode(struct TreeNode *root, const char *installs, long offset) {
    if (root == NULL) {
        return createNode(installs, offset);
    }

    if (strcmp(installs, root->installs) < 0) {
        root->left = insertNode(root->left, installs, offset);
    } else if (strcmp(installs, root->installs) > 0) {
        root->right = insertNode(root->right, installs, offset);
    }

    return root;
}

// Função para pesquisar um registro na árvore de pesquisa
void searchByTreeIndex(struct TreeNode *root, const char *searchInstalls, const char *dataFileName) {
    if (root == NULL) {
        printf("Registro não encontrado.\n");
        return;
    }

    int cmp = strcmp(searchInstalls, root->installs);

    if (cmp == 0) {
        FILE *dataFile = fopen(dataFileName, "rb");
        if (dataFile == NULL) {
            perror("Erro ao abrir o arquivo de dados");
            return;
        }

        fseek(dataFile, root->offset, SEEK_SET);  // Mova o cursor para o registro correspondente no arquivo de dados

        // Leia e imprima o registro
        struct TreeNode indexEntry;
        fread(&indexEntry, sizeof(struct TreeNode), 1, dataFile);
        printf("Registro encontrado: %s\n", indexEntry.installs);

        fclose(dataFile);
    } else if (cmp < 0) {
        searchByTreeIndex(root->left, searchInstalls, dataFileName);
    } else {
        searchByTreeIndex(root->right, searchInstalls, dataFileName);
    }
}

// Função para liberar a memória da árvore de pesquisa
void freeTree(struct TreeNode *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}


int main(){


    return 0;
}
