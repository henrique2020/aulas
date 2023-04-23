#include <stdio.h>

#define N 3


struct data{
    int d, m, a;
};
typedef struct data DATA;

struct aluno{
    char nome[50], sexo;
    DATA nasc;
};
typedef struct aluno ALUNO;

void le_alunos(ALUNO vet[N]){
    int i;
    for (i = 0; i < N; i++){
        printf("Nome: ");
        gets(vet[i].nome);

        printf("Sexo: ");
        scanf("%c", &vet[i].sexo);

        printf("Digite a data de nascimento: ");
        scanf("%d/%d/%d", &vet[i].nasc.d, &vet[i].nasc.m, &vet[i].nasc.a);
        
        printf("\n");
        getchar();
    }
    
}

void ordena_alunos(ALUNO vet[N]){
    int i, j;
    int a1, a2;
    ALUNO aux;
    for (i = 0; i < N-1; i++){
        for (j = 0; j < N-1-i; j++){
            a1 = vet[j].nasc.a*1000 + vet[j].nasc.m*100 + vet[j].nasc.d;
            a2 = vet[j+1].nasc.a*1000 + vet[j+1].nasc.m*100 + vet[j+1].nasc.d;
            if(a1 > a2){
                aux = vet[j];
                vet[j] = vet[j+1];
                vet[j+1] = aux;
            }
        }
        
    }
    
}

void escreve_alunos(ALUNO vet[N]){
    int i;
    for (i = 0; i < N; i++){
        printf("%s nascido em %02d/%02d/%d, é do sexo %c\n", vet[i].nome, vet[i].nasc.d, vet[i].nasc.m, vet[i].nasc.a, vet[i].sexo);

    }
}

int main(){
    ALUNO vet[N];

    le_alunos(vet);
    ordena_alunos(vet);
    escreve_alunos(vet);
}




