#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct produto{
    char desc[50];
    float preco;
} PRODUTO;

int main(){
    int n, np, i, j;
    float total, quantidade;
    char arquivo[50], aux[50];
    FILE *fin = NULL;
    printf("Digite o nome do arquivo de arquivo: ");
    scanf("%s", arquivo);

    fin = fopen(arquivo, "r");
    if(fin == NULL){
        printf("Erro ao abrir o arquivo %s\n", arquivo);
        exit(0);
    }

    fscanf(fin, "%d\n", &n);
    PRODUTO *vet = (PRODUTO *)malloc(n * sizeof(PRODUTO));

    for (i = 0; i < n; i++){
        fscanf(fin, "%s %fin\n", vet[i].desc, &vet[i].preco);
        printf("%s | %.2f\n", vet[i].desc, vet[i].preco);
    }

    fscanf(fin, "%d\n", &np);
    total = 0;
    for (i = 0; i < np; i++)    {
        fscanf(fin, "%s %fin\n", aux, &quantidade);
        for (j = 0; j < n; j++){
            if(strcasecmp(aux, vet[j].desc) == 0){
                total += quantidade * vet[j].preco;
            }
        }
    }
    
    printf("Total: %.2f\n", total);
    free(vet);
    fclose(fin);

    FILE *fout = NULL;
    printf("Digite o nome do arquivo de saída: ");
    scanf("%s", arquivo);

    fout = fopen(arquivo, "w");
    if (fout == NULL){
        printf("Erro ao abrir o arquivo %s\n", arquivo);
        exit(0);
    }
    fprintf(fout, "R$ %.2f\n", total);
    close(fout);
    
}
