#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TK_int 1
#define TK_float 2
#define TK_char 3
#define TK_struct 4
#define TK_if 5
#define TK_else 6
#define TK_while 7

#define TK_id 8
#define TK_Abre_Colch 9
#define TK_Fecha_Colch 10
#define TK_Abre_Chaves 11
#define TK_Fecha_Chaves 12
#define TK_Fim_Arquivo 13
#define TK_Atrib 14
#define TK_Const_Int 15
#define TK_Mais 16
#define TK_Menos 17
#define TK_Mult 18
#define TK_Abre_Par 19
#define TK_Fecha_Par 20
#define TK_virgula 21
#define TK_pv 22
#define TK_Maior 23
#define TK_Menor 24
#define TK_Menor_Igual 25
#define TK_Maior_Igual 26
#define TK_Igual 27
#define TK_Diferente 28

/***********************************************************************************/
/*                                                                                 */
/*  INICIO DO LEXICO - Nao entre a nao ser que tenha interesse pessoal em lexicos  */
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
    "TK_id",
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
    "TK_Diferente"
};

char reservadas[][20] = {"", "int", "float", "char", "struct", "if", "else", "while", "fim"};

FILE *arqin;
int token;
char c;
char lex[20];

// variaveis globais para retrocesso

typedef struct contexto {
    long posglobal;
    int tkant;
    char cant;
    char lexant[20];
} tcontexto;

tcontexto pilhacon[1000];
int topcontexto = 0;

void marcaPosToken() {
    pilhacon[topcontexto].posglobal = ftell(arqin);
    pilhacon[topcontexto].tkant = token;
    pilhacon[topcontexto].cant = c;
    strcpy(pilhacon[topcontexto].lexant, lex);
    topcontexto++;
}

// Implemente aqui a sua funcao restauraPosToken()

void restauraPosToken() {
    topcontexto--;
    fseek(arqin, pilhacon[topcontexto].posglobal, SEEK_SET);
    c = pilhacon[topcontexto].cant;
    token = pilhacon[topcontexto].tkant;
    strcpy(lex, pilhacon[topcontexto].lexant);
}

char le_char() {
    if (fread(&c, 1, 1, arqin) == 0) {
        return -1;
    }
    if (c == '\n') {
        linlex++;
        collex = 1;
    } else {
        collex++;
    }
    return c;
}

int pal_res(char lex[]) {
    int tk = 0;
    while (strcmp(reservadas[tk], "fim") != 0) {
        if (strcmp(lex, reservadas[tk]) == 0) {
            return tk;
        }
        tk++;
    }
    return TK_id;
}

