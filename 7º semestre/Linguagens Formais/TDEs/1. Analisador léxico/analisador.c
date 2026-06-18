#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TKId                1
#define TKVoid              2
#define TKInt               3
#define TKFloat             4
#define TKVirgula           5
#define TKDoisPontos        6
#define TKAbrePar           7
#define TKFechaPar          8
#define TKAtrib             9
#define TKPontoEVirgula    10
#define TKAbreChaves       11
#define TKFechaChaves      12
#define TKMais             13
#define TKDuploMais        14
#define TKProd             15
#define TKChar             16
#define TKSub              17
#define TKAbreColchete     18
#define TKFechaColchete    19
#define TKAtribMais        20
#define TKDouble           21
#define TKCteInt           22
#define TKElse             23
#define TKIf               24
#define TKString           25
#define TKFimArquivo       26
#define TKWhile            27
#define TKDo               28
#define TKFor              29
#define TKSwitch           30
#define TKCase             31
#define TKDefault          32
#define TKReturn           33
#define TKBreak            34
#define TKContinue         35
#define TKSizeof           36
#define TKStruct           37
#define TKTypedef          38
#define TKUnsigned         39
#define TKSigned           40
#define TKLong             41
#define TKShort            42
#define TKConst            43
#define TKStatic           44
#define TKExtern           45
#define TKEnum             46
#define TKUnion            47
#define TKGoto             48
#define TKVolatile         49
#define TKRegister         50
#define TKAuto             51
#define TKDiv              52
#define TKMod              53
#define TKDuploMenos       54
#define TKAtribSub         55
#define TKAtribProd        56
#define TKAtribDiv         57
#define TKAtribMod         58
#define TKAtribAndBit      59
#define TKAtribOrBit       60
#define TKAtribXorBit      61
#define TKAtribShiftLeft   62
#define TKAtribShiftRight  63
#define TKIgual            64
#define TKDiferente        65
#define TKMenor            66
#define TKMaior            67
#define TKMenorIgual       68
#define TKMaiorIgual       69
#define TKE                70
#define TKOu               71
#define TKNao              72
#define TKAndBit           73
#define TKOrBit            74
#define TKXorBit           75
#define TKNotBit           76
#define TKShiftLeft        77
#define TKShiftRight       78
#define TKSeta             79
#define TKPonto            80
#define TKInterrogacao     81
#define TKCteFloat         82
#define TKCteChar          83
#define TKHash             84


char nome[][25] = {
    "",                 "TKId",             "TKVoid",           "TKInt",                "TKFloat",
    "TKVirgula",        "TKDoisPontos",     "TKAbrePar",        "TKFechaPar",           "TKAtrib",
    "TKPontoEVirgula",  "TKAbreChaves",     "TKFechaChaves",    "TKMais",               "TKDuploMais",
    "TKProd",           "TKChar",           "TKSub",            "TKAbreColchete",       "TKFechaColchete",
    "TKAtribMais",      "TKDouble",         "TKCteInt",         "TKElse",               "TKIf",
    "TKString",         "TKFimArquivo",     "TKWhile",          "TKDo",                 "TKFor",
    "TKSwitch",         "TKCase",           "TKDefault",        "TKReturn",             "TKBreak",
    "TKContinue",       "TKSizeof",         "TKStruct",         "TKTypedef",            "TKUnsigned",
    "TKSigned",         "TKLong",           "TKShort",          "TKConst",              "TKStatic",
    "TKExtern",         "TKEnum",           "TKUnion",          "TKGoto",               "TKVolatile",
    "TKRegister",       "TKAuto",           "TKDiv",            "TKMod",                "TKDuploMenos",
    "TKAtribSub",       "TKAtribProd",      "TKAtribDiv",       "TKAtribMod",           "TKAtribAndBit",
    "TKAtribOrBit",     "TKAtribXorBit",    "TKAtribShiftLeft", "TKAtribShiftRight",    "TKIgual",
    "TKDiferente",      "TKMenor",          "TKMaior",          "TKMenorIgual",         "TKMaiorIgual",
    "TKE",              "TKOu",             "TKNao",            "TKAndBit",             "TKOrBit",
    "TKXorBit",         "TKNotBit",         "TKShiftLeft",      "TKShiftRight",         "TKSeta",
    "TKPonto",          "TKInterrogacao",   "TKCteFloat",       "TKCteChar",            "TKHash"
};
int tk;
char lex[520];
int lin = 1;                // linha atual
int col = 0;                // coluna atual
int tk_lin, tk_col;
FILE *arqin;
FILE *arqout;
char c;                     // ultimo caracter lido do arquivo

