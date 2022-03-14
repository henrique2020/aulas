// Autor : rique_hahn
// Data : 19/08/2021
#include <stdio.h>

int main() {
    int n1, n2, n3;
    scanf("%d", &n1);
    scanf("%d", &n2);
    scanf("%d", &n3);

    if(n1<n2 && n1<n3){
        printf("%d\n", n1);
        if(n2<n3){
            printf("%d\n", n2);
            printf("%d\n", n3);
        }
        else{
            printf("%d\n", n3);
            printf("%d\n", n2);
        }
    }
    else if(n2<n1 && n2<n3){
        printf("%d\n", n2);
        if(n1<n3){
            printf("%d\n", n1);
            printf("%d\n", n3);
        }
        else{
            printf("%d\n", n3);
            printf("%d\n", n1);
        }
    }
    else{
        printf("%d\n", n3);
        if(n1<n2){
            printf("%d\n", n1);
            printf("%d\n", n2);
        }
        else{
            printf("%d\n", n2);
            printf("%d\n", n1);
        }
    }
    return 0;
}
