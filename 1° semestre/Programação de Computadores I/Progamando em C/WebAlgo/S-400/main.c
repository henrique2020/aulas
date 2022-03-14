// Autor : rique_hahn
// Data : 30/08/2021
#include <stdio.h>
#include <math.h>

int main() {
    int a, b, maior;
    scanf("%d", &a);
    scanf("%d", &b);
    maior = (a+b+abs(a-b))/2;
    printf("%d\n", maior);
    return 0;
}
