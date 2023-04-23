#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 5

typedef struct ponto{
    float x;
    float y;
} PONTO;


void le_pontos(PONTO *p, int n){
    int i;
    for (i = 0; i < n; i++){
        printf("Digite os pontos X e Y: ");
        scanf("%f %f", &p[i].x, &p[i].y);
    }
}


void escreve_pontos(PONTO *p, int n){
    int i;
    for (i = 0; i < n; i++){
        printf("Ponto X = %.2f\nPonto Y = %.2f\n\n", p[i].x, p[i].y);
    }
}


float distancia(PONTO p1, PONTO p2){
    float d = sqrt(((p1.x - p2.x)*(p1.x - p2.x)) + ((p1.y - p2.y)*(p1.y - p2.y)));
    return d;
}


void maior_distancia(PONTO *p, int n, PONTO *p1, PONTO *p2){
    float maior = 0, d;
    int i, j;
    for (i = 0; i < n; i++){
        for (j = i+1; j < n; j++){
            d = distancia(p[i], p[j]);
            if(d > maior){
                //maior = d;
                *p1 = p[i];
                *p2 = p[j];            
            }
        }
        
    }
}


int main(){
    PONTO p[N];
    PONTO p1, p2;

    le_pontos(p, N);
    escreve_pontos(p, N);
    maior_distancia(p, N, &p1, &p2);
 
    printf("P1| X:%f Y:%f\n", p1.x, p1.y);
    printf("P2| X:%f Y:%f\n", p2.x, p2.y);
    return 0;
}