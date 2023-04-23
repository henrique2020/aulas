#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int valor;
    struct PILHA_NUM *prox;
} PILHA_NUM;

typedef struct {
    char valor;
    struct PILHA_OP *prox;
} PILHA_OP;

void empilhaNum (int valor, PILHA_NUM **topo){
    PILHA_NUM *novo = (PILHA_NUM*) malloc(sizeof(PILHA_NUM));
    novo->prox = *topo;
    novo->valor = valor;
    *topo = novo;
    //printf("empilhaNum: %d\n", novo->valor);
}

void empilhaOp(char valor, PILHA_OP **topo){
    PILHA_OP *novo = (PILHA_OP*) malloc(sizeof(PILHA_OP));
    novo->prox = *topo;
    novo->valor = valor;
    *topo = novo;
    //printf("empilhaOp: %c\n", novo->valor);
}

int desempilhaNum(PILHA_NUM **topo){
    PILHA_NUM *aux = (*topo)->prox;
    PILHA_NUM *del = *topo;
    int result = (*topo)->valor;
    *topo = aux;

    //printf("desempilhaNum: %d\n", result);
    return result;
}

char desempilhaOp(PILHA_OP **topo){
    PILHA_OP *aux = (*topo)->prox;
    PILHA_OP *del = *topo;
    char result = (*topo)->valor;
    *topo = aux;

    //printf("desempilhaOp: %c\n", result);
    return result;
}

void calcula(PILHA_NUM **topoNum, PILHA_OP **topoOp){
    int v1 = desempilhaNum(topoNum);
    int v2 = desempilhaNum(topoNum);
    char op = desempilhaOp(topoOp);

    switch(op){
        case '*':
            empilhaNum(v1 * v2, topoNum);
            break;

        case '+':
            empilhaNum(v1+v2, topoNum);
            break;

        case '-':
            empilhaNum(v2-v1, topoNum);
            break;

        case '/':
            if(v1 == 0){
                printf("Impossivel divir por 0\n");
                printf("Encerrando programa!\n");
                exit(1);
                break;
            }
            //Caso v1 seja diferente de 0, segue adiante
            empilhaNum(v2/v1, topoNum);

            break;
        default:
            printf("Operador invalido");
            exit(1);
            break;
    }
}

int main(){
    char expressao[50];
    int i, num = 0, sequencia=0, quebra=0;

    PILHA_NUM *topoNum;
    PILHA_OP *topoOp;

    printf("Digite a expressao matematica: ");
    scanf("%s", expressao);

    for(i=0; expressao[i]!='\0'; i++){
        if(expressao[i] >= '0' && expressao[i] <= '9') {
            num = expressao[i] - '0';
            empilhaNum(num, &topoNum);
            /*
            num = num*10 + expressao[i] - '0';
            if(expressao[i+1] < '0' || expressao[i+1]>'9'){
                empilhaNum(num, &topoNum);
            } else {
                num = 0;
            }*/
        }else if(expressao[i] != '(' && expressao[i] != ')') {
        //else if(expressao[i] == '+' || expressao[i] == '-' || expressao[i] == '*' || expressao[i] == '/') {
            empilhaOp(expressao[i], &topoOp);
        }else if(expressao[i] == ')'){
            calcula(&topoNum, &topoOp);
        }
    }

    if(expressao[i-1]!=')'){
        calcula(&topoNum, &topoOp);
    }

    printf("Resultado da expressao: %d", desempilhaNum(&topoNum));

    return 0;
}
