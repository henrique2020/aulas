// Autor : rique_hahn
// Data : 07/09/2021

#include <stdio.h>

int main() {
    int a, b, c;
    scanf("%d", &a);
    scanf("%d", &b);
    scanf("%d", &c);

    a = a*a;
    b = b*b;
    c = c*c;

    if(a >= b && a >= c){
        if(a == (b+c)){
            printf("0\n");
        }
        else if(a > (b+c)){
            printf("1\n");
        }
        else{
            printf("2\n");
        }
    }
    else if(a <= b && b >= c){
        if(b == (a+c)){
            printf("0\n");
        }
        else if(b > (a+c)){
            printf("1\n");
        }
        else{
            printf("2\n");
        }
    }
    else{
        if(c == (a+b)){
            printf("0\n");
        }
        else if(c > (a+b)){
            printf("1\n");
        }
        else{
            printf("2\n");
        }
    }
    return 0;
}
