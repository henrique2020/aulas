// Autor : rique_hahn
// Data : 06/09/2021

#include <stdio.h>
#include <math.h>

int main() {
    int a, b, c, delta, r1, r2;
    scanf("%d", &a);
    scanf("%d", &b);
    scanf("%d", &c);
    delta = (b*b)-4*a*c;
    if(a != 0 && delta >= 0){
        r1 = (-b+sqrt(delta))/(2*a);
        r2 = (-b-sqrt(delta))/(2*a);
        if (r1 >= r2){
            printf("|%d,%d\n", r2, r1);
        }
        else{
            printf("|%d,%d\n", r1, r2);
        }
    }
    else{
        printf("A equação não possui raízes reais");
    }
    return 0;
}
