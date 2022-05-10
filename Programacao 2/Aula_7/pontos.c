//Calcular qual ponto está mais longe da origem
#include <stdio.h>
//#include <math.h>
#define N 2

typedef struct ponto {
    float x, y;
} PONTO;

void le_pontos(PONTO p[N]){
    int i;
    for (i = 0; i < N; i++){
        printf("Digite os pontos X Y: ");
        scanf("%f %f", &p[i].x, &p[i].y);
    }
}

void escreve_pontos(PONTO p[N]){
    int i;
    for (i = 0; i < N; i++){
        printf("X%d: %.2f | Y%d: %.2f\n", i+1, p[i].x, i+1, p[i].y);
    }
}

float distancia(PONTO p1, PONTO p2){
    float distancia = 0;
        
    return distancia;
}

PONTO maior_distancia(PONTO p[N]){
    PONTO m_d, origem = {0, 0};
    float d = 0, maior = 0;

    int i;
    for (i = 0; i < N; i++){
        d = distancia(p[i], origem);
        if(d > maior){
            maior = d;
            m_d = p[i];
        }
    }
    return m_d;
}

int main(){
    PONTO p[N], m_d;    //Maior distancia
    
    le_pontos(p);
    escreve_pontos(p);
    m_d = maior_distancia(p);

    printf("Maior distãncia: X:%d | Y:%d", m_d.x, m_d.y);
}