#include <stdio.h>

void calcula_digitos_cpf(int cpf, int *d1, int *d2){
    int resto, soma1, soma2, m1;
    soma1 = soma2 = 0;
    m1 = 2;
    while (cpf > 0){
        int resto = cpf%10;
        cpf /= 10;
        soma1 += resto*m1;
        soma2 += resto*(m1+1);
        m1++;
    }

    resto = soma1%11;
    if (resto <= 1){ *d1 = 0; }
    else { *d1 = 11 - resto; }

    soma2 += *d1 * 2;
    resto = soma2%11;
    if (resto <= 1){ *d2 = 0; }
    else { *d2 = 11 - resto; }
}

int main(){
    //unsigned int x = 0xffffffff;
    //x = x+1;
    //printf("%d\n", x);

    int cpf, d1, d2;

    printf("Digite o CPF: ");
    scanf("%d", &cpf);

    calcula_digitos_cpf(cpf, &d1, &d2);

    printf("O CPF digitado foi %d\n", cpf);
    printf("%d, %d\n", d1, d2);
    return 0;
}