struct pal_res { char palavra[20]; int tk; };
struct pal_res lista_pal[] = {
    {"void",     TKVoid},
    {"int",      TKInt},
    {"float",    TKFloat},
    {"char",     TKChar},
    {"double",   TKDouble},
    {"else",     TKElse},
    {"if",       TKIf},
    {"while",    TKWhile},
    {"do",       TKDo},
    {"for",      TKFor},
    {"switch",   TKSwitch},
    {"case",     TKCase},
    {"default",  TKDefault},
    {"return",   TKReturn},
    {"break",    TKBreak},
    {"continue", TKContinue},
    {"sizeof",   TKSizeof},
    {"struct",   TKStruct},
    {"typedef",  TKTypedef},
    {"unsigned", TKUnsigned},
    {"signed",   TKSigned},
    {"long",     TKLong},
    {"short",    TKShort},
    {"const",    TKConst},
    {"static",   TKStatic},
    {"extern",   TKExtern},
    {"enum",     TKEnum},
    {"union",    TKUnion},
    {"goto",     TKGoto},
    {"volatile", TKVolatile},
    {"register", TKRegister},
    {"auto",     TKAuto},
    {"fimtabela", TKId}
};


typedef struct contexto {   // Retrocesso do arquivo
    long posglobal;
    int tkant;
    char cant;
    char lexant[520];
    int linant;             // linha anterior
    int colant;             // coluna anterior
} tcontexto;

tcontexto pilhacon[1000];
int topcontexto = 0;

int palavra_reservada(char lex[]) {
    int postab = 0;
    while (strcmp("fimtabela", lista_pal[postab].palavra) != 0) {
        if (strcmp(lex, lista_pal[postab].palavra) == 0)
            return lista_pal[postab].tk;
        postab++;
    }
    return TKId;
}

void marcaPosToken() {
    pilhacon[topcontexto].posglobal = ftell(arqin);
    pilhacon[topcontexto].tkant = tk;
    pilhacon[topcontexto].cant = c;
    strcpy(pilhacon[topcontexto].lexant, lex);
    pilhacon[topcontexto].linant = lin;
    pilhacon[topcontexto].colant = col;
    topcontexto++;
}

void restauraPosToken() {
    topcontexto--;
    fseek(arqin, pilhacon[topcontexto].posglobal, SEEK_SET);
    c = pilhacon[topcontexto].cant;
    tk = pilhacon[topcontexto].tkant;
    strcpy(lex, pilhacon[topcontexto].lexant);
    lin = pilhacon[topcontexto].linant;
    col = pilhacon[topcontexto].colant;
}

//Avanço do arquivo
void proxC() {
    if (feof(arqin) || fread(&c, 1, 1, arqin) != 1) {
        c = -1;
        return;
    }

    if (c == '\n') {
        lin++;
        col = 0;
    } else if (c != '\r') {
        col++;
    }
}

