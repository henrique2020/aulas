#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define TK_int 1
#define TK_float 2
#define TK_char 3
#define TK_struct 4
#define TK_if 5
#define TK_else 6
#define TK_while 7

#define TK_Abre_Colch 8
#define TK_Fecha_Colch 9
#define TK_Abre_Chaves 10
#define TK_Fecha_Chaves 11
#define TK_Fim_Arquivo 12
#define TK_Atrib 13
#define TK_Const_Int 14
#define TK_Mais 15
#define TK_Menos 16
#define TK_Mult 17
#define TK_Abre_Par 18
#define TK_Fecha_Par 19
#define TK_virgula 20
#define TK_pv 21
#define TK_Maior 22
#define TK_Menor 23
#define TK_Menor_Igual 24
#define TK_Maior_Igual 25
#define TK_Igual 26
#define TK_Diferente 27
#define TK_Div 28
#define TK_id 29

/***********************************************************************************/
/*                                                                                 */
/*  INÍCIO DO LÉXICO - Não entre a não ser que tenha interesse pessoal em léxicos  */
/*                                                                                 */
/***********************************************************************************/

int linlex = 0, collex = 1;

char tokens[][20] = {
    "",
    "TK_int",
    "TK_float",
    "TK_char",
    "TK_struct",
    "TK_if",
    "TK_else",
    "TK_while",
    "TK_Abre_Colch",
    "TK_Fecha_Colch",
    "TK_Abre_Chaves",
    "TK_Fecha_Chaves",
    "TK_Fim_Arquivo",
    "TK_Atrib",
    "TK_Const_Int",
    "TK_Mais",
    "TK_Menos",
    "TK_Mult",
    "TK_Abre_Par",
    "TK_Fecha_Par",
    "TK_virgula",
    "TK_pv",
    "TK_Maior",
    "TK_Menor",
    "TK_Menor_Igual",
    "TK_Maior_Igual",
    "TK_Igual",
    "TK_Diferente",
    "TK_id"
};

char reservadas[][20] = { "", "int", "float", "char", "struct", "if", "else", "while", "fim" };

FILE *arqin;
int token;
char lex[20];

char le_char()
{
    char c;

    if (fread(&c, 1, 1, arqin) == 0)
        return -1;
    if (c == '\n') {
        linlex++;
        collex = 1;
    } else {
        collex++;
    }
    return c;
}

int pal_res(char lex[])
{
    int tk = 0;
    while (strcmp(reservadas[tk], "fim") != 0) {
        if (strcmp(lex, reservadas[tk]) == 0)
            return tk;
        tk++;
    }
    return TK_id;
}

int le_token()
{
    static int pos = 0;
    static int estado = 0;
    static char c = '\0';

    while (1) {
        switch (estado) {
        case 0:
            if (c == ',') {
                c = le_char();
                return TK_virgula;
            }
            if (c == '+') {
                c = le_char();
                return TK_Mais;
            }
            if (c == '-') {
                c = le_char();
                return TK_Menos;
            }
            if (c == '*') {
                c = le_char();
                return TK_Mult;
            }
            if (c == '{') {
                c = le_char();
                return TK_Abre_Chaves;
            }
            if (c == '}') {
                c = le_char();
                return TK_Fecha_Chaves;
            }
            if (c == ';') {
                c = le_char();
                return TK_pv;
            }
            if (c == '[') {
                c = le_char();
                return TK_Abre_Colch;
            }
            if (c == ']') {
                c = le_char();
                return TK_Fecha_Colch;
            }
            if (c == '(') {
                c = le_char();
                return TK_Abre_Par;
            }
            if (c == ')') {
                c = le_char();
                return TK_Fecha_Par;
            }
            if (c == '/') {
                c = le_char();
                return TK_Div;
            }
            if (c == '=') {
                c = le_char();
                if (c == '=') {
                    c = le_char();
                    return TK_Igual;
                }
                return TK_Atrib;
            }
            if (c == '<') {
                c = le_char();
                if (c == '=') {
                    c = le_char();
                    return TK_Menor_Igual;
                }
                return TK_Menor;
            }
            if (c == '>') {
                c = le_char();
                if (c == '=') {
                    c = le_char();
                    return TK_Maior_Igual;
                }
                return TK_Maior;
            }
            if (c == '!') {
                c = le_char();
                if (c == '=') {
                    c = le_char();
                    return TK_Diferente;
                }
            }
            if ((c >= 'a' && c <= 'z') || c == '_') {
                lex[0] = c;
                c = le_char();
                pos = 1;
                estado = 1;
                break;
            }
            if (c >= '0' && c <= '9') {
                lex[0] = c;
                c = le_char();
                pos = 1;
                estado = 2;
                break;
            }
            if (c == -1)
                return TK_Fim_Arquivo;
            if (c == '\n' || c == '\r' || c == '\t' || c == '\0' || c == ' ') {
                c = le_char();
                break;
            }

        case 1:
            if ((c >= 'a' && c <= 'z') || c == '_' || (c >= '0' && c <= '9')) {
                lex[pos++] = c;
                c = le_char();
                break;
            } else {
                estado = 0;
                lex[pos] = '\0';
                return pal_res(lex);
            }

        case 2:
            if (c >= '0' && c <= '9') {
                lex[pos++] = c;
                c = le_char();
                break;
            } else {
                estado = 0;
                lex[pos] = '\0';
                return TK_Const_Int;
            }
        }
    }
}

