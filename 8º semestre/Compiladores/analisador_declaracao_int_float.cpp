#define TKId 1
#define TKVoid 2
#define TKInt 3
#define TKFloat 4
#define TKVirgula 5
#define TKDoisPontos 6
#define TKAbrePar 7
#define TKFechaPar 8
#define TKAtrib 9
#define TKPontoEVirgula 10
#define TKAbreChaves 11
#define TKFechaChaves 12
#define TKMais 13
#define TKDuploMais 14
#define TKProd 15
#define TKChar 16
#define TKSub 17
#define TKAbreColchete 18
#define TKFechaColchete 19
#define TKAtribMais 20
#define TKDouble 21
#define TKCteInt 22
#define TKElse 23
#define TKIf 24
#define TKString 25
#define TKFimArquivo 26

#define false 0
#define true 1

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char nome[10][20]={"","TKId","TKvoid","TKInt"};

int pos = 0;
int tk;
char lex[20];
int lin=1;
char c; // último caracter lido

// --- VARIÁVEIS PARA LEITURA DO INPUT DO USUÁRIO ---
char codigo_fonte[4096]; // Buffer para armazenar o texto digitado (até 4096 caracteres)
int pos_fonte = 0; // Índice de leitura atual

struct pal_res{char palavra[20]; int tk;};
struct pal_res lista_pal[]={
    {"void",TKVoid},
    {"int",TKInt},
    {"float",TKFloat},
    {"char",TKChar},
    {"double",TKDouble},
    {"else",TKElse},
    {"if",TKIf},
    {"fimtabela",TKId}
};

int palavra_reservada(char lex[])
{
    int postab=0;
    while (strcmp("fimtabela",lista_pal[postab].palavra)!=0)
    {
        if (strcmp(lex,lista_pal[postab].palavra)==0)
            return lista_pal[postab].tk;
        postab++;
    }
    return TKId;
}

void getToken(); // protótipos
void proxC();

// variáveis globais para retrocesso
typedef struct contexto{
    long posglobal;
    int tkant;
    char cant;
    char lexant[20];
} tcontexto;

tcontexto pilhacon[1000];
int topcontexto=0;

void marcaPosToken() {
    pilhacon[topcontexto].posglobal = pos_fonte;
    pilhacon[topcontexto].tkant = tk;
    pilhacon[topcontexto].cant = c;
    strcpy(pilhacon[topcontexto].lexant,lex);
    topcontexto++;
}

void restauraPosToken() {
    topcontexto--;
    pos_fonte = pilhacon[topcontexto].posglobal;
    c = pilhacon[topcontexto].cant;
    tk = pilhacon[topcontexto].tkant;
    strcpy(lex,pilhacon[topcontexto].lexant);
}

void proxC()
{
    // Verifica se chegou ao fim da string ou encontrou uma quebra de linha final
    if (codigo_fonte[pos_fonte] == '\0') {
        c = -1; // Representa o Fim de Arquivo (EOF)
        return;
    }

    // Lê o próximo caractere do array e incrementa a posição
    c = codigo_fonte[pos_fonte++];

    if (c=='\n') lin++;
}

