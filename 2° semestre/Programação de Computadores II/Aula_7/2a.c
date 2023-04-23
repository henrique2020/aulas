#include <stdio.h>

struct horario{
    int h, m, s;
};

typedef struct horario HORARIO;

HORARIO segundo_seguinte(HORARIO atual){
    HORARIO seguinte;
    int s = (atual.h*3600 + atual.m * 60 + atual.s + 1) % 86400; // 1 dia = 86400s

    seguinte.h = (s/3600)%24;
    s %= 3600;
    seguinte.m = s/60;
    seguinte.s = s%60;

    return(seguinte);
}

int main(){
    HORARIO atual, seguinte; 

    printf("Digite o horário: ");
    scanf("%d:%d:%d", &atual.h, &atual.m, &atual.s);

    seguinte = segundo_seguinte(atual);
    printf("%02d:%02d:%02d\n", seguinte.h, seguinte.m, seguinte.s);
}