void getToken() {
    int posl, tokenEncontrado = 0;

    while(!tokenEncontrado){
        /* Ignorar espacos em branco */
        while (c == ' ' || c == '\n' || c == '\t' || c == '\r') proxC();

        /* Fim de arquivo */
        if (c == -1 || c == '\0') {
            lex[0] = '\0';
            tk_lin = lin;
            tk_col = col;
            tk = TKFimArquivo;
            return;
        }

        /* Posicao inicial do token */
        tk_lin = lin;
        tk_col = col;
        posl = 0;

        // Palavras reservadas
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_') {
            while ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
                    c == '_' || (c >= '0' && c <= '9')) {
                if (posl < 510) lex[posl++] = c;
                proxC();
            }
            lex[posl] = '\0';
            tk = palavra_reservada(lex);
            return;
        }

        if (c >= '0' && c <= '9') {
            int ehFloat = 0;

            // Verificar hexadecimal (0x...)
            if (c == '0') {
                lex[posl++] = c;
                proxC();
                if (c == 'x' || c == 'X') {
                    lex[posl++] = c;
                    proxC();
                    while ((c >= '0' && c <= '9') ||
                        (c >= 'a' && c <= 'f') ||
                        (c >= 'A' && c <= 'F')) {
                        if (posl < 510) lex[posl++] = c;
                        proxC();
                    }
                    lex[posl] = '\0';
                    tk = TKCteInt;
                    return;
                }
            } else {
                lex[posl++] = c;
                proxC();
            }

            // Digitos decimais
            while (c >= '0' && c <= '9') {
                if (posl < 510) lex[posl++] = c;
                proxC();
            }

            // Parte fracionaria
            if (c == '.') {
                ehFloat = 1;
                if (posl < 510) lex[posl++] = c;
                proxC();
                while (c >= '0' && c <= '9') {
                    if (posl < 510) lex[posl++] = c;
                    proxC();
                }
            }

            // Expoente
            if (c == 'e' || c == 'E') {
                ehFloat = 1;
                if (posl < 510) lex[posl++] = c;
                proxC();
                if (c == '+' || c == '-') {
                    if (posl < 510) lex[posl++] = c;
                    proxC();
                }
                while (c >= '0' && c <= '9') {
                    if (posl < 510) lex[posl++] = c;
                    proxC();
                }
            }

            // Sufixos numericos
            if (c == 'f' || c == 'F') {
                ehFloat = 1;
                if (posl < 510) lex[posl++] = c;
                proxC();
            } else if (c == 'l' || c == 'L' || c == 'u' || c == 'U') {
                if (posl < 510) lex[posl++] = c;
                proxC();
                if (c == 'l' || c == 'L' || c == 'u' || c == 'U') {
                    if (posl < 510) lex[posl++] = c;
                    proxC();
                }
            }

            lex[posl] = '\0';
            tk = ehFloat ? TKCteFloat : TKCteInt;
            return;
        }

        // Strings
        if (c == '"') {
            lex[posl++] = c;
            proxC();
            while (c != '"' && c != -1 && c != '\n') {
                if (c == '\\') {
                    if (posl < 510) lex[posl++] = c;
                    proxC();
                }
                if (posl < 510) lex[posl++] = c;
                proxC();
            }
            if (c == '"') {
                if (posl < 510) lex[posl++] = c;
                proxC();
            }
            lex[posl] = '\0';
            tk = TKString;
            return;
        }

        if (c == '\'') {
            lex[posl++] = c;
            proxC();
            if (c == '\\') {
                if (posl < 510) lex[posl++] = c;
                proxC();
            }
            if (c != '\'' && c != -1) {
                if (posl < 510) lex[posl++] = c;
                proxC();
            }
            if (c == '\'') {
                if (posl < 510) lex[posl++] = c;
                proxC();
            }
            lex[posl] = '\0';
            tk = TKCteChar;
            return;
        }

        switch (c) {
            // Operadores mamtematicos
            case '+':
                lex[posl++] = c; proxC();
                if (c == '+') { lex[posl++] = c; lex[posl] = '\0'; proxC(); tk = TKDuploMais; return; }
                if (c == '=') { lex[posl++] = c; lex[posl] = '\0'; proxC(); tk = TKAtribMais; return; }
                lex[posl] = '\0'; tk = TKMais; return;
            case '-':
                lex[posl++] = c; proxC();
                if (c == '-') { lex[posl++] = c; lex[posl] = '\0'; proxC(); tk = TKDuploMenos; return; }
                if (c == '=') { lex[posl++] = c; lex[posl] = '\0'; proxC(); tk = TKAtribSub; return; }
                if (c == '>') { lex[posl++] = c; lex[posl] = '\0'; proxC(); tk = TKSeta; return; }
                lex[posl] = '\0'; tk = TKSub; return;
            case '*':
                lex[posl++] = c; proxC();
                if (c == '=') { lex[posl++] = c; lex[posl] = '\0'; proxC(); tk = TKAtribProd; return; }
                lex[posl] = '\0'; tk = TKProd; return;
            case '/':
                lex[posl++] = c; proxC();
                if (c == '/') { // Comentario de linha
                    while (c != '\n' && c != -1) proxC();
                    tokenEncontrado = 1;
                    continue;
                }
                if (c == '*') { //Comentario de bloco
                    proxC();
                    while (1) {
                        if (c == -1) break;
                        if (c == '*') {
                            proxC();
                            if (c == '/') { proxC(); break; }
                        } else {
                            proxC();
                        }
                    }
                    tokenEncontrado = 1;
                    continue;
                }
                if (c == '=') { lex[posl++] = c; lex[posl] = '\0'; proxC(); tk = TKAtribDiv; return; }
                lex[posl] = '\0'; tk = TKDiv; return;
            case '%':
                lex[posl++] = c; proxC();
                if (c == '=') { lex[posl++] = c; lex[posl] = '\0'; proxC(); tk = TKAtribMod; return; }
                lex[posl] = '\0'; tk = TKMod; return;

            // Operadores relacionais
            case '=':
                lex[posl++] = c; proxC();
                if (c == '=') { lex[posl++] = c; lex[posl] = '\0'; proxC(); tk = TKIgual; return; }
                lex[posl] = '\0'; tk = TKAtrib; return;
            case '!':
                lex[posl++] = c; proxC();
                if (c == '=') { lex[posl++] = c; lex[posl] = '\0'; proxC(); tk = TKDiferente; return; }
                lex[posl] = '\0'; tk = TKNao; return;
            case '<':
                lex[posl++] = c; proxC();
                if (c == '=') { lex[posl++] = c; lex[posl] = '\0'; proxC(); tk = TKMenorIgual; return; }
                if (c == '<') {
                    lex[posl++] = c; proxC();
                    if (c == '=') { lex[posl++] = c; lex[posl] = '\0'; proxC(); tk = TKAtribShiftLeft; return; }
                    lex[posl] = '\0'; tk = TKShiftLeft; return;
                }
                lex[posl] = '\0'; tk = TKMenor; return;
            case '>':
                lex[posl++] = c; proxC();
                if (c == '=') { lex[posl++] = c; lex[posl] = '\0'; proxC(); tk = TKMaiorIgual; return; }
                if (c == '>') {
                    lex[posl++] = c; proxC();
                    if (c == '=') { lex[posl++] = c; lex[posl] = '\0'; proxC(); tk = TKAtribShiftRight; return; }
                    lex[posl] = '\0'; tk = TKShiftRight; return;
                }
                lex[posl] = '\0'; tk = TKMaior; return;


            // Operadores bitwise
            case '&':
                lex[posl++] = c; proxC();
                if (c == '&') { lex[posl++] = c; lex[posl] = '\0'; proxC(); tk = TKE; return; }
                if (c == '=') { lex[posl++] = c; lex[posl] = '\0'; proxC(); tk = TKAtribAndBit; return; }
                lex[posl] = '\0'; tk = TKAndBit; return;

            case '|':
                lex[posl++] = c; proxC();
                if (c == '|') { lex[posl++] = c; lex[posl] = '\0'; proxC(); tk = TKOu; return; }
                if (c == '=') { lex[posl++] = c; lex[posl] = '\0'; proxC(); tk = TKAtribOrBit; return; }
                lex[posl] = '\0'; tk = TKOrBit; return;

            case '^':
                lex[posl++] = c; proxC();
                if (c == '=') { lex[posl++] = c; lex[posl] = '\0'; proxC(); tk = TKAtribXorBit; return; }
                lex[posl] = '\0'; tk = TKXorBit; return;

            case '~':
                lex[posl++] = c; lex[posl] = '\0'; proxC();
                tk = TKNotBit; return;

            case '?': // Operador ternário
                lex[posl++] = c; lex[posl] = '\0'; proxC();
                tk = TKInterrogacao; return;

            case '.':
                proxC();
                if (c >= '0' && c <= '9') {
                    lex[posl++] = '.';
                    while (c >= '0' && c <= '9') {
                        if (posl < 510) lex[posl++] = c;
                        proxC();
                    }
                    if (c == 'e' || c == 'E') {
                        if (posl < 510) lex[posl++] = c;
                        proxC();
                        if (c == '+' || c == '-') { if (posl < 510) lex[posl++] = c; proxC(); }
                        while (c >= '0' && c <= '9') { if (posl < 510) lex[posl++] = c; proxC(); }
                    }
                    lex[posl] = '\0';
                    tk = TKCteFloat;
                    return;
                }
                lex[0] = '.'; lex[1] = '\0';
                tk = TKPonto; return;

            case '#':   // INCLUDE, DEFINE, ...
                lex[posl++] = c; lex[posl] = '\0'; proxC();
                tk = TKHash; return;

            case '(': lex[0] = '('; lex[1] = '\0'; proxC(); tk = TKAbrePar; return;
            case ')': lex[0] = ')'; lex[1] = '\0'; proxC(); tk = TKFechaPar; return;
            case '{': lex[0] = '{'; lex[1] = '\0'; proxC(); tk = TKAbreChaves; return;
            case '}': lex[0] = '}'; lex[1] = '\0'; proxC(); tk = TKFechaChaves; return;
            case '[': lex[0] = '['; lex[1] = '\0'; proxC(); tk = TKAbreColchete; return;
            case ']': lex[0] = ']'; lex[1] = '\0'; proxC(); tk = TKFechaColchete; return;
            case ',': lex[0] = ','; lex[1] = '\0'; proxC(); tk = TKVirgula; return;
            case ';': lex[0] = ';'; lex[1] = '\0'; proxC(); tk = TKPontoEVirgula; return;
            case ':': lex[0] = ':'; lex[1] = '\0'; proxC(); tk = TKDoisPontos; return;

            default:
                printf("Erro lexico: caracter '%c' (%d) na linha %d, coluna %d\n", c, c, lin, col);
                proxC();
                tokenEncontrado = 1;
                continue;
        }
    }
}

