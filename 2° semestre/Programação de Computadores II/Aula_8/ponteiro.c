#include <stdio.h>


/*
void troca(int a, int b){
    int aux = a;
    a = b;
    b = aux;
}

int main(){
    int a = 5, b = 3;
    troca(a, b);

    printf("A: %d | B: %d\n", a, b);
    
    //int *p;
    //printf("%x | %x\n", &a, p);
    //printf("A: %d | P: %d\n", a, *p);

    return 0;
}
*/

void troca(int *a, int *b){
    int aux = *a;
    *a = *b;
    *b = aux;
}

int main(){
    int a = 5; 
    int b = 8;
    
    troca(&a, &b);
    printf("A: %d | B: %d\n", a, b);
    return 0;
}