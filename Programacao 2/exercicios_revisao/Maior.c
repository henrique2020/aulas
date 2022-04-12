#include <stdio.h>

int maior(char str[100]){
    int i, num = 0, maior = 0;
    for(i = 0; str[i] != '\0'; i++){
        if(str[i] != '#'){
            num = num*10 + (str[i] - '0');  // { Ambos funcionam, na tabela }
            //num = num*10 + (str[i] - 48); // { ASCII '0' é o caractere 48 }
        }
        else{
            if(num > maior){ maior = num; }
            num = 0;
        }
    }

    if(num > maior){ maior = num; }
    
    return maior;
}

int main(){
    //char str[100] = "121#190#250#30";
    char str[100] = "1#34";

    printf("Maior: %d\n", maior(str));
    return 0;
}