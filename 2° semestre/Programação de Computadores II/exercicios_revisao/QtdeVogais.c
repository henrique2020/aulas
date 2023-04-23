#include <stdio.h>
#include <ctype.h>

//Rever, está retornando -nan

int vogal(char c){
    c = toupper(c);
    if((c == 'A') || (c == 'E') || (c == 'I') || (c == 'O') || (c == 'U')){ return 1; }
    else{ return 0; }
}

float percentual(char str[100]){
    int vogais, total = 0;
    int i;
    for (i = 0; i != '\0'; i++){
        if (vogal(str[i])){ vogais++; }
        total++;
    }

    float percent = (vogais*100.0)/total;
}

int main(){
    char str[100] = "Programadores II em C";
    printf("Percentual de vogais: %.4f%%\n", percentual(str));
}