#include <stdio.h>

int compacta(int h, int m, int s){
    int c = 0;
    c = h;
    c <<= 8;
    c += m;
    c <<= 8;
    c |= s;
    // '|=' ou '+=' dão o mesmo resultado
    return c;
}

void descompacta(int c, int *h, int *m, int *s){
    *s = c & 0x000000FF;
    c >>= 8;
    *m = c & 0x000FF;
    c >>= 8;
    *h = c & 0xFF;
    //0x000000FF não precisa ter os 0's a esquerda
}

main(){
    int c, h, m, s;
    c = compacta(14, 20, 33);
    printf("%x\n", c);

    descompacta(c, &h, &m, &s);
    printf("%d:%d:%d\n", h, m, s);
    return 0;
}