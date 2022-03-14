// Autor : rique_hahn
// Data : 30/08/2021
#include <stdio.h>
#include <math.h>

int main() {
    int a, b, c, sp, raiz, area;
    scanf("%d", &a);
    scanf("%d", &b);
    scanf("%d", &c);

    sp = (a+b+c)/2;
    raiz =  sp*(sp-a)*(sp-b)*(sp-c);
    area = sqrt(raiz);

    printf("%d\n", area);
    return 0;
}
