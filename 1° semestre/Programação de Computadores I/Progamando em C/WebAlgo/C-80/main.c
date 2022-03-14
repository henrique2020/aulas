// Autor : rique_hahn
// Data : 19/08/2021
#include <stdio.h>

int main() {
    int n1, n2;
    scanf("%d", &n1);
    scanf("%d", &n2);
    if(n1<n2){
        printf("%d\n", n1);
        printf("%d\n", n2);
    }
    else{
        printf("%d\n", n2);
        printf("%d\n", n1);
    }
    return 0;
}