int main() {
    char
        *arquivo = "leitura.c",
        *saida = "resultado_analise.txt";

    arqin = fopen(arquivo, "rb");
    arqout = fopen(saida, "w");

    printf("Arquivo analisado: %s\n", arquivo);
    printf("Arquivo de saida: %s\n", saida);
    printf("========================================\n\n");

    fprintf(arqout, "Arquivo: %s\n", arquivo);
    fprintf(arqout, "========================================\n\n");

    printf("%3s | %-22s | %6s | %6s | %s\n", "ID", "Token", "Linha", "Coluna", "Lexema");
    printf("%-3s-+-%-22s-+-%6s-+-%6s-+-%s\n", "---", "----------------------", "------", "------", "--------------------");

    fprintf(arqout, "%3s | %-22s | %6s | %6s | %s\n", "ID", "Token", "Linha", "Coluna", "Lexema");
    fprintf(arqout, "%-3s-+-%-22s-+-%6s-+-%6s-+-%s\n", "---", "----------------------", "------", "------", "--------------------");

    proxC();
    getToken();
    while (tk != TKFimArquivo) {
        printf("%3d | %-22s | %6d | %6d | %s\n", tk, nome[tk], tk_lin, tk_col, lex);
        fprintf(arqout, "%3d | %-22s | %6d | %6d | %s\n", tk, nome[tk], tk_lin, tk_col, lex);
        getToken();
    }

    fclose(arqin);
    fclose(arqout);

    return 0;
}
