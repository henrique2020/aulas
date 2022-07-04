#include <stdio.h>
#include <string.h>

/*-------------------------------------------------*/
int eh_digito(char c){
    if ( c>= '0' && c<='9'){
        return 1;
    }
    else{
        return 0;
    }
}
/*-------------------------------------------------*/
void hora(char *str, int *h, int *m, int *s){
    
    if ( strlen(str) != 8 ){
        *h = -1;
        *m = -1;
        *s = -1;
    }
    else if ( !eh_digito(str[0]) || !eh_digito(str[1]) || str[2]!=':' || 
              !eh_digito(str[3]) || !eh_digito(str[4]) || str[5]!=':' ||
              !eh_digito(str[6]) || !eh_digito(str[7]) ){
        *h = -1;
        *m = -1;
        *s = -1;
    }
    else{
        *h = (str[0]-'0')*10 + (str[1]-'0');
        *m = (str[3]-'0')*10 + (str[4]-'0');
        *s = (str[6]-'0')*10 + (str[7]-'0');

        if ( *h >=24  || *m>=60 ||  *s>=60){
            *h = -1;
            *m = -1;  
            *s = -1;
        }

    }                
}
/*-------------------------------------------------*/
int main(){
    char horario[10];
    int h, m, s;

    printf("Digite o horario:\n");
    scanf("%s", horario);

    hora(horario, &h, &m, &s);
    
    printf("h= %d m= %d s= %d\n", h, m, s);

}

/*-------------------------------------------------*/
