#include <stdio.h>
#define N 9

int menu(){
    int temp;
    printf("1. Adicionar uma carta\n");
    printf("2. Adicionar todas cartas\n");
    printf("2. Ver lista\n");
    printf("3. Ver lista invertida\n");
    printf("0. Sair\n");
    printf("Selecione uma opcao: ");

    scanf("%d", &temp);
    getchar();
    printf("\n");

    if(temp >= 0 && temp <= 4){
        return temp;
    } else {
        printf("\t+---------------------------------+\n");
        printf("\t| VALOR INVALIDA! TENTE NOVAMENTE |\n");
        printf("\t+---------------------------------+\n\n");
        return menu();
    }
}


int num(){
    int temp;
    printf("Informe um numero entre 1 e 13: ");

    scanf("%d", &temp);
    getchar();
    printf("\n");

    if(temp >= 1 && temp <= 13){
        return temp;
    } else {
        printf("\t+---------------------------------+\n");
        printf("\t| VALOR INVALIDO! TENTE NOVAMENTE |\n");
        printf("\t+---------------------------------+\n\n");
        return num();
    }
}


void ordena(int cartas[], int n){
    int aux;
    for (n; cartas[n] < cartas[n-1]; n--){
        //printf("c1: %d, c2: %d\n", cartas[n], cartas[n-1]);
        aux = cartas[n];
        cartas[n] = cartas[n-1];
        cartas[n-1] = aux;
    }
}


void imprime(int c[], int tam, int ordem){   //Não é necessário passar o tamnho do array
    int i;
    if(tam != 0){
        if(ordem == 1){
            for(i = 0; (i < tam && c[i] != 0); i++){
                printf("%d ", c[i]);
            }
        } else if (ordem == 2){
            for(i = tam-1; i >= 0 ; i--){
                if(c[i] != 0) {
                    printf("%d ", c[i]);
                }
            }
        }
        printf("\n\n");
    } else {
        printf("\t+-------------------------------+\n");
        printf("\t| NENHUMA CARTA INSERIDA AINDA! |\n");
        printf("\t+-------------------------------+\n\n");
    }
}


int main(){
    int cartas[N];
    int c = 0, op, i;

    int rep = 1;
    while(rep){
        op = menu();

        switch(op){
            case 1:
                if (c < N){
                    cartas[c] = num();
                    ordena(cartas, c);
                    c++;
                } else {
                    printf("\t+--------------------------------------------+\n");
                    printf("\t| VOCE NAO PODE ADICIONAR MAIS NENHUMA CARTA |\n");
                    printf("\t+--------------------------------------------+\n\n");
                }
                break;
            case 2:
                if (c < N){
                    for(i = c; i < N; i++){
                        cartas[c] = num();
                        ordena(cartas, c);
                        c++;

                    }
                } else {
                    printf("\t+--------------------------------------------+\n");
                    printf("\t| VOCE NAO PODE ADICIONAR MAIS NENHUMA CARTA |\n");
                    printf("\t+--------------------------------------------+\n\n");
                }
                break;
            case 3:     //Imprime as cartas em ordem crescente
                imprime(cartas, c, 1);
                break;
            case 4:     //Imprime as cartas em ordem decrescente
                imprime(cartas, c, 2);
                break;
            case 0:
                printf("Você decidiu sair do programa!");
                rep = 0;
                break;
        }
    }
}
