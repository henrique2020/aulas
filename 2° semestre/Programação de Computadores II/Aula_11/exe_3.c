#include<stdio.h>
#include<stdlib.h>

#define N 5

struct naonulo{
  int num; 
  int lin; 
  int col;
};
typedef struct naonulo NAONULOS;

void le_vetor(int mat[N][N]){
    int i, j;
    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            printf("Digite um N: ");
            scanf("%d", &mat[i][j]);
        }
    }
}

void escreve_vetor(NAONULOS *vet, int tam){
	int i;
	for(i=0; i<tam; i++){
		printf("Valor: %d	Linha: %d	Coluna: %d\n", vet[i].num, vet[i].lin, vet[i].col);	
	}
}

NAONULOS *cria_vetor(int mat[N][N], int *tam){
    int i, j, cont, k;
    NAONULOS *vet = NULL;
    cont = 0;
    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            if(mat[i][j] != 0){
                cont++;
            }
        }
    }
    vet = (NAONULOS *)malloc(cont*sizeof(NAONULOS));
    
    k = 0;
    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            if(mat[i][j] != 0){
                vet[k].num = mat[i][j];
                vet[k].lin = i;
                vet[k].col = j;
                k++;
            }
        }
    }
    return vet;
}

void dois_maiores(NAONULOS *vet, int tam, NAONULOS *m1, NAONULOS *m2){
    int i;
    if(vet[0].num > vet[1].num){
        *m1 = vet[0];
        *m2 = vet[1];
    }
    else{
        *m1 = vet[1];
        *m2 = vet[0];
    }

    for(i = 2; i < tam; i++){
        if(vet[i].num > m1->num){
            *m2 = *m1;
            *m1 = vet[i];
        }
        else if(vet[i].num > m2->num){
            *m2 = vet[i];
        }
    }

    printf("Valor: %d	Linha: %d	Coluna: %d\n", m1->num, m2->lin, m2->col);
    printf("Valor: %d	Linha: %d	Coluna: %d\n", m2->num, m2->lin, m2->col);
}

int main(){
    int mat[N][N];
    int tam;

    le_vetor(mat);
    NAONULOS *v = NULL;

    v = cria_vetor(mat, &tam);
    escreve_vetor(v, tam);

    NAONULOS m1, m2;
    dois_maiores(v, tam, &m1, &m2);

    free(v);
}