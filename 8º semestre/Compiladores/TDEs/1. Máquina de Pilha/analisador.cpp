#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TK_int 1
#define TK_if 2
#define TK_else 3
#define TK_while 4
#define TK_for 5
#define TK_break 6
#define TK_continue 7
#define TK_Abre_Chaves 8
#define TK_Fecha_Chaves 9
#define TK_Fim_Arquivo 10
#define TK_Atrib 11
#define TK_Const_Int 12
#define TK_Mais 13
#define TK_Menos 14
#define TK_Mult 15
#define TK_Abre_Par 16
#define TK_Fecha_Par 17
#define TK_virgula 18
#define TK_pv 19
#define TK_Maior 20
#define TK_Menor 21
#define TK_Menor_Igual 22
#define TK_Maior_Igual 23
#define TK_Igual 24
#define TK_Diferente 25
#define TK_Div 26
#define TK_id 27
#define TK_Mais_Mais 28
#define TK_Menos_Menos 29

#define MAX_COD 10000
#define MAX_ID 64
#define MAX_ESCOPOS 64
#define MAX_IDS 256

int linlex=0,collex=1;
int token;
int erro=0;
char lex[128];
FILE *arqin;

char reservadas[][20]={"","int","if","else","while","for","break","continue","fim"};

typedef struct {
    char nome[MAX_ID];
} identificador;

typedef struct {
    identificador ids[MAX_IDS];
    int qtd;
} escopo;

escopo escopos[MAX_ESCOPOS];
int nescopos=0;
int nrotulo=0;
char rotulo_break[MAX_ESCOPOS][16];
char rotulo_continue[MAX_ESCOPOS][16];
int nlacos=0;

/* Recebe o arquivo global e retorna o próximo caractere lido. */
char le_char()
{
    char c;
    if (fread(&c,1,1,arqin)==0) return -1;
    if (c=='\n') {linlex++;collex=1;}
    else collex++;
    return c;
}

/* Recebe um identificador e retorna seu token reservado ou TK_id. */
int pal_res(char palavra[])
{
    int tk=0;
    while (strcmp(reservadas[tk],"fim")!=0) {
        if (strcmp(palavra,reservadas[tk])==0) return tk;
        tk++;
    }
    return TK_id;
}

/* Recebe o arquivo global e retorna o próximo token léxico reconhecido. */
int le_token()
{
    static int pos=0;
    static int estado=0;
    static char c='\0';
    char d;
    while (1) {
        switch (estado) {
        case 0:
            if (c==',') {c=le_char();return TK_virgula;}
            if (c=='+') {
                c=le_char();
                if (c=='+') {c=le_char();return TK_Mais_Mais;}
                return TK_Mais;
            }
            if (c=='-') {
                c=le_char();
                if (c=='-') {c=le_char();return TK_Menos_Menos;}
                return TK_Menos;
            }
            if (c=='*') {c=le_char();return TK_Mult;}
            if (c=='{') {c=le_char();return TK_Abre_Chaves;}
            if (c=='}') {c=le_char();return TK_Fecha_Chaves;}
            if (c==';') {c=le_char();return TK_pv;}
            if (c=='(') {c=le_char();return TK_Abre_Par;}
            if (c==')') {c=le_char();return TK_Fecha_Par;}
            if (c=='/') {
                d=le_char();
                if (d=='/') {
                    do {c=le_char();} while (c!='\n' && c!=-1);
                    break;
                }
                if (d=='*') {
                    char anterior=0;
                    c=le_char();
                    while (c!=-1 && !(anterior=='*' && c=='/')) {
                        anterior=c;
                        c=le_char();
                    }
                    if (c==-1) erro=1;
                    c=le_char();
                    break;
                }
                c=d;
                return TK_Div;
            }
            if (c=='=') {
                c=le_char();
                if (c=='=') {c=le_char();return TK_Igual;}
                return TK_Atrib;
            }
            if (c=='<') {
                c=le_char();
                if (c=='=') {c=le_char();return TK_Menor_Igual;}
                return TK_Menor;
            }
            if (c=='>') {
                c=le_char();
                if (c=='=') {c=le_char();return TK_Maior_Igual;}
                return TK_Maior;
            }
            if (c=='!') {
                c=le_char();
                if (c=='=') {c=le_char();return TK_Diferente;}
                erro=1;
                break;
            }
            if ((c>='a' && c<='z') || (c>='A' && c<='Z') || c=='_') {
                lex[0]=c;
                c=le_char();
                pos=1;
                estado=1;
                break;
            }
            if (c>='0' && c<='9') {
                lex[0]=c;
                c=le_char();
                pos=1;
                estado=2;
                break;
            }
            if (c==-1) return TK_Fim_Arquivo;
            if (c=='\n'||c=='\r'||c=='\t'||c=='\0'||c==' ') {
                c=le_char();
                break;
            }
            erro=1;
            c=le_char();
            break;
        case 1:
            if ((c>='a' && c<='z') || (c>='A' && c<='Z') ||
                (c>='0' && c<='9') || c=='_') {
                if (pos<127) lex[pos++]=c;
                c=le_char();
                break;
            }
            estado=0;
            lex[pos]='\0';
            return pal_res(lex);
        case 2:
            if (c>='0' && c<='9') {
                if (pos<127) lex[pos++]=c;
                c=le_char();
                break;
            }
            estado=0;
            lex[pos]='\0';
            return TK_Const_Int;
        }
    }
}

