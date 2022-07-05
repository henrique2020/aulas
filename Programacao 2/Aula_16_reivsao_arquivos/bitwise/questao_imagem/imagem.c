#include <stdio.h>
#pragma pack(1)

typedef struct cabecalho{
    unsigned short int tipo;
    unsigned int tamanho;
    unsigned short int r1;
    unsigned short int r2;
    unsigned int offset;
    unsigned int ncab;
    unsigned int largura;
    unsigned int altura;
    unsigned short int planos;
    unsigned short int nbits;
    unsigned int comp;
    unsigned int tam_img;
    unsigned int xres;
    unsigned int yres;
    unsigned int usados;
    unsigned int importante;
} CABECALHO;

typedef struct pixel{
    unsigned char b;
    unsigned char g;
    unsigned char r;
} PIXEL;

int main(){
    //printf("%d\n", sizeof(CABECALHO));

    unsigned char m;
    CABECALHO c;
    PIXEL p;
    int i, j;

    FILE *in = fopen("borboleta.bmp", "rb"); 
    if(in == NULL){
        printf("Erro ao abrir o arquivo de entrada\n");
        exit(0);
    }

    FILE *out = fopen("lixo.bmp", "wb");
    if(out == NULL){
        printf("Erro ao abrir o arquivo de saída\n");
        exit(0);
    }

    fread(&c, sizeof(CABECALHO), 1, in);

    fwrite(&c, sizeof(CABECALHO), 1, out);

    for(i = 0; i<c.altura; i++){
        for (j = 0; j < c.largura; j++){
            fread(&p, sizeof(PIXEL), 1, in);
            //fwrite(&p, sizeof(PIXEL), 1, out);
            m = (p.b + p.g + p.r)/3;
            p.b = 255-m; 
            p.g = m;
            p.r = 0+m;
            fwrite(&p, sizeof(PIXEL), 1, out);
        }
    }
    



    printf("Tamanho: %d\n", c.tamanho);
    printf("Tamanho (offset): %d\n", c.offset);
    printf("(A)%dpx x %dpx(L)\n", c.altura, c.largura);
    printf("Bits: %d\n", c.nbits);
    printf("Tamano (img): %d\n", c.tam_img);

    fclose(in);
    fclose(out);
}