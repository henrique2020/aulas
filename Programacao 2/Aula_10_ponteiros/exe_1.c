#include <stdio.h>
#include <stdlib.h>

char *gerarStr(char c, int n){
    char *str = (char *)malloc((n+1) * sizeof(char));
    int i;
    for (i = 0; i < n; i++){
        str[i] = c;
    }
    str[i] = '\0';
    return str;
}

int main(){
    int n;
    char c, *string;

    printf("Digite um caracter: ");
    scanf("%c", &c);

    printf("Digite quantas vezes ele deve aparecer: ");
    scanf("%d", &n);

    string = gerarStr(c, n);
    printf("%s\n", string);

    free(string);
    return 0;
}