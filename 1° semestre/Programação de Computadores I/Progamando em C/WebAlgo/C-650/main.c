// Autor : rique_hahn
// Data : 04/09/2021

#include <stdio.h>

int main() {
    float n1, n2, n3, media;
    scanf("%f", &n1);
    scanf("%f", &n2);
    scanf("%f", &n3);

    if(n1 == 0){
        n1 = 1;
    }
    if(n2 == 0){
        n2 = 1;
    }
    if(n3 == 0){
        n3 = 1;
    }

    media = 3/(1/n1 + 1/n2 + 1/n3);
    printf("Nota: %.1f\n", media);
    if (media < 6){
        if(n1 > n2 && n2 > n3){
            if((3/(1/n1 + 1/n2 + 1/10)) >= 6){
                float rec;
                scanf("%f", &rec);
                n3 = rec;
                media = 3/(1/n1 + 1/n2 + 1/n3);
                printf("Nota: %.1f\n", media);
            }
        }
        else{
            if(n2 < n3){
                if((3/(1/n1 + 1/10 + 1/n3)) >= 6){
                    float rec;
                    scanf("%f", &rec);
                    n2 = rec;
                    media = 3/(1/n1 + 1/n2 + 1/n3);
                    printf("Nota: %.1f\n", media);
                }
            }
            else{
                if((3/(1/10 + 1/n2 + 1/n3)) >= 6){
                    float rec;
                    scanf("%f", &rec);
                    n1 = rec;
                    media = 3/(1/n1 + 1/n2 + 1/n3);
                    printf("Nota: %.1f\n", media);
                }
            }
        }
    }

    if(media < 6){
        printf("Conceito -> 0\n");
    }
    else if(media >= 6 && media < 7){
        printf("Conceito -> 1\n");
    }
    else if(media >= 7 && media < 8){
        printf("Conceito -> 2\n");
    }
    else if(media >= 8 && media < 9){
        printf("Conceito -> 3\n");
    }
    else{
        printf("Conceito -> 4\n");
    }

    return 0;
}