/* Recebe um nome e registra a declaração no escopo atual. */
int declara(char nome[])
{
    int i;
    if (nescopos==0) escopos[nescopos++].qtd=0;
    for (i=0;i<escopos[nescopos-1].qtd;i++)
        if (strcmp(escopos[nescopos-1].ids[i].nome,nome)==0) {
            printf("Variavel %s declarada novamente na linha %d\n",nome,linlex+1);
            erro=1;
            return 0;
        }
    if (escopos[nescopos-1].qtd>=MAX_IDS) {
        erro=1;
        return 0;
    }
    strcpy(escopos[nescopos-1].ids[escopos[nescopos-1].qtd++].nome,nome);
    return 1;
}

/* Recebe um nome e retorna se ele foi declarado em algum escopo visível. */
int declarada(char nome[])
{
    int i,j;
    for (i=nescopos-1;i>=0;i--)
        for (j=0;j<escopos[i].qtd;j++)
            if (strcmp(escopos[i].ids[j].nome,nome)==0) return 1;
    return 0;
}

/* Não recebe argumentos e abre um novo escopo lexical. */
void abre_escopo()
{
    if (nescopos<MAX_ESCOPOS)
        escopos[nescopos++].qtd=0;
    else erro=1;
}

/* Não recebe argumentos e fecha o escopo lexical mais interno. */
void fecha_escopo()
{
    if (nescopos>0) nescopos--;
}

/* Recebe um buffer e retorna nele um rótulo único para saltos. */
void geralabel(char label[])
{
    sprintf(label,"LB%03d",nrotulo++);
}

int F(char F_c[MAX_COD]);
int E(char E_c[MAX_COD]);
int R(char R_h[MAX_COD],char R_s[MAX_COD]);
int T(char T_c[MAX_COD]);
int S(char S_h[MAX_COD],char S_s[MAX_COD]);
int Rel(char Rel_c[MAX_COD]);
int Com(char Com_c[MAX_COD]);

/* Recebe um buffer e retorna o código pós-fixo de um fator. */
int F(char F_c[MAX_COD])
{
    char E_c[MAX_COD],id[MAX_ID];
    if (token==TK_Const_Int) {
        sprintf(F_c,"\tpush %s\n",lex);
        token=le_token();
        return 1;
    }
    if (token==TK_id) {
        strcpy(id,lex);
        if (!declarada(id)) {
            printf("Variavel %s nao foi declarada\n",id);
            erro=1;
            return 0;
        }
        sprintf(F_c,"\tvalor-r %s\n",id);
        token=le_token();
        return 1;
    }
    if (token==TK_Abre_Par) {
        token=le_token();
        if (E(E_c) && token==TK_Fecha_Par) {
            token=le_token();
            strcpy(F_c,E_c);
            return 1;
        }
    }
    return 0;
}

