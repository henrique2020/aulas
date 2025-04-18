#include <stdio.h>

#define N 6  // Defina o número de vértices do grafo

void bfs(int vi, int G[N][N], int nivel[N]) {
    // Inicializa todos os níveis como -1
    for (int i = 0; i < N; i++) {
        nivel[i] = -1;
    }

    // O nível do vértice inicial é 0
    nivel[vi] = 0;

    int NivelCorrente = 0;

    while (1) {
        int trocou = 0;

        // Explora os vértices no nível atual
        for (int i = 0; i < N; i++) {
            if (nivel[i] == NivelCorrente) {
                // Para cada vizinho do vértice i
                for (int j = 0; j < N; j++) {
                    // Se há uma aresta entre i e j e j não foi visitado
                    if (G[i][j] == 1 && nivel[j] == -1) {
                        nivel[j] = NivelCorrente + 1;
                        trocou = 1;
                    }
                }
            }
        }

        // Se não houve trocas, significa que todos os vértices foram visitados
        if (trocou == 0) {
            break;
        }

        // Avança para o próximo nível
        NivelCorrente++;
    }
}


void bfs_fila(int vi, int G[N][N], int nivel[N]) {
    int fila[N], PA = 0, TD = 0; // Fila de vértices
    for (int i = 0; i < N; i++) nivel[i] = -1; // Inicializa níveis

    fila[PA++] = vi;  // Adiciona o vértice inicial à fila
    nivel[vi] = 0;     // Define o nível do vértice inicial

    while (PA != TD) { // Enquanto houver elementos na fila
        int v = fila[TD++]; // Remove o primeiro da fila

        for (int j = 0; j < N; j++) { // Percorre os vizinhos
            if (G[v][j] == 1 && nivel[j] == -1) { // Se há aresta e não visitado
                fila[PA++] = j; // Adiciona o vizinho à fila
                nivel[j] = nivel[v] + 1; // Define nível
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
    // Exemplo de grafo representado por uma matriz de adjacência
    int G[N][N] = {
        {0, 1, 0, 0, 1, 0},
        {1, 0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0, 0},
        {0, 0, 1, 0, 0, 1},
        {1, 0, 0, 0, 0, 1},
        {0, 0, 0, 1, 1, 0}
    };

    // Vetor de níveis
    int nivel[N];

    // Chama a função BFS a partir do vértice 0
    //bfs(0, G, nivel);
    bfs_fila(4, G, nivel);

    // Imprime os níveis dos vértices após a execução do BFS
    printNivel(nivel);

    return 0;
}
