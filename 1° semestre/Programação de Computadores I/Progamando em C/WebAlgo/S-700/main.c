// Autor : rique_hahn
// Data : 30/08/2021
#include <stdio.h>

int main() {
    int dinheiro, n100, n50, n20, n10, n5, n2, n1;
    scanf("%d", &dinheiro);
    //printf("%d\n", dinheiro);

    n100 = dinheiro/100;
    dinheiro = dinheiro % 100; //WebAlgo não aceita o comando '%='
    n50 = dinheiro/50;
    dinheiro = dinheiro % 50;
    n20 = dinheiro/20;
    dinheiro = dinheiro % 20;
    n10 = dinheiro/10;
    dinheiro = dinheiro % 10;
    n5 = dinheiro/5;
    dinheiro = dinheiro % 5;
    n2 = dinheiro/2;
    dinheiro = dinheiro % 2;
    n1 = dinheiro;

    printf("%d nota(s) de R$ 100,00\n", n100);
    printf("%d nota(s) de R$ 50,00\n", n50);
    printf("%d nota(s) de R$ 20,00\n", n20);
    printf("%d nota(s) de R$ 10,00\n", n10);
    printf("%d nota(s) de R$ 5,00\n", n5);
    printf("%d nota(s) de R$ 2,00\n", n2);
    printf("%d nota(s) de R$ 1,00\n", n1);
    return 0;
}