/* Recebe os códigos esquerdo e resultado e retorna a cadeia de multiplicações. */
int S(char S_h[MAX_COD],char S_s[MAX_COD])
{
    char F_c[MAX_COD],S1_h[MAX_COD],S1_s[MAX_COD];
    if (token==TK_Mult || token==TK_Div) {
        char op=token==TK_Mult?'*':'/';
        token=le_token();
        if (F(F_c)) {
            sprintf(S1_h,"%s%s\t%c\n",S_h,F_c,op);
            if (S(S1_h,S1_s)) {strcpy(S_s,S1_s);return 1;}
        }
        return 0;
    }
    strcpy(S_s,S_h);
    return 1;
}

/* Recebe um buffer e retorna o código pós-fixo de um termo multiplicativo. */
int T(char T_c[MAX_COD])
{
    char F_c[MAX_COD],S_h[MAX_COD],S_s[MAX_COD];
    if (F(F_c)) {
        strcpy(S_h,F_c);
        if (S(S_h,S_s)) {
            strcpy(T_c,S_s);
            return 1;
        }
    }
    return 0;
}

/* Recebe os códigos esquerdo e resultado e retorna a cadeia de somas. */
int R(char R_h[MAX_COD],char R_s[MAX_COD])
{
    char T_c[MAX_COD],R1_h[MAX_COD],R1_s[MAX_COD];
    if (token==TK_Mais || token==TK_Menos) {
        char op=token==TK_Mais?'+':'-';
        token=le_token();
        if (T(T_c)) {
            sprintf(R1_h,"%s%s\t%c\n",R_h,T_c,op);
            if (R(R1_h,R1_s)) {strcpy(R_s,R1_s);return 1;}
        }
        return 0;
    }
    strcpy(R_s,R_h);
    return 1;
}

/* Recebe um buffer e retorna o código pós-fixo de uma expressão aritmética. */
int E(char E_c[MAX_COD])
{
    char T_c[MAX_COD],R_h[MAX_COD],R_s[MAX_COD];
    if (T(T_c)) {
        strcpy(R_h,T_c);
        if (R(R_h,R_s)) {strcpy(E_c,R_s);return 1;}
    }
    return 0;
}

/* Recebe um buffer e retorna o código de uma expressão relacional opcional. */
int Rel(char Rel_c[MAX_COD])
{
    char E1_c[MAX_COD],E2_c[MAX_COD],op[8];
    if (!E(E1_c)) return 0;
    if (token==TK_Maior || token==TK_Menor || token==TK_Igual ||
        token==TK_Diferente || token==TK_Maior_Igual || token==TK_Menor_Igual) {
        if (token==TK_Maior) strcpy(op,">");
        if (token==TK_Menor) strcpy(op,"<");
        if (token==TK_Igual) strcpy(op,"=");
        if (token==TK_Diferente) strcpy(op,"<>");
        if (token==TK_Maior_Igual) strcpy(op,">=");
        if (token==TK_Menor_Igual) strcpy(op,"<=");
        token=le_token();
        if (!E(E2_c)) return 0;
        sprintf(Rel_c,"%s%s\t%s\n",E1_c,E2_c,op);
    } else strcpy(Rel_c,E1_c);
    return 1;
}

/* Recebe um buffer e retorna o código de uma declaração int. */
int Declaracao(char Dec_c[MAX_COD])
{
    (void)Dec_c;
    if (token!=TK_int) return 0;
    token=le_token();
    if (token!=TK_id) return 0;
    while (1) {
        if (!declara(lex)) return 0;
        token=le_token();
        if (token!=TK_virgula) break;
        token=le_token();
        if (token!=TK_id) return 0;
    }
    if (token!=TK_pv) return 0;
    token=le_token();
    return 1;
}

/* Recebe um buffer e retorna o código de uma atribuição sem ponto-e-vírgula opcional. */
int Atrib(char Atrib_c[MAX_COD],int pv)
{
    char id[MAX_ID],E_c[MAX_COD];
    if (token!=TK_id) return 0;
    strcpy(id,lex);
    if (!declarada(id)) {
        printf("Variavel %s nao foi declarada\n",id);
        erro=1;
        return 0;
    }
    token=le_token();
    if (token==TK_Mais_Mais || token==TK_Menos_Menos) {
        int op_inc = (token==TK_Mais_Mais);
        token=le_token();
        if (pv && token!=TK_pv) return 0;
        if (pv) token=le_token();
        sprintf(Atrib_c,"\tvalor-l %s\n\tvalor-r %s\n\tpush 1\n\t%c\n\t:=\n\tpop\n",
                id,id,op_inc?'+':'-');
        return 1;
    }
    if (token!=TK_Atrib) return 0;
    token=le_token();
    if (!E(E_c)) return 0;
    if (pv && token!=TK_pv) return 0;
    if (pv) token=le_token();
    sprintf(Atrib_c,"\tvalor-l %s\n%s\t:=\n\tpop\n",id,E_c);
    return 1;
}

