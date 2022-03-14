// Autor : rique_hahn
// Data : 19/08/2021
#include <stdio.h>

int main() {
    int n1, n2, n3, aux;
    scanf("%d", &n1);
    scanf("%d", &n2);
    scanf("%d", &n3);

    if(n1>n2 && n1>n3){
        if(n2<n3){
            aux = n3;
            n3 = n2;
            n2 = aux;
        }
    }
    else if(n2>n1 && n2>n3){
        if(n1>n3){
            aux = n1;
            n1 = n2;
            n2 = aux;
        }
        else{
            aux = n3;
            n3 = n1;
            n1 = n2;
            n2 = aux;
        }
    }
    else{
        if(n1>n2){
            aux = n2;
            n2 = n1;
            n1 = n3;
            n3 = aux;
        }
        else{
            aux = n1;
            n1 = n3;
            n3 = aux;
        }
    }
    printf("%d\n%d\n%d\n", n1, n2, n3);
    return 0;
}
