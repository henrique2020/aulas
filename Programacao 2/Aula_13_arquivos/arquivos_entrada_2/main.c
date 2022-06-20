#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float busca(char *arquivo, char *matricula){
    FILE *f = NULL;
    f = fopen(arquivo, "r");
    if(f == NULL){
        printf("Error with OPEN!\n");
        exit(0);
    }
    
    char m[100];
    float media;

    while (fscanf(f, "%s %f", m, &media) == 2){
        if(strcasecmp(m, matricula) == 0){
            fclose(f);
            return media;
        }
    }
    fclose(f);
    return -1;
}

int main(){
    char arquivo[100], matricula[10];
    float media;

    printf("Digite o nome do arquivo: ");
    gets(arquivo);

    printf("Digite a matrícula: ");
    gets(matricula);

    media = busca(arquivo, matricula);
    printf("A matrícula %s teve média %.2f\n", matricula, media);
    return 0;
}