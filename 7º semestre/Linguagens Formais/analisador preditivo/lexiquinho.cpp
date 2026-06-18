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
#include <conio.h>
#include <stdlib.h>

char nome[10][20]={"","TKId","TKvoid","TKInt"};

int pos = 0;

int tk;
char lex[20];
int lin=1;
FILE *arqin;
char c; // último caracter lido do arquivo

struct pal_res{char palavra[20]; int tk;};
struct pal_res lista_pal[]={{"void",TKVoid},
                  {"int",TKInt},
                  {"float",TKFloat},
                  {"char",TKChar},
                  {"double",TKDouble},
                  {"else",TKElse},
                  {"if",TKIf},
                  {"fimtabela",TKId}};

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

typedef struct contexto{long posglobal;
               int tkant;
               char cant;
               char lexant[20];} tcontexto;

tcontexto pilhacon[1000];
int topcontexto=0;

void marcaPosToken() {
	pilhacon[topcontexto].posglobal=ftell(arqin);
	pilhacon[topcontexto].tkant=tk;
	pilhacon[topcontexto].cant=c;
    strcpy(pilhacon[topcontexto].lexant,lex);
    topcontexto++;
}

//Implemente aqui a sua funcao restauraPosToken()

void restauraPosToken() {
    topcontexto--;
	fseek(arqin,pilhacon[topcontexto].posglobal,SEEK_SET);
    c=pilhacon[topcontexto].cant;
	tk=pilhacon[topcontexto].tkant;
    strcpy(lex,pilhacon[topcontexto].lexant);
}

void proxC()
{
if (feof(arqin)) {
   c=-1;
//   printf("Chegou no fim de arquivo\n");
   return;
   }
fread(&c,1,1,arqin);
if (c=='\n') lin++;
//printf("Leu caracter %c\n",c);
}

void getToken()
{
int estado=0,
    fim=0,
    posl=0;
while (!fim)
   {
/*printf("%s\n",exp1);
printf("char=%c pos=%d\n",c,pos);*/
   lex[posl++]=c;
   switch(estado){
      case 0:if (c>='a' && c<='z' || c>='A' && c<='Z' || c=='_')
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
             if (c=='='){lex[posl]='\0';proxC();tk=TKAtrib;/*printf("Reconheceu token TKAtrib\n");*/return;}
             if (c=='+')
			    {
			    proxC();
				if (c=='+')
			       {
				   lex[posl++]='+';
     			   lex[posl]='\0';
				   proxC();
				   tk=TKDuploMais;/*printf("Reconheceu token TKDuploMais\n");*/return;
				   }
				else if (c=='=')
			       {
				   lex[posl++]='=';
     			   lex[posl]='\0';
				   proxC();
				   tk=TKAtribMais;/*printf("Reconheceu token TKDuploMais\n");*/return;
				   }
				else
				   {
	               lex[posl]='\0';
				   tk=TKMais;/*printf("Reconheceu token TKSoma\n");*/return;
				   }
			    }
             if (c=='*'){lex[posl]='\0';proxC();tk=TKProd;/*printf("Reconheceu token TKProd\n");*/return;}
             if (c=='['){lex[posl]='\0';proxC();tk=TKAbreColchete;/*printf("Reconheceu token TKAbrePar\n");*/return;}
             if (c==']'){lex[posl]='\0';proxC();tk=TKFechaColchete;/*printf("Reconheceu token TKAbrePar\n");*/return;}
             if (c=='('){lex[posl]='\0';proxC();tk=TKAbrePar;/*printf("Reconheceu token TKAbrePar\n");*/return;}
             if (c==')'){lex[posl]='\0';proxC();tk=TKFechaPar;/*printf("Reconheceu token FechaPar\n");*/return;}
             if (c=='{'){lex[posl]='\0';proxC();tk=TKAbreChaves;/*printf("Reconheceu token TKAbreChaves\n");*/return;}
             if (c=='}'){lex[posl]='\0';proxC();tk=TKFechaChaves;/*printf("Reconheceu token TKFechaChaves\n");*/return;}
             if (c==','){lex[posl]='\0';proxC();tk=TKVirgula;/*printf("Reconheceu token TKVirgula\n");*/return;}
             if (c==';'){lex[posl]='\0';proxC();tk=TKPontoEVirgula;/*printf("Reconheceu token TKPontoEVirgula\n");*/return;}
             if (c==':'){lex[posl]='\0';proxC();tk=TKDoisPontos;/*printf("Reconheceu token TKDoisPontos\n");*/return;}
             if (c=='-'){lex[posl]='\0';proxC();tk=TKSub;/*printf("Reconheceu token TKSub\n");*/return;}
             if (c==-1){lex[posl]='\0';proxC();tk=TKFimArquivo;/*printf("Reconheceu token TKFimArquivo\n");*/return;}
             if (c==' ' || c=='\n' || c=='\t' || c=='\r') {proxC();posl--;break;}
             if (c=='\0') {tk=-1;return;}
             printf("Erro léxico: encontrou o caracter %c (%d) na linha %d\n",c,c,lin);
             while (c!='\n') proxC();
             break;
      case 1:if (c>='a' && c<='z' || c>='A' && c<='Z' || c=='_' || c>='0' && c<='9') {proxC();break;}
             lex[--posl]='\0';
             tk=palavra_reservada(lex);
             //printf("reconheceu token %s\n",lex);
             return;
      } //switch
   }// while
}// função


//int a, b, c;
int R(){
    if(tk==TKVirgula){
        getToken();
        if(tk==TKId){
            getToken();
            if(R()){ return 1; }
            else { return 0; }
        }
        else {
            return 0;
        }
    }
    else if(tk==TKPontoEVirgula){
        getToken();
        return 1;
    } else {
        printf("Esperava ';'");
        return 0;
    }
}

int Dec(){
    if(tk==TKInt){
        getToken();
        if(tk==TKId){
            getToken();
            if(R()){ return 1; }
            else { return 0; }
        } else {
            printf("Esperava identificador");
            return 0;
        }
    } else {
        printf("Esperava tipo");
        return 0;
    }
}


// a + b
int F() {
}

int T(){
    if(tk==TKId){
        getToken();
        return 1;
    }
    return 0;
}

int EL(){
    if(tk==TKMais){
        getToken();
        if(T())
            if(EL())
                return 1;
        return 0;
    }
    return 1;
}

int E(){
    if(T())
        if(EL())
            return 1;
    return 0;
}

int CE(){
    if(E()){
        if(tk==TKPontoEVirgula){
            getToken();
            return 1;
        }
    }
    return 0;
}

int main(){
    arqin=fopen("leitura.cpp","rb");
        if (!arqin) {
        printf("Erro na abertura do fonte.\n");
        return 0;
    }
    proxC(); // lê primeiro caracter do arquivo
    getToken(); // lê primeiro token

    //if(Dec()){
    if(CE()){
        printf("Reconheceu");
    } else {
        printf("\nNao reconheceu");
    }
}