/********************/
/*                  */
/*  FIM DO LÉXICO   */
/*                  */
/********************/

#define MAX_COD 1000

void mostra_t()
{
    printf("%s lex=%s na lin %d, col %d\n", tokens[token], lex, linlex, collex);
}

/****************/
/*              */
/*  EXPRESSÔES  */
/*              */
/****************/

int F(char F_c[MAX_COD]);
int E(char E_c[MAX_COD]);
int R(char R_h[MAX_COD], char R_s[MAX_COD]);
int T(char T_c[MAX_COD]);
int S(char S_h[MAX_COD], char S_s[MAX_COD]);

int Rel(char Rel_c[MAX_COD])
{
    char E1_c[MAX_COD], E2_c[MAX_COD], R_s[MAX_COD];
    if (E(E1_c)) {
        char op[10];
        if (token == TK_Maior)
            strcpy(op, ">");
        else if (token == TK_Menor)
            strcpy(op, "<");
        else if (token == TK_Igual)
            strcpy(op, "=");
        else if (token == TK_Diferente)
            strcpy(op, "<>");
        else if (token == TK_Maior_Igual)
            strcpy(op, ">=");
        else if (token == TK_Menor_Igual)
            strcpy(op, "<=");

        if (token == TK_Maior || token == TK_Menor || token == TK_Igual || token == TK_Diferente || token == TK_Maior_Igual || token == TK_Menor_Igual) {
            token = le_token();
            if (E(E2_c)) {
                sprintf(Rel_c, "%s%s\t%s\n", E1_c, E2_c, op);
                return 1;
            }
            return 0;
        } else {
            strcpy(Rel_c, E1_c);
            return 1;
        }
    }
    return 0;
}

// E -> T   R
// R -> + T R
// R -> vazio

// T -> F   S
// S -> * F S
// S -> vazio

int E(char E_c[MAX_COD])
{
    char T_c[MAX_COD], R_h[MAX_COD], R_s[MAX_COD];
    if (T(T_c)) {
        strcpy(R_h, T_c);
        if (R(R_h, R_s)) {
            strcpy(E_c, R_s);
            return 1;
        }
    }
    return 0;
}

int R(char R_h[MAX_COD], char R_s[MAX_COD])
{
    char T_c[MAX_COD], R1_h[MAX_COD], R1_s[MAX_COD];
    if (token == TK_Mais) {
        token = le_token();
        if (T(T_c)) {
            sprintf(R1_h, "%s%s\t+\n", R_h, T_c);
            if (R(R1_h, R1_s)) {
                strcpy(R_s, R1_s);
                return 1;
            }
        }
        return 0;
    }
    if (token == TK_Menos) {
        token = le_token();
        if (T(T_c)) {
            sprintf(R1_h, "%s%s\t-\n", R_h, T_c);
            if (R(R1_h, R1_s)) {
                strcpy(R_s, R1_s);
                return 1;
            }
        }
        return 0;
    }
    strcpy(R_s, R_h);
    return 1;
}

int T(char T_c[MAX_COD])
{
    char F_c[MAX_COD], S_h[MAX_COD], S_s[MAX_COD];
    if (F(F_c)) {
        strcpy(S_h, F_c);
        if (S(S_h, S_s)) {
            strcpy(T_c, S_s);
            return 1;
        }
    }
    return 0;
}

int S(char S_h[MAX_COD], char S_s[MAX_COD])
{
    char F_c[MAX_COD], S1_h[MAX_COD], S1_s[MAX_COD];
    if (token == TK_Mult) {
        token = le_token();
        if (F(F_c)) {
            sprintf(S1_h, "%s%s\t*\n", S_h, F_c);
            if (S(S1_h, S1_s)) {
                strcpy(S_s, S1_s);
                return 1;
            }
        }
        return 0;
    }
    if (token == TK_Div) {
        token = le_token();
        if (F(F_c)) {
            sprintf(S1_h, "%s%s\t/\n", S_h, F_c);
            if (S(S1_h, S1_s)) {
                strcpy(S_s, S1_s);
                return 1;
            }
        }
        return 0;
    }
    strcpy(S_s, S_h);
    return 1;
}

// F -> cte | id | (E)
int F(char F_c[MAX_COD])
{
    if (token == TK_Const_Int) {
        sprintf(F_c, "\tpush %s\n", lex);
        token = le_token();
        return 1;
    }
    if (token == TK_id) {
        sprintf(F_c, "\tvalor-r %s\n", lex);
        token = le_token();
        return 1;
    }
    if (token == TK_Abre_Par) {
        char E_c[MAX_COD];
        token = le_token();
        if (E(E_c))
            if (token == TK_Fecha_Par) {
                token = le_token();
                strcpy(F_c, E_c);
                return 1;
            }
    }

    return 0;
}