/* Recebe um buffer e retorna o código de uma lista de atribuições separadas por vírgula. */
int LAtrib(char LAtrib_c[MAX_COD])
{
    char Atrib_c[MAX_COD],Atrib2_c[MAX_COD];
    if (!Atrib(Atrib_c,0)) return 0;
    strcpy(LAtrib_c,Atrib_c);
    while (token==TK_virgula) {
        token=le_token();
        if (!Atrib(Atrib2_c,0)) return 0;
        strcat(LAtrib_c,Atrib2_c);
    }
    return 1;
}

/* Recebe um buffer e retorna o código do comando if com else opcional. */
int ComIf(char ComIfc[MAX_COD])
{
    char Ec[MAX_COD],Comc[MAX_COD],Com2c[MAX_COD],lbfim[16],lbelse[16];
    if (token!=TK_if) return 0;
    token=le_token();
    if (token!=TK_Abre_Par) return 0;
    token=le_token();
    if (!Rel(Ec) || token!=TK_Fecha_Par) return 0;
    token=le_token();
    if (!Com(Comc)) return 0;
    geralabel(lbelse);
    if (token==TK_else) {
        token=le_token();
        if (!Com(Com2c)) return 0;
        geralabel(lbfim);
        sprintf(ComIfc,"%s\tgofalse %s\n%s\tgoto %s\n%s:\n%s%s:\n",
                Ec,lbelse,Comc,lbfim,lbelse,Com2c,lbfim);
    } else {
        sprintf(ComIfc,"%s\tgofalse %s\n%s%s:\n",Ec,lbelse,Comc,lbelse);
    }
    return 1;
}

/* Recebe um buffer e retorna o código do comando while. */
int ComWhile(char ComWhilec[MAX_COD])
{
    char Ec[MAX_COD],Comc[MAX_COD],lblaco[16],lbfim[16];
    if (token!=TK_while) return 0;
    token=le_token();
    if (token!=TK_Abre_Par) return 0;
    token=le_token();
    if (!Rel(Ec) || token!=TK_Fecha_Par) return 0;
    token=le_token();
    geralabel(lblaco);
    geralabel(lbfim);
    strcpy(rotulo_break[nlacos],lbfim);
    strcpy(rotulo_continue[nlacos],lblaco);
    nlacos++;
    if (!Com(Comc)) {nlacos--;return 0;}
    nlacos--;
    sprintf(ComWhilec,"%s:\n%s\tgofalse %s\n%s\tgoto %s\n%s:\n",
            lblaco,Ec,lbfim,Comc,lblaco,lbfim);
    return 1;
}

/* Recebe um buffer e retorna o código do comando for com expressões opcionais. */
int ComFor(char ComForc[MAX_COD])
{
    char init[MAX_COD],cond[MAX_COD],inc[MAX_COD],Comc[MAX_COD];
    char lblaco[16],lbincremento[16],lbfim[16];
    if (token!=TK_for) return 0;
    token=le_token();
    if (token!=TK_Abre_Par) return 0;
    token=le_token();
    strcpy(init,"");
    strcpy(cond,"");
    strcpy(inc,"");
    if (token!=TK_pv) {
        if (!LAtrib(init)) return 0;
    }
    if (token!=TK_pv) return 0;
    token=le_token();
    if (token!=TK_pv) {
        if (!Rel(cond)) return 0;
    }
    if (token!=TK_pv) return 0;
    token=le_token();
    if (token!=TK_Fecha_Par) {
        if (!LAtrib(inc)) return 0;
    }
    if (token!=TK_Fecha_Par) return 0;
    token=le_token();
    geralabel(lblaco);
    geralabel(lbincremento);
    geralabel(lbfim);
    strcpy(rotulo_break[nlacos],lbfim);
    strcpy(rotulo_continue[nlacos],lbincremento);
    nlacos++;
    if (!Com(Comc)) {nlacos--;return 0;}
    nlacos--;
    sprintf(ComForc,"%s%s:\n%s%s\tgofalse %s\n%s%s:\n%s\tgoto %s\n%s:\n",
            init,lblaco,cond[0]?cond:"\tpush 1\n",cond[0]?"":"",lbfim,
            Comc,lbincremento,inc,lblaco,lbfim);
    return 1;
}

