#include <stdio.h>
#include <time.h>
#define N 9

int num(){
    int temp;
    printf("Informe um n°: ");
    scanf("%d", &temp);
    
    //temp = rand() % 20;
    return temp;
}

void ordena(int cartas[], int n){
    int aux;
    for (n; cartas[n] < cartas[n-1]; n--){
        printf("c1: %d, c2: %d\n", cartas[n], cartas[n-1]);
        aux = cartas[n];
        cartas[n] = cartas[n-1];
        cartas[n-1] = aux;
    }
}


void imprime(int c[]){   //Não é necessário passar o tamnho do array
    int i;
    printf("Saída de dados!\n");
    for(i = 0; i < N; i++){
        printf("%d\n", c[i]);
    }
}

int main(){
    int cartas[N], c, p, i;
  
    cartas[0] = num();
    for(i = 1; i < N; i++){
        cartas[i] = num();
        ordena(cartas, i);
        imprime(cartas);
    }
    
    printf("FIM: \n");
    imprime(cartas);
}
