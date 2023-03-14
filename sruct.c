#include <stdio.h>
#define N 5

typedef struct pessoa {
    int id;
    char nome[15];
} Pessoa;


void imprime(Pessoa p[N]){
    int i;
    printf("Saída de dados!\n");
    for(i = 0; i < N; i++){
        printf("ID -> %d | Nome -> %s\n", p[i].id, p[i].nome);
    }
}


int main() {
    Pessoa p[N];
    int i, j, tam = 0;
    
    printf("Entrada de dados!\n");
    for(i = 0; i < N; i++){
        printf("Nº: ");
        scanf("%d", &p[i].id);
        
        printf("Nome: ");
        scanf("%s", p[i].nome);
        
        tam += 1;
        printf("\n");
        
    }
    
    imprime(p);
    for(i = 0, j = tam-1; i<j; i++, j--){
        Pessoa aux = p[i];
        p[i] = p[j];
        p[j] = aux;
    }
    
    printf("INVERSÃO!\n");
    imprime(p);
}
