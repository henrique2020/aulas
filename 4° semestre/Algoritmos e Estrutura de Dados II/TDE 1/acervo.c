#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct filme{
    int id;
    char titulo[200];
    int ano;
    char url[500];
    int idDirector;
} FILME;

int main(){
    int i;
    char line[900], *token;;
    FILME listaFilmes[2000];
    FILE *in = NULL;

    in = fopen("teste.txt", "r");
    i = 0;
    while(!feof(in)){
        fgets(line, 900, in);
        token = strtok(line, ";");

        while(token != NULL){
            printf("Token: %s\n", token);
            token = strtok(NULL, ";");
        }

        //fscanf(in, "%d;%s;%d;%s;%d\n", &listaFilmes[i].id, listaFilmes[i].titulo, &listaFilmes[i].ano, listaFilmes[i].url, &listaFilmes[i].idDirector);
        //printf("%d;\n%s;\n%d;\n%s;\n%d\n", listaFilmes[i].id, listaFilmes[i].titulo, listaFilmes[i].ano, listaFilmes[i].url, listaFilmes[i].idDirector);
        //i++;
    }
    fclose(in);
}
