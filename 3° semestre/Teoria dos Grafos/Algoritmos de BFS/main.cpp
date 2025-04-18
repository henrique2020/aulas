#include <stdio.h>

#define N 6  // Defina o n�mero de v�rtices do grafo

void bfs(int vi, int G[N][N], int nivel[N]) {
    // Inicializa todos os n�veis como -1
    for (int i = 0; i < N; i++) {
        nivel[i] = -1;
    }

    // O n�vel do v�rtice inicial � 0
    nivel[vi] = 0;

    int NivelCorrente = 0;

    while (1) {
        int trocou = 0;

        // Explora os v�rtices no n�vel atual
        for (int i = 0; i < N; i++) {
            if (nivel[i] == NivelCorrente) {
                // Para cada vizinho do v�rtice i
                for (int j = 0; j < N; j++) {
                    // Se h� uma aresta entre i e j e j n�o foi visitado
                    if (G[i][j] == 1 && nivel[j] == -1) {
                        nivel[j] = NivelCorrente + 1;
                        trocou = 1;
                    }
                }
            }
        }

        // Se n�o houve trocas, significa que todos os v�rtices foram visitados
        if (trocou == 0) {
            break;
        }

        // Avan�a para o pr�ximo n�vel
        NivelCorrente++;
    }
}


void bfs_fila(int vi, int G[N][N], int nivel[N]) {
    int fila[N], PA = 0, TD = 0; // Fila de v�rtices
    for (int i = 0; i < N; i++) nivel[i] = -1; // Inicializa n�veis

    fila[PA++] = vi;  // Adiciona o v�rtice inicial � fila
    nivel[vi] = 0;     // Define o n�vel do v�rtice inicial

    while (PA != TD) { // Enquanto houver elementos na fila
        int v = fila[TD++]; // Remove o primeiro da fila

        for (int j = 0; j < N; j++) { // Percorre os vizinhos
            if (G[v][j] == 1 && nivel[j] == -1) { // Se h� aresta e n�o visitado
                fila[PA++] = j; // Adiciona o vizinho � fila
                nivel[j] = nivel[v] + 1; // Define n�vel
            }
        }
    }
}


void printNivel(int nivel[N]) {
    printf("Niveis dos vertices:\n");
    for (int i = 0; i < N; i++) {
        printf("Vertice %d: Nivel %d\n", i, nivel[i]);
    }
}

int main() {
    // Exemplo de grafo representado por uma matriz de adjac�ncia
    int G[N][N] = {
        {0, 1, 0, 0, 1, 0},
        {1, 0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0, 0},
        {0, 0, 1, 0, 0, 1},
        {1, 0, 0, 0, 0, 1},
        {0, 0, 0, 1, 1, 0}
    };

    // Vetor de n�veis
    int nivel[N];

    // Chama a fun��o BFS a partir do v�rtice 0
    //bfs(0, G, nivel);
    bfs_fila(4, G, nivel);

    // Imprime os n�veis dos v�rtices ap�s a execu��o do BFS
    printNivel(nivel);

    return 0;
}
