// Autor : rique_hahn
// Data : 15/09/2021

#include <stdio.h>

int main() {
    int c1, v1;
    int c2, v2;
    int c3, v3;
    int c4, v4;
    int c5, v5;

    int total;

    printf("Insira o código do candidato e em seguida o nº de votos\n");

    scanf("%d", &c1);
    scanf("%d", &v1);

    scanf("%d", &c2);
    scanf("%d", &v2);

    scanf("%d", &c3);
    scanf("%d", &v3);

    scanf("%d", &c4);
    scanf("%d", &v4);

    scanf("%d", &c5);
    scanf("%d", &v5);

    total = v1+v2+v3+v4+v5;
    float p1, p2, p3, p4, p5;

    p1 = (float)(v1*100)/total;
    p2 = (float)(v2*100)/total;
    p3 = (float)(v3*100)/total;
    p4 = (float)(v4*100)/total;
    p5 = (float)(v5*100)/total;

    printf("\n");
    printf("Candidato %d teve %d votos, representando %.1f%% de todos os votos!\n", c1, v1, p1);
    printf("Candidato %d teve %d votos, representando %.1f%% de todos os votos!\n", c2, v2, p2);
    printf("Candidato %d teve %d votos, representando %.1f%% de todos os votos!\n", c3, v3, p3);
    printf("Candidato %d teve %d votos, representando %.1f%% de todos os votos!\n", c4, v4, p4);
    printf("Candidato %d teve %d votos, representando %.1f%% de todos os votos!\n", c5, v5, p5);
    printf("\n");

    int auxv, auxc;
    for(int i = 0; i < 5; i++){
        if(v5 > v4){
            //Coloca na menor posição o maior número de votos
            auxv = v5;
            v5 = v4;
            v4 = auxv;

            //Coloca o código conforme o número de votos
            auxc = c5;
            c5 = c4;
            c4 = auxc;
        }
        if(v4 > v3){
            //Coloca na menor posição o maior número de votos
            auxv = v4;
            v4 = v3;
            v3 = auxv;

            //Coloca o código conforme o número de votos
            auxc = c4;
            c4 = c3;
            c3 = auxc;
        }
        if(v3 > v2){
            //Coloca na menor posição o maior número de votos
            auxv = v3;
            v3 = v2;
            v2 = auxv;

            //Coloca o código conforme o número de votos
            auxc = c3;
            c3 = c2;
            c2 = auxc;
        }
        if(v2 > v1){
            //Coloca na menor posição o maior número de votos
            auxv = v2;
            v2 = v1;
            v1 = auxv;

            //Coloca o código conforme o número de votos
            auxc = c2;
            c2 = c1;
            c1 = auxc;
        }
    }
    if(2*v1 >= total){
        printf("Candidato %d ganhou com %d votos!\n", c1, p1);
    }
    else{
        printf("Os candidatos mais votados foram:\n");
        printf("Candidato %d com %.1f%% dos votos!\n", c1, p1);
        printf("Candidato %d com %.1f%% dos votos!\n", c2, p2);
    }
    return 0;
}
