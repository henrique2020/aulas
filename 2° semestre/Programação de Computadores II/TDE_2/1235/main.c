#include <stdio.h>
#include <string.h>

int str(){
    char str[100] = {'U','m','a',' ','f','r','a','s','e','\0'};
    char str2[100] = "Uma frase\0";
    //printf("Digite uma frase: ");
    //scanf("%s\n", &str);
    //str[2] = '\0';
    printf("%s\n", str);
    puts(str2);
    printf("%c\n", str[4]);

    return  0;
}

int int_char(){
    int n;
    printf("Digite o valor de N: ");
    scanf("%d", &n);
    //fflush(stdin);    //Limpa os caracteres    //Só funciona no Windows
    //__fpurge(stdin);    //Limpa os caracteres    //Só funciona no Linux
    getchar();     //Limpa os caracteres    //Funciona em ambos
    char c;
    printf("Digite uma letra: ");
    scanf("%c", &c);

    printf("O valor digitado foi: %d\n", n);
    printf("A letra digitada foi: %c\n", c);
    return 0;
}

int newInfo(){
    int a = 10, b;
    printf("%d\n", a++);
    b = a++;
    printf("%d\n", a);
    printf("%d\n", b);
    // valor++ (Primeiro usa e depois aumenta)
    // ++valor (Primeiro aumenta e depois usa)
    return 0;
}

int atv(){
    char str1[100] = "Oi\0", str2[100];
    int i, k;
    for (i = 0, k = 0; str1[i] != '\0'; i++){
        str2[k++] = str1[i];
        //k++;
        str2[k++] = str1[i];
        //k++;
    }
    str2[i] = '\0';
    printf("%s\n", str2);
    return 0;
}

int exemplo(){
    char str[10];
    printf("Digite uma frase: ");
    //scanf("%s", str); //Separa pelos espaços
    //gets(str);    //Não recomendado
    fgets(str, 10, stdin);  //Mais recomendado
    printf("%s!!!\n", str);
    str[strlen(str)-1] = '\0';  //Substitui o '\n' no final
    printf("%s!!!\n", str);
}

int tamString(char str[100]){
    int tam, i;
    //for (i = 0; str[i] != '\0'; i++){ tam++; }
    for (tam = 0; str[tam] != '\0'; tam++);
    return tam;
}

int palindromo(char str[100]){
    int i;
    int tam = tamString(str);
    for (i = 0; i < tam; i++, tam--){
        if (str[i] != str[tam-i]){
            return 0;
        }
    }
    return 1;
}

int atv2(){
    char str[100];
    fgets(str, 100, stdin);
    str[strlen(str)-1] = '\0';

    if(palindromo(str)){ printf("E palindromo\n"); }
    else { printf("Nao e palindromo\n"); }
    return 0;
}

int main(){
   
    return 0;
}