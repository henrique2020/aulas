//É passado um horário e esse horário deve ser acrescentado
#include <stdio.h>

/*
H: 23 | M: 40 | MP: 30
R: 00:10
*/

void calcular_horario(int *h, int *m, int *mp){
    int total = *h*60 + *m + *mp;
    total = total%1440;
    *h = total/60;
    *m = total%60;
}


int main(){
    int h, m, mp;
    printf("Difgite o horário: ");
    scanf("%d:%d", &h, &m);

    printf("Tempo passado? (min)\n");
    scanf("%d", &mp);

    calcular_horario(&h, &m, &mp);

    printf("Agora são %02dh%02dmin\n", h, m);
    return 0;
}