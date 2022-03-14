// Autor : rique_hahn
// Data : 30/08/2021
#include <stdio.h>

int main() {
    float n1, n2, n3, n4, media;
    scanf("%f", &n1);
    scanf("%f", &n2);
    scanf("%f", &n3);
    scanf("%f", &n4);
    if(n1 >= n4 && n2 >= n4 && n3 >= n4){
        media = (n1+n2+n3)/3;
    }
    else if(n1 >= n3 && n2 >= n3 && n4 >= n3){
        media = (n1+n2+n4)/3;
    }
    else if(n1 >= n2 && n3 >= n2 && n4 >= n2){
        media = (n1+n3+n4)/3;
    }
    else{
        media = (n2+n3+n4)/3;
    }
    printf("%.2f\n", media);
    return 0;
}
