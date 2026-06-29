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
    "TKPonto",          "TKInterrogacao",   "TKCteFloat",       "TKCteChar",
};

int tk;
char lex[520];
int lin = 1;
int col = 0;
int tk_lin, tk_col;
FILE *arqin;
char c;

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

typedef struct contexto {
    long posglobal;
    int tkant;
    char cant;
    char lexant[520];
    int linant;
    int colant;
} tcontexto;

tcontexto pilhacon[1000];
int topcontexto = 0;


// ANALISADOR LÉXICO (168 até 421)
int palavra_reservada(char lex[]) {
    int postab = 0;
    while (strcmp("fimtabela", lista_pal[postab].palavra) != 0) {
        if (strcmp(lex, lista_pal[postab].palavra) == 0)
            return lista_pal[postab].tk;
        postab++;
    }
    return TKId;
}

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
        while (c == ' ' || c == '\n' || c == '\t' || c == '\r') proxC();

        if (c == -1 || c == '\0') {
            lex[0] = '\0';
            tk_lin = lin;
            tk_col = col;
            tk = TKFimArquivo;
            return;
        }

        tk_lin = lin;
        tk_col = col;
        posl = 0;

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
            if (c == '0') {
                lex[posl++] = c; proxC();
                if (c == 'x' || c == 'X') {
                    lex[posl++] = c; proxC();
                    while ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F')) {
                        if (posl < 510) lex[posl++] = c; proxC();
                    }
                    lex[posl] = '\0'; tk = TKCteInt; return;
                }
            } else {
                lex[posl++] = c; proxC();
            }

            while (c >= '0' && c <= '9') {
                if (posl < 510) lex[posl++] = c; proxC();
            }

            if (c == '.') {
                ehFloat = 1;
                if (posl < 510) lex[posl++] = c; proxC();
                while (c >= '0' && c <= '9') {
                    if (posl < 510) lex[posl++] = c; proxC();
                }
            }

            if (c == 'e' || c == 'E') {
                ehFloat = 1;
                if (posl < 510) lex[posl++] = c; proxC();
                if (c == '+' || c == '-') {
                    if (posl < 510) lex[posl++] = c; proxC();
                }
                while (c >= '0' && c <= '9') {
                    if (posl < 510) lex[posl++] = c; proxC();
                }
            }

            if (c == 'f' || c == 'F') {
                ehFloat = 1;
                if (posl < 510) lex[posl++] = c; proxC();
            } else if (c == 'l' || c == 'L' || c == 'u' || c == 'U') {
                if (posl < 510) lex[posl++] = c; proxC();
                if (c == 'l' || c == 'L' || c == 'u' || c == 'U') {
                    if (posl < 510) lex[posl++] = c; proxC();
                }
            }

            lex[posl] = '\0';
            tk = ehFloat ? TKCteFloat : TKCteInt;
            return;
        }

        if (c == '"') {
            lex[posl++] = c; proxC();
            while (c != '"' && c != -1 && c != '\n') {
                if (c == '\\') { if (posl < 510) lex[posl++] = c; proxC(); }
                if (posl < 510) lex[posl++] = c; proxC();
            }
            if (c == '"') { if (posl < 510) lex[posl++] = c; proxC(); }
            lex[posl] = '\0'; tk = TKString; return;
        }

        if (c == '\'') {
            lex[posl++] = c; proxC();

            if (c == '\\') {
                if (posl < 510) lex[posl++] = c;
                proxC();

                if (c != -1) {
                    if (posl < 510) lex[posl++] = c;
                    proxC();
                }
            } else if (c != '\'' && c != -1) {
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
                if (c == '/') {
                    while (c != '\n' && c != -1) proxC();
                    continue;
                }
                if (c == '*') {
                    proxC();
                    while (1) {
                        if (c == -1) break;
                        if (c == '*') {
                            proxC();
                            if (c == '/') { proxC(); break; }
                        } else { proxC(); }
                    }
                    continue;
                }
                if (c == '=') { lex[posl++] = c; lex[posl] = '\0'; proxC(); tk = TKAtribDiv; return; }
                lex[posl] = '\0'; tk = TKDiv; return;
            case '%':
                lex[posl++] = c; proxC();
                if (c == '=') { lex[posl++] = c; lex[posl] = '\0'; proxC(); tk = TKAtribMod; return; }
                lex[posl] = '\0'; tk = TKMod; return;
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
                lex[posl++] = c; lex[posl] = '\0'; proxC(); tk = TKNotBit; return;
            case '?':
                lex[posl++] = c; lex[posl] = '\0'; proxC(); tk = TKInterrogacao; return;
            case '.':
                proxC();
                if (c >= '0' && c <= '9') {
                    lex[posl++] = '.';
                    while (c >= '0' && c <= '9') { if (posl < 510) lex[posl++] = c; proxC(); }
                    if (c == 'e' || c == 'E') {
                        if (posl < 510) lex[posl++] = c; proxC();
                        if (c == '+' || c == '-') { if (posl < 510) lex[posl++] = c; proxC(); }
                        while (c >= '0' && c <= '9') { if (posl < 510) lex[posl++] = c; proxC(); }
                    }
                    lex[posl] = '\0'; tk = TKCteFloat; return;
                }
                lex[0] = '.'; lex[1] = '\0'; tk = TKPonto; return;
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

// ANALISADOR SINTÁTICO (424 até 762)
void parse_programa();       /* Ponto de entrada do parser | Avalia declarações globais em laço até o fim do arquivo */
void parse_declaracao();     /* Declarações de variáveis e funções globais | Encadeia para parse_tipo, parse_resto_var e parse_bloco */
void parse_tipo();           /* Tipos primitivos, structs e typedefs | Valida as palavras-chave de tipo de dado */
void parse_resto_var();      /* Finaliza declarações de variáveis (arrays vazios/cheios e inicializações) | Encadeia para parse_expr e parse_inicializador */
void parse_inicializador();  /* Atribuições literais e listas com chaves {...} | Encadeia para parse_atribuicao ou chama a si mesma (recursiva) */
void parse_bloco();          /* Escopo fechado entre chaves { ... } | Encadeia para parse_tipo (variáveis locais) ou parse_comando */
void parse_comando();        /* Estruturas de controle (if, while, for, switch, return) ou expressões terminadas em ';' | Encadeia para parse_expr e parse_bloco */
void parse_expr();           /* Expressões separadas por vírgula (ex: a=1, b=2) | Encadeia para parse_atribuicao */
void parse_atribuicao();     /* Atribuições simples e compostas (=, +=, -=, <<=, &=, etc.) | Encadeia para parse_ternario */
void parse_ternario();       /* Operador condicional ternário (? :) | Encadeia para parse_logico_ou */
void parse_logico_ou();      /* Operador lógico OR (||) | Encadeia para parse_logico_e */
void parse_logico_e();       /* Operador lógico AND (&&) | Encadeia para parse_bit_ou */
void parse_bit_ou();         /* Operador bit a bit OR (|) | Encadeia para parse_bit_xor */
void parse_bit_xor();        /* Operador bit a bit XOR (^) | Encadeia para parse_bit_e */
void parse_bit_e();          /* Operador bit a bit AND (&) | Encadeia para parse_igualdade */
void parse_igualdade();      /* Operadores de igualdade e diferença (==, !=) | Encadeia para parse_relacional */
void parse_relacional();     /* Operadores de comparação (>, <, >=, <=) | Encadeia para parse_shift */
void parse_shift();          /* Deslocamento de bits shift-left e shift-right (<<, >>) | Encadeia para parse_aditiva */
void parse_aditiva();        /* Adições e subtrações (+, -) | Encadeia para parse_multiplicativa */
void parse_multiplicativa(); /* Multiplicação, divisão e resto (*, /, %) | Encadeia para parse_unaria */
void parse_unaria();         /* Sinais unários, ponteiros, not (!, ~, *, &, +, -) | Encadeia para parse_posfixa */
void parse_posfixa();        /* Acesso a arrays [], struct (., ->), chamadas de função () e incr/decr (++, --) | Encadeia para parse_primaria */
void parse_primaria();       /* A "folha" da árvore: Identificadores, constantes (int, float, char, string) e parênteses '(' expr ')' */

void eat(int token_esperado) {
    if (tk == token_esperado) {
        getToken();
    } else {
        printf("\nERRO SINTATICO [Linha %d, Coluna %d]:\n", tk_lin, tk_col);
        printf(" -> Esperado token: %s\n", nome[token_esperado]);
        printf(" -> Encontrado: %s ('%s')\n", nome[tk], lex);
        exit(1);
    }
}

int is_tipo() {
    return (tk == TKInt || tk == TKLong || tk == TKFloat || tk == TKChar ||
            tk == TKDouble || tk == TKVoid || tk == TKUnsigned ||
            tk == TKStruct || tk == TKTypedef ||
            (tk == TKId && (strcmp(lex, "FILE") == 0 || strcmp(lex, "tcontexto") == 0)));
}

void parse_tipo() {
    if (tk == TKTypedef) eat(TKTypedef);
    if (tk == TKUnsigned) eat(TKUnsigned);

    if (tk == TKInt) eat(TKInt);
    else if (tk == TKLong) {
        eat(TKLong);
        if (tk == TKLong) eat(TKLong);
        if (tk == TKInt) eat(TKInt);
    }
    else if (tk == TKFloat) eat(TKFloat);
    else if (tk == TKChar) eat(TKChar);
    else if (tk == TKDouble) eat(TKDouble);
    else if (tk == TKVoid) eat(TKVoid);
    else if (tk == TKStruct) {
        eat(TKStruct);
        eat(TKId);
        if (tk == TKAbreChaves) {
            eat(TKAbreChaves);
            while (tk != TKFechaChaves) {
                parse_tipo();
                while (tk == TKProd) eat(TKProd);
                eat(TKId);
                parse_resto_var();
                while (tk == TKVirgula) {
                    eat(TKVirgula);
                    while (tk == TKProd) eat(TKProd);
                    eat(TKId);
                    parse_resto_var();
                }
                eat(TKPontoEVirgula);
            }
            eat(TKFechaChaves);
        }
    }
    else if (tk == TKId && (strcmp(lex, "FILE") == 0 || strcmp(lex, "tcontexto") == 0)) {
        eat(TKId);
    }
    else {
        printf("ERRO SINTATICO [Linha %d]: Tipo invalido '%s'\n", tk_lin, lex);
        exit(1);
    }
}

void parse_inicializador() {
    if (tk == TKAbreChaves) {
        eat(TKAbreChaves);
        if (tk != TKFechaChaves) {
            parse_inicializador();
            while (tk == TKVirgula) {
                eat(TKVirgula);
                if (tk == TKFechaChaves) break;
                parse_inicializador();
            }
        }
        eat(TKFechaChaves);
    } else {
        parse_atribuicao();
    }
}

void parse_resto_var() {
    while (tk == TKAbreColchete) {
        eat(TKAbreColchete);
        if (tk != TKFechaColchete) parse_expr();
        eat(TKFechaColchete);
    }
    if (tk == TKAtrib) {
        eat(TKAtrib); parse_inicializador();
    }
}

void parse_primaria() {
    if (tk == TKId) eat(TKId);
    else if (tk == TKCteInt) eat(TKCteInt);
    else if (tk == TKCteFloat) eat(TKCteFloat);
    else if (tk == TKCteChar) eat(TKCteChar);
    else if (tk == TKString) eat(TKString);
    else if (tk == TKAbrePar) {
        eat(TKAbrePar); parse_expr(); eat(TKFechaPar);
    }
    else if (tk == TKSizeof) {
        eat(TKSizeof); eat(TKAbrePar);
        if (is_tipo()) { parse_tipo(); while(tk == TKProd) eat(TKProd); }
        else { parse_expr(); }
        eat(TKFechaPar);
    } else {
        printf("ERRO SINTATICO [Linha %d, Coluna %d]: Expressao invalida '%s'\n", tk_lin, tk_col, lex);
        exit(1);
    }
}

void parse_posfixa() {
    parse_primaria();
    while (tk == TKAbreColchete || tk == TKAbrePar || tk == TKPonto || tk == TKSeta || tk == TKDuploMais || tk == TKDuploMenos) {
        if (tk == TKAbreColchete) {
            eat(TKAbreColchete); parse_expr(); eat(TKFechaColchete);
        } else if (tk == TKAbrePar) {
            eat(TKAbrePar);
            if (tk != TKFechaPar) {
                parse_atribuicao();
                while (tk == TKVirgula) { eat(TKVirgula); parse_atribuicao(); }
            }
            eat(TKFechaPar);
        } else if (tk == TKPonto || tk == TKSeta) {
            eat(tk); eat(TKId);
        } else if (tk == TKDuploMais || tk == TKDuploMenos) {
            eat(tk);
        }
    }
}

void parse_unaria() {
    if (tk == TKSub || tk == TKMais || tk == TKNao || tk == TKNotBit || tk == TKProd || tk == TKAndBit) {
        eat(tk); parse_unaria();
    } else {
        parse_posfixa();
    }
}

void parse_multiplicativa() {
    parse_unaria();
    while (tk == TKProd || tk == TKDiv || tk == TKMod) { eat(tk); parse_unaria(); }
}

void parse_aditiva() {
    parse_multiplicativa();
    while (tk == TKMais || tk == TKSub) { eat(tk); parse_multiplicativa(); }
}

void parse_shift() {
    parse_aditiva();
    while (tk == TKShiftLeft || tk == TKShiftRight) { eat(tk); parse_aditiva(); }
}

void parse_relacional() {
    parse_shift();
    while (tk == TKMenor || tk == TKMaior || tk == TKMenorIgual || tk == TKMaiorIgual) { eat(tk); parse_shift(); }
}

void parse_igualdade() {
    parse_relacional();
    while (tk == TKIgual || tk == TKDiferente) { eat(tk); parse_relacional(); }
}

void parse_bit_e() {
    parse_igualdade();
    while (tk == TKAndBit) { eat(tk); parse_igualdade(); }
}

void parse_bit_xor() {
    parse_bit_e();
    while (tk == TKXorBit) { eat(tk); parse_bit_e(); }
}

void parse_bit_ou() {
    parse_bit_xor();
    while (tk == TKOrBit) { eat(tk); parse_bit_xor(); }
}

void parse_logico_e() {
    parse_bit_ou();
    while (tk == TKE) { eat(tk); parse_bit_ou(); }
}

void parse_logico_ou() {
    parse_logico_e();
    while (tk == TKOu) { eat(tk); parse_logico_e(); }
}

void parse_ternario() {
    parse_logico_ou();
    if (tk == TKInterrogacao) {
        eat(TKInterrogacao);
        parse_expr();
        eat(TKDoisPontos);
        parse_ternario();
    }
}

void parse_atribuicao() {
    parse_ternario();
    if (tk == TKAtrib || tk == TKAtribMais || tk == TKAtribSub ||
        tk == TKAtribProd || tk == TKAtribDiv || tk == TKAtribMod ||
        tk == TKAtribShiftLeft || tk == TKAtribShiftRight ||
        tk == TKAtribAndBit || tk == TKAtribOrBit || tk == TKAtribXorBit) {
        eat(tk); parse_atribuicao();
    }
}

void parse_expr() {
    parse_atribuicao();
    while (tk == TKVirgula) { eat(TKVirgula); parse_atribuicao(); }
}

void parse_comando() {
    if (tk == TKAbreChaves) {
        parse_bloco();
    } else if (tk == TKIf) {
        eat(TKIf); eat(TKAbrePar); parse_expr(); eat(TKFechaPar);
        parse_comando();
        if (tk == TKElse) { eat(TKElse); parse_comando(); }
    } else if (tk == TKWhile) {
        eat(TKWhile); eat(TKAbrePar); parse_expr(); eat(TKFechaPar); parse_comando();
    } else if (tk == TKDo) {
        eat(TKDo); parse_comando();
        eat(TKWhile); eat(TKAbrePar); parse_expr(); eat(TKFechaPar); eat(TKPontoEVirgula);
    } else if (tk == TKFor) {
        eat(TKFor); eat(TKAbrePar);
        if (tk != TKPontoEVirgula) parse_expr(); eat(TKPontoEVirgula);
        if (tk != TKPontoEVirgula) parse_expr(); eat(TKPontoEVirgula);
        if (tk != TKFechaPar) parse_expr(); eat(TKFechaPar);
        parse_comando();
    } else if (tk == TKSwitch) {
        eat(TKSwitch); eat(TKAbrePar); parse_expr(); eat(TKFechaPar); parse_comando();
    } else if (tk == TKCase) {
        eat(TKCase); parse_expr(); eat(TKDoisPontos);
    } else if (tk == TKDefault) {
        eat(TKDefault); eat(TKDoisPontos);
    } else if (tk == TKBreak) {
        eat(TKBreak); eat(TKPontoEVirgula);
    } else if (tk == TKContinue) {
        eat(TKContinue); eat(TKPontoEVirgula);
    } else if (tk == TKReturn) {
        eat(TKReturn);
        if (tk != TKPontoEVirgula) parse_expr();
        eat(TKPontoEVirgula);
    } else if (tk == TKPontoEVirgula) {
        eat(TKPontoEVirgula);
    } else {
        parse_expr(); eat(TKPontoEVirgula);
    }
}

void parse_bloco() {
    eat(TKAbreChaves);
    while (tk != TKFechaChaves && tk != TKFimArquivo) {
        if (is_tipo()) {
            parse_tipo();
            while (tk == TKProd) eat(TKProd);
            eat(TKId);
            parse_resto_var();
            while (tk == TKVirgula) {
                eat(TKVirgula);
                while (tk == TKProd) eat(TKProd);
                eat(TKId);
                parse_resto_var();
            }
            eat(TKPontoEVirgula);
        } else {
            parse_comando();
        }
    }
    eat(TKFechaChaves);
}

void parse_declaracao() {
    parse_tipo();

    if (tk == TKPontoEVirgula) {
        eat(TKPontoEVirgula);
        return;
    }

    while (tk == TKProd) eat(TKProd);
    eat(TKId);

    if (tk == TKAbrePar) {
        eat(TKAbrePar);
        if (is_tipo()) {
            parse_tipo();
            while (tk == TKProd) eat(TKProd);
            eat(TKId);
            while (tk == TKAbreColchete) { eat(TKAbreColchete); if (tk!=TKFechaColchete) parse_expr(); eat(TKFechaColchete); }

            while (tk == TKVirgula) {
                eat(TKVirgula);
                parse_tipo();
                while (tk == TKProd) eat(TKProd);
                eat(TKId);
                while (tk == TKAbreColchete) { eat(TKAbreColchete); if (tk!=TKFechaColchete) parse_expr(); eat(TKFechaColchete); }
            }
        }
        eat(TKFechaPar);
        if (tk == TKPontoEVirgula) eat(TKPontoEVirgula);
        else parse_bloco();
    } else {
        parse_resto_var();
        while (tk == TKVirgula) {
            eat(TKVirgula);
            while (tk == TKProd) eat(TKProd);
            eat(TKId);
            parse_resto_var();
        }
        eat(TKPontoEVirgula);
    }
}

void parse_programa() {
    while (tk != TKFimArquivo) {
        parse_declaracao();
    }
    printf("ANALISE SINTATICA CONCLUIDA COM SUCESSO!\n");
}


int main() {
    char *arquivo = "teste.c";

    arqin = fopen(arquivo, "rb");
    if (!arqin) {
        printf("Erro ao abrir arquivo '%s'\n", arquivo);
        return 1;
    }

    printf("Iniciando Analise Lexica e Sintatica...\n");
    printf("Arquivo analisado: %s\n", arquivo);
    printf("========================================\n\n");

    proxC();
    getToken();

    parse_programa();

    fclose(arqin);
    return 0;
}
