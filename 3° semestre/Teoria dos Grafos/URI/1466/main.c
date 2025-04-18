#include <stdio.h>

int main() {
    int casos;
    scanf("%d", &casos);
    for(int i = 0; i < casos; i++){
        int numeros;
        scanf("%d", &numeros);

        int arvore[numeros];
        for(int j = 0; j < numeros; j++){
            scanf("%d", &arvore[j]);
        }

        for(int j = 0; j < numeros; j++){
            printf("%d ", arvore[j]);
        }
        printf("\n");
    }
    return 0;
}
