#include <stdio.h>

int minimo(int a, int b){
   if (a<=b) return a;
   else return b;
}

int bottom_up(int degraus, int custos[], int dp[]){
    for(int i = 0; i < degraus; i++){
        if(i < 2){ dp[i] = custos[i]; }
        else { dp[i] = minimo(dp[i-1], dp[i-2]) + custos[i]; }

        printf("Degrau: %d | Custo: %d | Custo ate o degrau: %d\n", i+1, custos[i], dp[i]);
    }

    return dp[degraus-1];
}

int top_down(int i, int custos[], int dp[]) {
    if (i < 2) return custos[i];
    if (dp[i] != -1) return dp[i];
    dp[i] = minimo(top_down(i-1, custos, dp), top_down(i-2, custos, dp)) + custos[i];

    printf("Degrau: %d | Custo: %d | Custo ate o degrau: %d\n", i+1, custos[i], dp[i]);
    return dp[i];
}


int main() {
    int degraus = 10;
    int custos[] = {1, 6, 4, 9, 12, 10, 9, 8, 3, 5};
    int dpUp[degraus];

    printf("BottomUp: %d degraus - custo %d\n", degraus, bottom_up(degraus, custos, dpUp));

    printf("\n");

    int dpDown[degraus];
    for(int i=0; i<degraus; i++) dpDown[i] = -1;
    printf("TopDown: %d degraus - custo %d\n", degraus, top_down(degraus-1, custos, dpDown));

    return 0;
}
