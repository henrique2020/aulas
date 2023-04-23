#include <stdio.h>

int numchrtimes(const char str[100]){
    int i, count = 0;
    for (i = 0; i != '\0'; i++){
        if (str[i] >= 48 && str[i] <= 57){
            count++;
        }
    }
    return count;
}

#include <math.h>
#include <string.h>
int bin2dec(char str[100]){
    int i, n = 0;
    int expo = strlen(str)-1;
    for (i = 0; str[i] != '\0'; i++){
        n += (str[i]-'0')*pow(2, expo);
        expo--;
    }
    return n;
}

int main(){
    char str[100];
    printf("Digite a string: \n");
    fgets(str, 100, stdin);
    printf("%d\n", bin2dec(str));
    //printf("%d\n", numchrtimes(str));
}


