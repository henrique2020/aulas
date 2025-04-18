#include <stdio.h>
#include <stdlib.h>

#define INF 9999

/*
NÃO FUNCIONA! INCOMPLETO
*/

typedef struct aresta{
    int origem;
    int destino;
    int horas;
} ARESTA;

int Bellman(ARESTA arestas[], int s, int c2, int n_cidades, int n_arestas){
    int d[n_cidades];
    for(int i = 0; i<n_cidades; i++){
        d[i] = INF;
    }

    d[s] = 0;
    for(int i = 0; i<n_arestas; i++){
        for(int j = 0; j < n_arestas; j++){
            int c1 = arestas[j].origem, c2 = arestas[j].destino;
            if(d[c2] > d[c1]+arestas[j].horas){
                d[c2] > d[c1]+arestas[j].horas;
            }
        }
    }

    return d[s];
}


int main() {
    while(1) {
        int n_cidades, n_acordos, n_consultas;
        scanf("%d %d", &n_cidades, &n_acordos);

        if(n_cidades == n_acordos && n_cidades == 0)
            break;

        ARESTA arestas[n_acordos];
        for(int i = 0; i < n_acordos; i++){
            scanf("%d %d %d", &arestas[i].origem, &arestas[i].destino, &arestas[i].horas);
        }

        scanf("%d", &n_consultas);
        for(int i = 0; i < n_consultas; i++){
            int c1, c2, horas;
            scanf("%d %d", &c1, &c2);

            horas = Bellman(arestas, c1, c2, n_cidades, n_acordos);
            if(horas == INF)
                horas = 0;

            if(horas == -1)
                printf("Nao e possivel entregar a carta\n");
            else
                printf("%d\n", horas);
        }

        printf("\n");

    }

    return 0;
}
