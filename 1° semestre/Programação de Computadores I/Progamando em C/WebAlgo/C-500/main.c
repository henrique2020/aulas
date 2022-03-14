// Autor : rique_hahn
// Data : 09/09/2021

#include <stdio.h>

int main() {
    float n1, n2, n3, media;
    scanf("%f", &n1);
    scanf("%f", &n2);
    scanf("%f", &n3);

    if(n1 == 0 || n2 == 0 || n3 == 0){
        media = 0;
        printf("%.1f\n", media);
    }
    else{
        media = 3/(1/n1 + 1/n2 + 1/n3);
        printf("%.1f\n", media);
    }
    return 0;
}
