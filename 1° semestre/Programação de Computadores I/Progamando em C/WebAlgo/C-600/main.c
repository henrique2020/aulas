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
        printf("Nota: %.1f\n", media);
        if(media >= 6){
            if(media >= 6 && media < 7){
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
        }
        else{
            float rec;
            scanf("%f", &rec);
            if(n1 > n2 && n2 > n3){
                n3 = rec;
            }
            else{
                if(n2 < n3){
                    n2 = rec;
                }
                else{
                    n1 = rec;
                }
            }
            media = 3/(1/n1 + 1/n2 + 1/n3);
            printf("Nota: %.1f\n", media);
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
        }
    }
    return 0;
}
