#include <stdio.h>
#define N 5

struct horario{
    int h, m, s;
};
typedef struct horario HORARIO;

void le_horarios(HORARIO vet[N]){
    int i;
    for (i = 0; i < N; i++){
        printf("Digite o horário: ");
        scanf("%d:%d:%d", &vet[i].h, &vet[i].m, &vet[i].s);
    }
}

void escreve_horarios(HORARIO vet[N]){
    int i;
    for (i = 0; i < N; i++){
        printf("Horário: %02d:%02d:%02d\n", vet[i].h, vet[i].m, vet[i].s);
    }
    
}

int maior_horario(HORARIO vet[N]){
    int i, pos, maior, aux;
    maior = 0;
    pos = 0;
    for (i = 0; i < N; i++){
        aux = vet[i].h*3600 + vet[i].m*60 + vet[i].s;
        if(aux > maior){
            maior = aux;
            pos = i;
        }
    }
    return pos;
}

int main(){
    HORARIO vet[N];
    int m_h;    //Maior horário
    le_horarios(vet);
    escreve_horarios(vet);
    
    printf("\n");
    m_h = maior_horario(vet);
    printf("Maior horário: %02d:%02d:%02d", vet[m_h].h, vet[m_h].m, vet[m_h].s);
}