int le_token() {
    static int pos = 0;
    static int estado = 0;
    while (1) {
        switch (estado) {
            case 0:
                if (c == ',') {
                    c = le_char();
                    return TK_virgula;
                }
                if (c == '+') {
                    c = le_char();
                    printf("Reconheci tkmais\n");
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
                if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_') {
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
                if (c == -1) {
                    return TK_Fim_Arquivo;
                }
                if (c == '\n' || c == '\r' || c == '\t' || c == '\0' || c == ' ') {
                    c = le_char();
                    break;
                }
                // Se encontrar caractere nao mapeado, avanca para nao travar em loop infinito
                c = le_char();
                break;

            case 1:
                if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' || (c >= '0' && c <= '9')) {
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
/*  FIM DO LEXICO   */
/*                  */
/********************/

#define MAX_COD 1000

void mostra_t() {
    printf("%s lex=%s na lin %d, col %d\n", tokens[token], lex, linlex, collex);
}

/****************/
/*              */
/*  EXPRESSOES  */
/*              */
/****************/

int E15(char E15_c[MAX_COD]); // operador virgula
int RE15(char RE15_h[MAX_COD], char RE15_s[MAX_COD]); // operador virgula
int E14(char E14_c[MAX_COD]); // atribuicao
int E(char E_c[MAX_COD]);
int R(char R_h[MAX_COD], char R_s[MAX_COD]);
int T(char T_c[MAX_COD]);
int S(char S_h[MAX_COD], char S_s[MAX_COD]);
int F(char F_c[MAX_COD]);
int Rel(char Rel_c[MAX_COD]);
int Com(char Com_c[MAX_COD]);
int Lista_Com(char Lista_Com_c[MAX_COD]);
int Com_if(char Com_c[MAX_COD]);
int Com_while(char Com_c[MAX_COD]);
int LL(char LL_c[MAX_COD]);
void geralabel(char label[]);

// E15 -> E14 RE15
// RE15 -> , E14 RE15
// RE15 -> vazio

int E15(char E15_c[MAX_COD]) {
    printf("Entrei no E15\n");
    char E14_c[MAX_COD], RE15_h[MAX_COD], RE15_s[MAX_COD];
    if (E14(E14_c)) {
        strcpy(RE15_h, E14_c);
        if (RE15(RE15_h, RE15_s)) {
            strcpy(E15_c, RE15_s);
            return 1;
        }
    }
    return 0;
}

// RE15 -> , RE14 {RE15f.h = RE15.h || RE14.t || '+'} RE15f {RE15.s=RE15f.s }
// RE15 -> vazio {RE15.s = RE15.h}

int RE15(char RE15_h[MAX_COD], char RE15_s[MAX_COD]) {
    printf("Entrei no RE15\n");
    char E14_c[MAX_COD], RE15f_h[MAX_COD], RE15f_s[MAX_COD];
    if (token == TK_virgula) {
        printf("Achei a virgula\n");
        token = le_token();
        if (E14(E14_c)) {
            sprintf(RE15f_h, "%s\tpop\n%s", RE15_h, E14_c);
            printf("Reconheci\n%s", RE15f_h);
            if (RE15(RE15f_h, RE15f_s)) {
                strcpy(RE15_s, RE15f_s);
                return 1;
            }
        }
        return 0;
    }
    strcpy(RE15_s, RE15_h);
    return 1;
}

// E14 -> id = E14
// E14 -> E13

int E14(char E14_c[MAX_COD]) {
    char E_c[MAX_COD];
    marcaPosToken();
    if (token == TK_id) {
        char id[10];
        strcpy(id, lex);
        token = le_token();
        if (token == TK_Atrib) {
            token = le_token();
            if (E(E_c)) {
                sprintf(E14_c, "\tvalor-l %s\n%s\t:=\n\tpop\n\tvalor-r %s\n", id, E_c, id);
                return 1;
            }
        }
    }
    restauraPosToken();
    return E(E14_c);
}

int Rel(char Rel_c[MAX_COD]) {
    printf("Entrei no Rel\n");
    char E1_c[MAX_COD], E2_c[MAX_COD];
    if (E(E1_c)) {
        char op[10] = "";
        if (token == TK_Maior) strcpy(op, ">");
        else if (token == TK_Menor) strcpy(op, "<");
        else if (token == TK_Igual) strcpy(op, "=");
        else if (token == TK_Diferente) strcpy(op, "<>");
        else if (token == TK_Maior_Igual) strcpy(op, ">=");
        else if (token == TK_Menor_Igual) strcpy(op, "<=");

        printf("Voltei do E, token e %s op e %s\n", tokens[token], op);
        if (token == TK_Maior || token == TK_Menor || token == TK_Igual ||
            token == TK_Diferente || token == TK_Maior_Igual || token == TK_Menor_Igual) {
            token = le_token();
            if (E(E2_c)) {
                printf("Voltei do E2, token e %s\n", tokens[token]);
                sprintf(Rel_c, "%s%s\t%s\n", E1_c, E2_c, op);
                return 1;
            }
            return 0;
        } else {
            strcpy(Rel_c, E1_c);
            printf("Vou retornar 1 no E\n");
            return 1;
        }
    }
    return 0;
}

// E -> T {R.h=T.t} R {E.t=R.s}

int E(char E_c[MAX_COD]) {
    printf("Entrei no E. Lexema=%s\n", lex);
    char T_c[MAX_COD], R_h[MAX_COD], R_s[MAX_COD];
    if (T(T_c)) {
        strcpy(R_h, T_c);
        printf("Em T gerei\n %s", T_c);
        if (R(R_h, R_s)) {
            strcpy(E_c, R_s);
            return 1;
        }
    }
    return 0;
}

// R -> +T {R1.h = R.h || T.t || '+'}R1{R.s=R1.s }
// R -> vazio {R.s = R.h}

int R(char R_h[MAX_COD], char R_s[MAX_COD]) {
    printf("Entrei no R. Lexema=%s\n", lex);
    char T_c[MAX_COD], R1_h[MAX_COD], R1_s[MAX_COD];
    if (token == TK_Mais) {
        token = le_token();
        if (T(T_c)) {
            sprintf(R1_h, "%s%s\t+\n", R_h, T_c);
            printf("Em R reconheci %s", R1_h);
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
            strcpy(R1_h, R_h);
            strcat(R1_h, T_c);
            strcat(R1_h, "\t-\n");
            if (R(R1_h, R1_s)) {
                strcpy(R_s, R1_s);
                return 1;
            }
        }
        return 0;
    }
    strcpy(R_s, R_h);
    printf("Vou retornar 1 no R\n");
    return 1;
}

int T(char T_c[MAX_COD]) {
    char F_c[MAX_COD], S_h[MAX_COD], S_s[MAX_COD];
    printf("Entrei no T\n");
    if (F(F_c)) {
        strcpy(S_h, F_c);
        if (S(S_h, S_s)) {
            strcpy(T_c, S_s);
            return 1;
        }
    }
    return 0;
}

int S(char S_h[MAX_COD], char S_s[MAX_COD]) {
    printf("Entrei no S (*FS)\n");
    char F_c[MAX_COD], S1_h[MAX_COD], S1_s[MAX_COD];
    if (token == TK_Mult) {
        token = le_token();
        if (F(F_c)) {
            strcpy(S1_h, S_h);
            strcat(S1_h, F_c);
            strcat(S1_h, "\t*\n");
            if (S(S1_h, S1_s)) {
                strcpy(S_s, S1_s);
                return 1;
            }
        }
        return 0;
    }
    strcpy(S_s, S_h);
    printf("Vou retornar 1 no S\n");
    return 1;
}

int F(char F_c[MAX_COD]) {
    printf("Entrei no F\n");

    if (token == TK_Const_Int) {
        strcpy(F_c, "\tpush ");
        strcat(F_c, lex);
        strcat(F_c, "\n");
        token = le_token();
        return 1;
    }
    if (token == TK_id) {
        strcpy(F_c, "\tvalor-r ");
        strcat(F_c, lex);
        strcat(F_c, "\n");
        token = le_token();
        return 1;
    }
    if (token == TK_Abre_Par) {
        char E_c[MAX_COD];
        token = le_token();
        if (E(E_c)) {
            if (token == TK_Fecha_Par) {
                token = le_token();
                strcpy(F_c, E_c);
                return 1;
            }
        }
    }

    return 0;
}

/**************/
/*            */
/*  COMANDOS  */
/*            */
/**************/

int LL(char LL_c[MAX_COD]) {
    printf("Entrei no LL\n");
    char LL1_c[MAX_COD], Com_c[MAX_COD];

    if (token == TK_id || token == TK_pv || token == TK_if || token == TK_while || token == TK_Abre_Chaves) {
        if (Com(Com_c)) {
            printf("C - token e %s\n", tokens[token]);
            if (LL(LL1_c)) {
                strcpy(LL_c, Com_c);
                strcat(LL_c, LL1_c);
                printf("A-Vou retornar 1 no LL\n");
                return 1;
            }
            printf("B-Vou retornar 0 no LL porque deu erro no LL\n");
            return 0;
        } else {
            printf("C-Vou retornar 0 no LL porque deu erro no Com\n");
            return 0;
        }
    } else {
        strcpy(LL_c, "");
        printf("D-Vou retornar 1 no LL\n");
        return 1;
    }
}

/* Lista_Com ->

*/

int Lista_Com(char Lista_Com_c[MAX_COD]) {
    printf("Entrei no Lista_Com\n");

    char LL_c[MAX_COD];
    char Com_c[MAX_COD];
    printf("Vou testar Com - token e %s\n", tokens[token]);
    if (token == TK_Fim_Arquivo) {
        return 1;
    }
    if (Com(Com_c)) {
        printf("B - token e %s\n", tokens[token]);
        if (LL(LL_c)) {
            strcpy(Lista_Com_c, Com_c);
            strcat(Lista_Com_c, LL_c);
            printf("Vou retornar 1 no Lista_Com. Token e %s\n", tokens[token]);
            return 1;
        }
        printf("Vou retornar 0 no Lista_Com-1 - token e %s\n", tokens[token]);
        return 0;
    }
    if (token == TK_Fim_Arquivo) {
        return 1;
    }
    printf("Vou retornar 0 no Lista_Com-2\n");
    return 0;
}

void geralabel(char label[]) {
    static int numlabel = 0;
    sprintf(label, "LB%03d", numlabel++);
}

int Com_if(char Com_c[MAX_COD]) {
    char Rel_c[MAX_COD];
    char labelelse[10], labelfim[10];
    geralabel(labelelse);
    geralabel(labelfim);
    token = le_token();
    if (token == TK_Abre_Par) {
        token = le_token();
        if (Rel(Rel_c)) {
            if (token == TK_Fecha_Par) {
                token = le_token();
                if (Com(Com_c)) {
                    if (token == TK_else) {
                        token = le_token();
                        char Com2_c[MAX_COD];
                        if (Com(Com2_c)) {
                            sprintf(Com_c, "%s\tgofalse %s\n%sgoto %s\nrotulo %s\n%srotulo %s\n",
                                    Rel_c, labelelse, Com_c, labelfim, labelelse, Com2_c, labelfim);
                            return 1;
                        } else {
                            printf("Erro no comando do else\n");
                            return 0;
                        }
                    } else {
                        printf("Esperava palavra else\n");
                        return 0;
                    }
                }
            } else {
                printf("Esperava fecha parenteses\n");
                return 0;
            }
        } else {
            printf("Erro na expressao do if \n");
            return 0;
        }
    } else {
        printf("Esperava abre parenteses\n");
        return 0;
    }
    return 0;
}

int Com_while(char Com_c[MAX_COD]) {
    char Rel_c[MAX_COD];
    char labelinicio[10], labelfim[10];
    geralabel(labelinicio);
    geralabel(labelfim);
    token = le_token();
    if (token == TK_Abre_Par) {
        token = le_token();
        if (Rel(Rel_c)) {
            if (token == TK_Fecha_Par) {
                token = le_token();
                char Com1_c[MAX_COD];
                if (Com(Com1_c)) {
                    sprintf(Com_c, "rotulo %s\n%s\tgofalse %s\n%sgoto %s\nrotulo %s\n",
                            labelinicio, Rel_c, labelfim, Com1_c, labelinicio, labelfim);
                    return 1;
                } else {
                    printf("Erro no comando do while\n");
                    return 0;
                }
            } else {
                printf("Esperava fecha parenteses\n");
                return 0;
            }
        } else {
            printf("Erro na expressao do while\n");
            return 0;
        }
    } else {
        printf("Esperava abre parenteses\n");
        return 0;
    }
    return 0;
}

int Com(char Com_c[MAX_COD]) {
    printf("Entrei no Com\n");
    if (token == TK_if) {
        return Com_if(Com_c);
    }
    if (token == TK_while) {
        return Com_while(Com_c);
    }
    if (token == TK_id) {
        char E15_c[MAX_COD];
        if (E15(E15_c)) {
            if (token == TK_pv) {
                token = le_token();
                strcpy(Com_c, E15_c);
                return 1;
            } else {
                printf("Faltou ponto-e-virgula em comando expressao\n");
                return 0;
            }
        }
    } else if (token == TK_Abre_Chaves) {
        char Lista_Com_c[MAX_COD];
        token = le_token();
        printf("Consumi o abre chaves\n");
        if (Lista_Com(Lista_Com_c)) {
            printf("Voltei do Lista_Com. Token=%s\n", tokens[token]);
            if (token == TK_Fecha_Chaves) {
                token = le_token();
                printf("Consumi o fecha chaves\n");
                strcpy(Com_c, Lista_Com_c);
                return 1;
            } else {
                printf("Esperava fecha chaves na linha %d\n", linlex);
                return 0;
            }
        }
    } else if (token == TK_pv) {
        printf("Vou retornar 1 no Com com ponto e virgula\n");
        token = le_token();
        return 1;
    } else {
        printf("Vou retornar 0 no Com vazio - token e %s\n", tokens[token]);
        return 1;
    }
    return 0;
}

int main() {
    char Com_C[MAX_COD];
    if ((arqin = fopen("leitura.txt", "rt")) == NULL) {
        printf("Erro na abertura do arquivo\n");
        exit(0);
    }
    token = le_token();

    if (Com(Com_C) == 0) {
        printf("Erro no comando!!!\n");
    } else {
        printf("%s", Com_C);
    }
    fclose(arqin);
    system("pause");
    return 0;
}