/**************/
/*            */
/*  COMANDOS  */
/*            */
/**************/

// Atrib -> id = E ; {Atrib.cod = 'valor-L' || id || E.cod || ... }

int Atrib(char Com_c[MAX_COD])
{
    if (token == TK_id) {
        char id[10];
        strcpy(id, lex);
        token = le_token();
        if (token == TK_Atrib) {
            token = le_token();
            char E_c[MAX_COD];
            if (E(E_c)) {
                if (token == TK_pv) {
                    token = le_token();
                    sprintf(Com_c, "\tvalor-l %s\n%s\t:=\n\tpop\n", id, E_c);
                    return 1;
                } else {
                    printf("Faltou ponto-e-vírgula após atribuição\n");
                    return 0;
                }
            }
        }
    }
    return 0;
}

int LAtrib(char LAtrib_c[])
{
    char Atrib_c[MAX_COD];
    char LAtrib2_c[MAX_COD];
    if (Atrib(Atrib_c) != 0) {
        if (LAtrib(LAtrib2_c) != 0) {
            sprintf(LAtrib_c, "%s%s", Atrib_c, LAtrib2_c);
            return 1;
        }
    }
    sprintf(LAtrib_c, "");
    return 1;
}

void geralabel(char label[])
{
    static int numlabel = 0;
    sprintf(label, "LB%03d", numlabel++);
}

int Com(char Comc[MAX_COD]);

int ComExp(char ComExpc[MAX_COD])
{
    char Ec[MAX_COD];
    if (E(Ec))
        if (token == TK_pv) {
            token = le_token();
            strcpy(ComExpc, Ec);
            return 1;
        }
    return 0;
}

int ComIf(char ComIfc[MAX_COD])
{
    if (token == TK_if) {
        token = le_token();
        if (token == TK_Abre_Par) {
            token = le_token();
            char Ec[MAX_COD];
            if (Rel(Ec))
                if (token == TK_Fecha_Par) {
                    token = le_token();
                    char Comc[MAX_COD];
                    if (Com(Comc)) {
                        if (token != TK_else) {
                            char lbfim[10];
                            geralabel(lbfim);
                            sprintf(ComIfc, "%s\tgofalse %s\n%s%s:\n", Ec, lbfim, Comc, lbfim);
                            return 1;
                        } else {
                            token = le_token();
                            char Com2c[MAX_COD];
                            if (Com(Com2c)) {
                                char lbfim[10], lbelse[10];
                                geralabel(lbfim);
                                geralabel(lbelse);
                                sprintf(ComIfc, "%s\tgofalse %s\n%s\tgoto %s\n%s:\n%s%s:\n", Ec, lbelse, Comc, lbfim, lbelse, Com2c, lbfim);
                                return 1;
                            }
                        }
                    }
                }
        }
    }
    return 0;
}

int ComWhile(char ComWhilec[MAX_COD])
{
    if (token == TK_while) {
        token = le_token();
        if (token == TK_Abre_Par) {
            token = le_token();
            char Ec[MAX_COD];
            if (Rel(Ec))
                if (token == TK_Fecha_Par) {
                    token = le_token();
                    char Comc[MAX_COD];
                    if (Com(Comc)) {
                        char lbfim[10], lblaco[10];
                        geralabel(lblaco);
                        geralabel(lbfim);
                        sprintf(ComWhilec, "%s:\n%s\tgofalse %s\n%s\tgoto %s\n%s:\n", lblaco, Ec, lbfim, Comc, lblaco, lbfim);
                        return 1;
                    }
                }
        }
    }
    return 0;
}

int ComComp(char ComCompc[MAX_COD])
{
    if (token == TK_Abre_Chaves) {
        token = le_token();
        strcpy(ComCompc, "");
        while (token != TK_Fecha_Chaves) {
            char Comc[MAX_COD];
            if (Com(Comc))
                strcat(ComCompc, Comc);
            else
                return 0;
        }
        token = le_token();
        return 1;
    }
    return 0;
}

int Com(char Comc[MAX_COD])
{
    if (token == TK_while)
        return ComWhile(Comc);
    if (token == TK_if)
        return ComIf(Comc);
    if (token == TK_Abre_Chaves)
        return ComComp(Comc);
    return ComExp(Comc);
}

int main()
{
    FILE *arqout;
    char Com_c[MAX_COD];

    if ((arqin = fopen("leitura.txt", "rt")) == NULL) {
        printf("Erro na abertura do arquivo");
        exit(0);
    }
    if ((arqout = fopen("saida.kvmp", "wt")) == NULL) {
        printf("Erro na abertura do arquivo de saida");
        exit(0);
    }

    token = le_token();
    if (Com(Com_c) == 0)
        printf("Erro no comando!!!\n");
    else {
        fprintf(arqout, "%s", Com_c);
        printf("%s", Com_c);
    }

    fclose(arqin);
    fclose(arqout);
    system("pause");
    return 0;
}
