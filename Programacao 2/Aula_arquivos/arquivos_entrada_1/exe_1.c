#include <stdio.h>
#include <stdlib.h>

typedef struct pontos {
    float x;
    float y;
} PONTOS;


float distancia(PONTOS p1,PONTOS p2){
    return (((p1.x-p2.x)*(p1.x-p2.x))+((p1.y-p2.y)*(p1.y-p2.y)));
}


int main(){
    FILE *f = NULL;
    char arquivo [100];
    PONTOS p;

    printf("Digite o nome do arquivo: ");
    gets(arquivo);
    //fgets(arquivo, 100, stdin);

    f = fopen(arquivo, "rb");   //rb, wb, ab -> arquivos binários
    if (f == NULL){
        printf("Erro ao abrir o arquivo: %s\n", arquivo);
        exit(0);
    }
    
    /* float aux;
    while (fread(&aux, sizeof(float), 1, f)){
        printf("%.2f\n", aux);
    } */

    float soma_x = 0, soma_y = 0;
    int contador = 0;
    while (fread(&p, sizeof(PONTOS), 1, f)){
        printf("Ponto: (%.2f, %.2f)\n", p.x, p.y);
        soma_x += p.x;
        soma_y += p.y;
        contador++;
    }

    PONTOS media;
    media.x = soma_x/contador;
    media.y = soma_y/contador;
    printf("Média: (%.2f, %.2f)\n", media.x, media.y);

    rewind(f);  //retorna ao inicio do arquivo
    /*
    fseek(f, 0, SEEK_SET);   //Vai até o inicio do arquivo
    fseek(f, 0, SEEK_END);   //Vai até o fim do arquivo
    fseek(f, 0, SEEK_CUR);   //Avança/Retorna x bites do arquivo
    */

    float maior = 0;
    PONTOS maior_distancia;
    while (fread(&p, sizeof(PONTOS), 1, f)){
        float d = distancia(media, p);
        if(d > maior){
            maior = d;
            maior_distancia = p;
        }
    }
    printf("MD: (%.2f, %.2f)\n", maior_distancia.x, maior_distancia.y);

    /* FILE *out = NULL;
    out = fopen("lixo_gerado.dat", "wb");
    if(out == NULL){
        printf("Erro ao abrir o arquivo de saída\n");
        exit(0);
    } 
    
    fwrite(&media, sizeof(PONTOS), 1, out); */

    FILE *out = NULL;
    out = fopen("lixo_gerado.txt", "w");
    if(out == NULL){
        printf("Erro ao abrir o arquivo de saída\n");
        exit(0);
    } 

    fprintf(out, "%f %f\n", media.x, media.y);
    
    fclose(out);
    fclose(f);
}