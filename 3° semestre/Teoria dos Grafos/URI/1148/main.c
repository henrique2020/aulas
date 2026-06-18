#include <stdio.h>
#include <stdlib.h>

#define INF 9999

typedef struct aresta {
    int origem;
    int destino;
    int horas;
} ARESTA;

int Bellman(ARESTA arestas[], int c1, int c2, int n_cidades, int n_arestas) {
    int d[n_cidades];
    for (int i = 0; i < n_cidades; i++)
        d[i] = INF;

    d[c1] = 0;

    for (int i = 0; i < n_cidades - 1; i++) {
        for (int j = 0; j < n_arestas; j++) {
            int u = arestas[j].origem;
            int v = arestas[j].destino;
            int w = arestas[j].horas;

            if (d[u] != INF && d[v] > d[u] + w)
                d[v] = d[u] + w;
        }
    }

    return d[c2];
}

int main() {
    while (1) {
        int n_cidades, n_acordos, n_consultas;
        scanf("%d %d", &n_cidades, &n_acordos);

        if (n_cidades == 0 && n_acordos == 0)
            break;

        ARESTA arestas[n_acordos];
        for (int i = 0; i < n_acordos; i++) {
            scanf("%d %d %d", &arestas[i].origem, &arestas[i].destino, &arestas[i].horas);
            // Ajuste de índice (caso a entrada comece em 1)
            arestas[i].origem--;
            arestas[i].destino--;
        }

        scanf("%d", &n_consultas);
        for (int i = 0; i < n_consultas; i++) {
            int c1, c2, horas;
            scanf("%d %d", &c1, &c2);

            horas = Bellman(arestas, c1 - 1, c2 - 1, n_cidades, n_acordos);
            if (horas == INF)
                printf("Nao e possivel entregar a carta\n");
            else
                printf("%d\n", horas);
        }

        printf("\n");
    }

    return 0;
}
