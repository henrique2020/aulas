// Autor : rique_hahn
// Data : 07/09/2021

#include <stdio.h>
#include <math.h>

int main() {
    int l1, l2, l3, sp, raiz, area;
    scanf("%d", &l1);
    scanf("%d", &l2);
    scanf("%d", &l3);

    if ((l1 <= (l2+l3)) && (l2 <= (l1+l3)) && (l3 <= (l1+l2))){
        sp = (l1+l2+l3)/2;
        raiz =  sp*(sp-l1)*(sp-l2)*(sp-l3);
        area = sqrt(raiz);

        printf("%d\n", area);
    }
    else{
        printf("-1\n");
    }
    return 0;
}
