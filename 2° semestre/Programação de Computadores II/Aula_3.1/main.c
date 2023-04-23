#include<stdio.h>

/*int converte(char str[100]){
    int n = 0;
    int i;
    for (i = 0; str[i] != '\0'; i++){
        n = n*10+(str[i] - '0');
    }
    return n;
    
}*/

void converte(int n, char str[100]){
    int i = 0, resto;
    while (n > 0){
        resto = n%10;
        str[i++] = resto + '0';
        n/=10;
    }
    //printf("%s\n", str);
    
    int j, k, aux;
    for (j = i-1, k = 0 ; k < j; j--, k++){
        aux = str[k];
        str[k] = str[j];
        str[j] = aux;
    }
    str[i] = '\0';
}

int main(){
    char str[100];
    //printf("Digite uma string\n");
    //scanf("%s", str);
    //printf("Convertido %d\n", converte(str));

    int n;
    printf("Digite o valor: ");
    scanf("%d", &n);
    converte(n, str);
    printf("%s\n", str);
}