void getToken()
{
    int estado=0, fim=0, posl=0;
    while (!fim)
    {
        lex[posl++]=c;
        switch(estado){
            case 0:
                if ((c>='a' && c<='z') || (c>='A' && c<='Z') || c=='_')
                    {proxC();estado=1;break;}
                if (c>='0' && c<='9')
                {
                    while (c>='0' && c<='9') proxC();
                    lex[posl]='\0';
                    tk=TKCteInt;
                    return;
                }
                if (c=='"')
                {
                    proxC();
                    while (c!='"')
                    {
                        lex[posl++]=c;
                        proxC();
                    }
                    proxC();
                    lex[posl]='\0';
                    tk=TKString;
                    return;
                }
                if (c=='='){lex[posl]='\0';proxC();tk=TKAtrib;return;}
                if (c=='+')
                {
                    proxC();
                    if (c=='+')
                    {
                        lex[posl++]='+'; lex[posl]='\0'; proxC();
                        tk=TKDuploMais; return;
                    }
                    else if (c=='=')
                    {
                        lex[posl++]='='; lex[posl]='\0'; proxC();
                        tk=TKAtribMais; return;
                    }
                    else
                    {
                        lex[posl]='\0'; tk=TKMais; return;
                    }
                }
                if (c=='*'){lex[posl]='\0';proxC();tk=TKProd;return;}
                if (c=='['){lex[posl]='\0';proxC();tk=TKAbreColchete;return;}
                if (c==']'){lex[posl]='\0';proxC();tk=TKFechaColchete;return;}
                if (c=='('){lex[posl]='\0';proxC();tk=TKAbrePar;return;}
                if (c==')'){lex[posl]='\0';proxC();tk=TKFechaPar;return;}
                if (c=='{'){lex[posl]='\0';proxC();tk=TKAbreChaves;return;}
                if (c=='}'){lex[posl]='\0';proxC();tk=TKFechaChaves;return;}
                if (c==','){lex[posl]='\0';proxC();tk=TKVirgula;return;}
                if (c==';'){lex[posl]='\0';proxC();tk=TKPontoEVirgula;return;}
                if (c==':'){lex[posl]='\0';proxC();tk=TKDoisPontos;return;}
                if (c=='-'){lex[posl]='\0';proxC();tk=TKSub;return;}
                if (c==-1){lex[posl]='\0';proxC();tk=TKFimArquivo;return;}
                if (c==' ' || c=='\n' || c=='\t' || c=='\r') {proxC();posl--;break;}
                if (c=='\0') {tk=-1;return;}

                printf("Erro léxico: encontrou o caracter %c (%d) na linha %d\n",c,c,lin);
                while (c!='\n' && c!='\0' && c!=-1) proxC();
                break;

            case 1:
                if ((c>='a' && c<='z') || (c>='A' && c<='Z') || c=='_' || (c>='0' && c<='9')) {proxC();break;}
                lex[--posl]='\0';
                tk=palavra_reservada(lex);
                return;
        }
    }
}

int Dec();

void Poetab(char *lex, char TipoT){
    printf("Achou %s = %c\n", lex, TipoT);
}

int RL(char TipoT){
    if(tk==TKVirgula){
        getToken();
        if(tk==TKId){
            Poetab(lex, TipoT);
            getToken();
            if(RL(TipoT)){ return 1; }
            else { return 0; }
        }
        else {
            return 0;
        }
    } else if(tk==TKPontoEVirgula){
        getToken();
        return 1;
    } else {
        printf("Esperava ';'\n");
        return 0;
    }
}

int Tipo(char *TipoT){
    if(tk == TKInt){
        getToken();
        *TipoT = 'I';
        return 1;
    } else if(tk == TKFloat){
        getToken();
        *TipoT = 'F';
        return 1;
    } else {
        printf("Esperava tipo\n");
        return 0;
    }
}

int Dec(){
    char TipoT;
    if(Tipo(&TipoT)){
        if(tk==TKId){
            Poetab(lex, TipoT);
            getToken();
            if(RL(TipoT)){ return 1; }
            else { return 0; }
        } else {
            printf("Esperava identificador\n");
            return 0;
        }
    }
    return 0;
}

int main(){
    printf("Digite a declaracao para analise (ex: int a, b;): ");

    if (fgets(codigo_fonte, sizeof(codigo_fonte), stdin) == NULL) {
        printf("Erro ao ler a entrada.\n");
        return 1;
    }

    proxC(); // lê primeiro caracter da string capturada
    getToken(); // lê primeiro token

    if(Dec()){
        printf("\nReconheceu com sucesso!\n");
    } else {
        printf("\nNao reconheceu!\n");
    }

    return 0;
}
