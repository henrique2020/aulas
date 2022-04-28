#include <stdio.h>

#define P 3
#define T 4

struct piloto {
    char nome[50];
    char equipe[50];
    int tempo[T];    //Tempo em segundos
    float media;
};

typedef struct piloto PILOTO;

void le_pilotos(PILOTO p[P]){
    int i, j;
    for (i = 0; i < P; i++){
        printf("Digite o nome: ");
        gets(p[i].nome);

        printf("Digite a equipe: ");
        gets(p[i].equipe);

        p[i].media = 0;
        for (j = 0; j < T; j++){
            printf("Digite o tempo %d: ", j+1);
            scanf("%d", &p[i].tempo[j]);
            p[i].media += p[i].tempo[j];
        }

        p[i].media /= T;
        getchar();
        printf("\n");
    }
}

void escreve_pilotos(PILOTO p[P]){
    int i, j;
    for (i = 0; i < P; i++){
        printf("NOME: %s | EQUIPE: %s | TEMPOS: \n", p[i].nome, p[i].equipe);
        for (j = 0; j < T; j++){
            printf("T%d: %03d\n", j+1, p[i].tempo[j]);
        }
        printf("MEDIA: %03.2f\n", p[i].media);
        printf("\n");
    }
}

PILOTO menor_media(PILOTO p[P]){
    PILOTO m_p = p[0];
    int i;
    for (i = 1; i < P; i++){
        if(m_p.media > p[i].media){
            m_p = p[i];
        }
    }
    return m_p;
}

int main(){
    PILOTO p[P];
    PILOTO m_p;

    le_pilotos(p);
    escreve_pilotos(p);

    m_p = menor_media(p);
    printf("PILOTO: %s | EQUIPE: %s \n", m_p.nome, m_p.equipe);
    return 0;
}
