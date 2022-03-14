// Autor : rique_hahn
// Data : 06/09/2021

#include <stdio.h>

int main() {
    int a, b, c;
    scanf("%d", &a);
    scanf("%d", &b);
    scanf("%d", &c);
    if(a == b && a == c){
        printf("0\n");
    }
    else if ((a == b && a != c) || (a != b && a == c) || (a != b && b == c)){
        printf("1\n");
    }
    else{
        printf("2\n");
    }
    return 0;
}