/* Recebe um buffer e retorna o código do bloco composto com escopo local. */
int ComComp(char ComCompc[MAX_COD])
{
    char Comc[MAX_COD];
    if (token!=TK_Abre_Chaves) return 0;
    token=le_token();
    abre_escopo();
    strcpy(ComCompc,"");
    while (token!=TK_Fecha_Chaves && token!=TK_Fim_Arquivo) {
        if (token==TK_int) {
            if (!Declaracao(Comc)) {fecha_escopo();return 0;}
        } else {
            if (!Com(Comc)) {fecha_escopo();return 0;}
            strcat(ComCompc,Comc);
        }
    }
    if (token!=TK_Fecha_Chaves) {fecha_escopo();return 0;}
    token=le_token();
    fecha_escopo();
    return 1;
}

/* Recebe um buffer e retorna o código de break dentro de um laço. */
int ComBreak(char ComBreakc[MAX_COD])
{
    if (token!=TK_break || nlacos==0) return 0;
    token=le_token();
    if (token!=TK_pv) return 0;
    token=le_token();
    sprintf(ComBreakc,"\tgoto %s\n",rotulo_break[nlacos-1]);
    return 1;
}

/* Recebe um buffer e retorna o código de continue dentro de um laço. */
int ComContinue(char ComContinuec[MAX_COD])
{
    if (token!=TK_continue || nlacos==0) return 0;
    token=le_token();
    if (token!=TK_pv) return 0;
    token=le_token();
    sprintf(ComContinuec,"\tgoto %s\n",rotulo_continue[nlacos-1]);
    return 1;
}

/* Recebe um buffer e retorna o código de um comando expressão ou atribuição. */
int ComExp(char ComExpc[MAX_COD])
{
    char Ec[MAX_COD];
    if (token==TK_id) return Atrib(ComExpc,1);
    if (E(Ec) && token==TK_pv) {
        token=le_token();
        strcpy(ComExpc,Ec);
        return 1;
    }
    return 0;
}

/* Recebe um buffer e retorna o código do próximo comando reconhecido. */
int Com(char Comc[MAX_COD])
{
    if (token==TK_for) return ComFor(Comc);
    if (token==TK_while) return ComWhile(Comc);
    if (token==TK_if) return ComIf(Comc);
    if (token==TK_Abre_Chaves) return ComComp(Comc);
    if (token==TK_break) return ComBreak(Comc);
    if (token==TK_continue) return ComContinue(Comc);
    return ComExp(Comc);
}

/* Recebe o nome da entrada e retorna o código final no arquivo saida.cod. */
int main(int argc,char *argv[])
{
    FILE *arqout;
    char Com_c[MAX_COD];
    if ((arqin=fopen("entrada.c","rt"))==NULL) {
        printf("Erro na abertura do arquivo de entrada\n");
        return 1;
    }
    if ((arqout=fopen("saida.cod","wt"))==NULL) {
        printf("Erro na abertura do arquivo de saida\n");
        fclose(arqin);
        return 1;
    }
    abre_escopo();
    token=le_token();
    strcpy(Com_c,"");
    while (token!=TK_Fim_Arquivo && !erro) {
        if (token==TK_int) {
            if (!Declaracao(Com_c)) erro=1;
        } else if (Com(Com_c)) {
            fprintf(arqout,"%s",Com_c);
        } else {
            erro=1;
        }
    }
    fclose(arqin);
    fclose(arqout);
    fecha_escopo();
    if (erro) {
        remove("saida.cod");
        printf("Erro durante a analise na linha %d\n",linlex+1);
        return 1;
    }
    return 0;
}
