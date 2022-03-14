// Autor : rique_hahn
// Data : 30/08/2021
#include <stdio.h>

int main() {
    int valor, udcm; //ucdm = Unicade, Dezena, Centena, Milhar
    int res = 0;
    scanf("%d", &valor);

    udcm = valor%10; //Unidade
    res += udcm;
    valor /= 10;

    udcm = valor%10; //Dezena
    res += udcm;
    valor /= 10;

    udcm = valor%10; //Centena
    res += udcm;

    udcm = valor/10; //Milhar
    res += udcm;

    printf("%d\n", res);
    return 0;
}
