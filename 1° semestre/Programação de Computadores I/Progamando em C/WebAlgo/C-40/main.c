// Autor : rique_hahn
// Data : 19/08/2021
#include <stdio.h>

int main() {
    int num, res;
    scanf("%d", &num);
    if(num%2 == 0){
        res = 0;
    }
    else{
        res = 1;
    }
    printf("%d\n", res);
    return 0;
}
