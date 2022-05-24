#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char *aleatoria(int n){
    char *str = (char *)malloc((n+1) * sizeof(char));
    int i, type;
    srand(time(NULL));
    for (i = 0; i < n; i++){
        type = rand()%3;
        /*if(type == 0){
            str[i] = rand()%26+'a';
        }
        else if(type == 1){
            str[i] = rand()%26+'A';
        }
        else{
            str[i] = rand()%10+'0';
        }*/
        switch (type){
        case 0:
            str[i] = rand()%26+'a';
            break;

        case 1:
            str[i] = rand()%26+'A';
            break;
        
        default:
            str[i] = rand()%10+'0';
            break;
        }
    }
    str[i] = '\0';
    return str;
}

int main(){
    int n;
    char c, *string;

    printf("Digite o tamanho: ");
    scanf("%d", &n);

    string = aleatoria(n);
    printf("%s\n", string);

    free(string);
    return 0;
}