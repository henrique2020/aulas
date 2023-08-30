#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define nDIRETORES 300
#define nFILMES 2000

int tam_filmes = 0;
int tam_diretores = 0;

typedef struct diretor{
    int id;
    char nome[200];
} DIRETOR;

typedef struct filme{
    int id;
    char titulo[200];
    int ano;
    char url[500];
    int idDiretor;
} FILME;

/*
FILME *procura_filme_id(FILME *filmes, int id){
    int i, tam = (sizeof(filmes) / sizeof(FILME));
    for(i = 0; i < tam; i++){
        if(filmes[i].id == id){
            return filmes[i];
        }
    }

    return NULL;
}

FILME *procura_filme_nome(FILME *filmes, char *nome){
    int i, tam = (sizeof(filmes) / sizeof(FILME));
    for(i = 0; i < tam; i++){
        if(strcasecmp(filmes[i].titulo, nome) == 0){
            return filmes[i];
        }
    }

    return NULL;
}

DIRETOR *procura_diretor_id(DIRETOR *diretores, int id){
    int i, tam = (sizeof(diretores) / sizeof(DIRETOR));
    for(i = 0; i < tam; i++){
        if(diretores[i].id == id){
            return diretores[i];
        }
    }

    return NULL;
}

DIRETOR *procura_diretor_nome(DIRETOR *diretores, char *nome){
    int i, tam = (sizeof(diretores) / sizeof(DIRETOR));
    for(i = 0; i < tam; i++){
        if(strcasecmp(diretores[i].nome, nome) == 0){
            return diretores[i];
        }
    }

    return NULL;
}
*/

FILME *le_filmes(char *arquivo){
    FILME *filmes = (FILME *)malloc(nFILMES*sizeof(FILME));
    FILE *in = NULL;

    char line[nFILMES], *token, *temp[5];
    int i, j;

    in = fopen(arquivo, "r");
    i = 0;

    while(!feof(in)){
        fgets(line, nFILMES, in);
        token = strtok(line, ";");
        j = 0;
        while(token != NULL){
            token[strcspn(token, "\n")] = 0;
            temp[j++] = token;
            token = strtok(NULL, ";\n");
        }


        for(j = 0; j < (sizeof(filmes) / sizeof(FILME)); j++){
            if(strcasecmp(filmes[j].titulo, temp[1]) == 0 || temp[1] == NULL){
                continue;
            }
        }

        strcpy(filmes[i].titulo, temp[1]);

        //Valida se a url não está em branco
        if(temp[3] != NULL) {
            strcpy(filmes[i].url, temp[3]);
        } else {
            strcpy(filmes[i].url, NULL);
        }

        //Valida se o id não está em branco
        if(temp[0] != NULL) {
            filmes[i].id = atoi(temp[0]);
        } else {
            filmes[i].id = NULL;
        }

        //Valida se o ano não está em branco
        if(temp[2] != NULL) {
            filmes[i].ano = atoi(temp[2]);
        } else {
            filmes[i].ano = NULL;
        }

        //Valida se o diretor não está em branco
        if(temp[2] != NULL) {
            filmes[i].idDiretor = atoi(temp[4]);
        } else {
            filmes[i].idDiretor = NULL;
        }

        //printf("%d;%s;%d;%s;%d\n", filmes[i].id, filmes[i].titulo, filmes[i].ano, filmes[i].url, filmes[i].idDiretor);
        i++;
    }
    fclose(in);
    tam_filmes = i;
    return filmes;
}

DIRETOR *le_diretores(char *arquivo){
    DIRETOR *diretores = (DIRETOR *)malloc(nDIRETORES*sizeof(DIRETOR));
    FILE *in = NULL;
    char line[nDIRETORES], *token, *temp[5];
    int i, j;

    in = fopen(arquivo, "r");
    i = 0;

    while(!feof(in)){
        fgets(line, nFILMES, in);
        token = strtok(line, ",");
        j = 0;
        while(token != NULL){
            token[strcspn(token, "\n")] = 0;
            temp[j++] = token;
            token = strtok(NULL, ",\n");
        }

        //Valida se o id não está em branco
        if(temp[0] != NULL) {
            diretores[i].id = atoi(temp[0]);
        } else {
            diretores[i].id = NULL;
        }

        //Valida se o nome não está em branco
        if(temp[1] != NULL) {
            strcpy(diretores[i].nome, temp[1]);
        } else {
            strcpy(diretores[i].nome, NULL);
        }

        //printf("%d;%s\n", diretores[i].id, diretores[i].nome);
        i++;
    }
    fclose(in);
    tam_diretores = i;
    return diretores;
}


void exibir_vinculo(FILME *filmes, int tF, DIRETOR *diretores, int tD){
    int i, j;
    int achou;
    for(i = 0; i < tF; i++){
        achou = 0;
        for(j = 0; j < tD; j++){
            if(filmes[i].id == diretores[j].id){
                achou = 1;
                break;
            }
        }
        printf("+---------------------------------------------------------------------+\n");

        if(achou == 0){
            printf("| NAO FOI ENCONTRADO NENHUM VINCULO ENTRE FILME E DIRETOR PARA O FILME\n");
            printf("| '%s'\n", filmes[i].titulo);
        } else {
            printf("| FILME: '%s'\n", filmes[i].titulo);
            printf("| DIRETOR: '%s'\n", diretores[j].nome);
        }
        printf("+---------------------------------------------------------------------+\n");
    }

}


int main(){
    char arquivo_filmes[100] = "movies.txt";
    FILME *filmes = le_filmes(arquivo_filmes);

    char arquivo_diretores[100] = "directors.txt";
    DIRETOR *diretores = le_diretores(arquivo_diretores);

    exibir_vinculo(filmes, tam_filmes, diretores, tam_diretores);

    return 0;
}
