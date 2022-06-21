#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct funcionario {
    char cpf[20];
    char nome[100];
    float salario;
    char setor[50];
} FUNCIONARIO;

FUNCIONARIO *le_funcionarios(char *arquivo, int *nf){
    int n, i;
    FILE *F = NULL;
    F = fopen(arquivo, "r");
    if (F == NULL){
        printf("Error with opne file in read mode!\n");
        exit(0);
    }
    fscanf(F, "%d\n", &n);
    printf("NF: %d\n", n);
    
    FUNCIONARIO *v = (FUNCIONARIO *)malloc(n*sizeof(FUNCIONARIO));
    for(i = 0; i<n; i++){
        fscanf(F, "%s\n", v[i].cpf);
        fgets(v[i].nome, 100, F);
        v[i].nome[strlen(v[i].nome)-1] = '\0';
        fscanf(F, "%f\n", &v[i].salario);
        fscanf(F, "%s\n", v[i].setor);

        printf("%s (%s) |%s| = R$ %0.2f\n", v[i].nome, v[i].cpf, v[i].setor, v[i].salario);
    }
    fclose(F);

    *nf = n;
    return v;
}


void escreve_funcionarios(char *arquivo, FUNCIONARIO *v, int nf){
    int i, j;

    for(i = 0; i<nf-1; i++){
        for(j = 0; j<nf-1; j++){
            if(strcasecmp(v[j].nome, v[j+1].nome) > 0){
                FUNCIONARIO aux = v[j];
                v[j] = v[j+1];
                v[j+1] = aux;
            }
        }
    }

    FILE *F = NULL;
    F = fopen(arquivo, "w");
    if (F == NULL){
        printf("Error with opne file in write mode!\n");
        exit(0);
    }

    for (i = 0; i < nf; i++){
        fprintf(F, "%s;%s;%s;%0.2f\n", v[i].cpf, v[i].nome, v[i].setor, v[i].salario);
    }
    fclose(F);
}


int main(){
    int nf;
    char entrada[100] = "entrada.txt";
    char saida[100] = "saida.txt";
    
    FUNCIONARIO *v = le_funcionarios(entrada, &nf);
    escreve_funcionarios(saida, v, nf);

    return 0;
}