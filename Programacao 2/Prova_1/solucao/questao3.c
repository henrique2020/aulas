#include <stdio.h>

//-----------------------------------------------------
#define N 100

//-----------------------------------------------------
float calcula(char str[N]){
	int i, num1, num2, flag;
    char op;
    float res;
    
    num1 = 0;
    num2 = 0;
    flag = 0;

    for(i=0; str[i] != '\0'; i++){
        if ( str[i]>='0' && str[i]<='9'){
            if ( !flag ){
                num1 = (num1*10) + (str[i]-'0');
            }
            else{
                num2 = (num2*10) + (str[i]-'0');
            }        
        }
        else{
            op = str[i];
            flag = 1;
        }
    }

    switch(op){
        case '+': res = num1 + num2;
                  break;
        case '-': res = num1 - num2;
                  break;
        case '*': res = num1 * num2;
                  break;
        case '/': res = (float)num1/num2;
                  break;
    }

    return res;
}
//-----------------------------------------------------
int main(){
	char str[N];

    printf("Digite a string:\n");
    scanf("%s", str);

    printf("Resultado: %.2f\n", calcula(str));
}
