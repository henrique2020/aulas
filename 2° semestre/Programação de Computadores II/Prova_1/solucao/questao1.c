#include <stdio.h>

//---------------------------------------------------
#define N 100

//---------------------------------------------------
void separa(char str[N], char dir[N], char arq[N]){
    int i, k, barra = -1;

    for(i=0; str[i]!=0; i++){
        if (str[i] == '/'){
            barra = i;
        }
    }

    if ( barra == -1){
        dir[0] = '.';
        dir[1] = '/';
        dir[2] = '\0';      
    }
    else{
        for(i=0; i<=barra; i++){
            dir[i] = str[i];
        }
        dir[i] = '\0';
    }

    for(i=barra+1, k=0; str[i]!='\0'; i++, k++){
        arq[k] = str[i];
    }
    arq[k]='\0';
}
//---------------------------------------------------
int main(){
    char str[N], dir[N], arq[N];
    printf("Digite o caminho:\n");
    gets(str);

    separa(str, dir, arq);

    printf("Diretorio: %s \t Arquivo: %s\n", dir, arq);
}
