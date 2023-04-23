#include <stdio.h>
#include <stdlib.h>

#define N 2

struct data{
    int dia;
    int mes;
    int ano;
};
typedef struct data DATA;

struct cliente{
    int codigo;
    char nome[50];
    DATA nascimento;
};
typedef struct cliente CLIENTE;


void le_cliente(CLIENTE *c, int tam){
    int i;
    for(i = 0; i < tam; i++){
        printf("COD: ");
        scanf("%d", &c[i].codigo);

        getchar();
        printf("Nome: ");
        gets(c[i].nome);

        printf("Nascimento (Y/M/D): ");
        scanf("%d-%d-%d", &c[i].nascimento.ano, &c[i].nascimento.mes, &c[i].nascimento.dia);
    }
}


void escreve_cliente(CLIENTE *c, int tam){
    int i;
    for(i = 0; i < tam; i++){
        printf("%d - %s\n", c[i].codigo, c[i].nome);
        printf("Data de nascimento: %02d/%02d/%02d\n", c[i].nascimento.dia, c[i].nascimento.mes, c[i].nascimento.mes);
    }
}


int calcula_idade(int dN, int mN, int aN, int dA, int mA, int aA){
    int idade;

    idade = aA - aN;
    if(mN > mA || (mN == mA && dN > dA)){
        idade --;
    }

    if(idade > 18){
        return 1;
    }
    else{
        return 0;
    }
}


CLIENTE *maiores_idade(CLIENTE *c, int tam, int dA, int mA, int aA, int *num_maiores){
    int i, k, cont = 0;
    for (i = 0; i < tam; i++){
        if(calcula_idade(c[i].nascimento.dia, c[i].nascimento.mes, c[i].nascimento.ano, dA, mA, aA)){
            cont++;
        }
    }

    CLIENTE *maiores = (CLIENTE *)malloc(cont * sizeof(int));
    for (i = 0, k = 0; i < tam; i++){
        if(calcula_idade(c[i].nascimento.dia, c[i].nascimento.mes, c[i].nascimento.ano, dA, mA, aA)){
            maiores[k++] = c[i];
        }
    }

    *num_maiores = cont;
    return maiores;
}


int main(){
    CLIENTE c[N];
    int num_maiores;

    le_cliente(c, N);
    escreve_cliente(c, N);

    printf("-------------------------------------------------------------------------\n");
    CLIENTE *m = maiores_idade(c, N, 23, 5, 2022, &num_maiores);
    escreve_cliente(m, num_maiores);

    free(m);
    return 0;
}
