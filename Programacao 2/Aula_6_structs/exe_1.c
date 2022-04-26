#include <stdio.h>

#define N 5

typedef struct funcionario {
    int cod;
    char nome[50];
    float salario;
} FUNC;

void ordena_dados(FUNC f[N]){
    int i, j;

    FUNC aux;
    for (i = 0; i < N-1; i++){
        for (j = 0; j < N-1-i; j++){
            if(f[j].salario < f[j+1].salario){  //DECRESCENTE
                aux = f[j];
                f[j] = f[j+1];
                f[j+1] = aux;
            }
        }
    }
}

void le_dados(FUNC f[N]){
    int i;
    for (i = 0; i < N; i++){
        printf("Digite o codigo: ");
        scanf("%d", &f[i].cod);

        getchar();
        printf("Digite o nome: ");
        gets(f[i].nome);

        printf("Digite o salario: ");
        scanf("%f", &f[i].salario);
        
        printf("\n");
    }
}

void escreve_dados(FUNC f[N]){
    int i;
    for (i = 0; i < N; i++){
        printf("COD: %d | NOME: %s | SALARIO: %.2f\n", f[i].cod, f[i].nome, f[i].salario);
    }
}

int main(){
    FUNC f[N];

    le_dados(f);
    ordena_dados(f);
    escreve_dados(f);
    
    return 0;
}