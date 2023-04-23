#include <stdio.h>

/*
struct pessoa {
    char nome[50];
    int peso;
    float altura;
};

typedef struct pessoa PESSOA;
*/

/**/
typedef struct pessoa {
    char nome[50];
    int peso;
    float altura;
} PESSOA;


int main() {
    //struct pessoa p1, p2;
    PESSOA p1, p2;
    printf("Digite o nome: ");
    gets(p1.nome);

    printf("Digite o peso: ");
    scanf("%d", &p1.peso);

    printf("Digite a altura: ");
    scanf("%f", &p1.altura);

    printf("Nome: %s | Peso: %d | Altura: %.2f\n", p1.nome, p1.peso, p1.altura);

    p2 = p1;
    printf("Nome: %s | Peso: %d | Altura: %.2f\n", p2.nome, p2.peso, p2.altura);
}
