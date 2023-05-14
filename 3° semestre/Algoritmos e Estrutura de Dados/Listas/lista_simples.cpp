#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

struct nodo{
  int info;
  struct nodo *prox;
}elemento;


char resp;
int valor;

// Procedimento para inserção no inicio da lista
void insere(int dado, struct nodo **ini)
{
  struct nodo *pnovo;
  pnovo=(struct nodo*)malloc(sizeof(elemento));
  pnovo->info=dado;
  pnovo->prox=NULL;
  if(ini == NULL){
     *ini = pnovo;
  }
  else{
     pnovo->prox=*ini;
	 *ini=pnovo;
  }
}

// Procedimento para inserção no fim da lista
void insereFim(int dado, struct nodo **ini)
{
  struct nodo *pnovo;

  pnovo=(struct nodo*)malloc(sizeof(elemento));
  pnovo->info=dado;
  pnovo->prox=NULL;

  struct nodo *atual = *ini;
  if(*ini == NULL){
     *ini = pnovo;
  }
  else{
	  while(atual->prox != NULL){
		  atual = atual->prox;
	  }
      atual->prox = pnovo;
  }
}

// Procedimento para escrever a lista na tela
void escreve(struct nodo *ini)
{
  struct nodo *primeiro = ini;
  if(primeiro == NULL){
     printf("Lista Vazia\n");
  }
  else{
     while(primeiro != NULL){
	    printf("Elemento: %d \n",primeiro->info);
	    primeiro=primeiro->prox;
     }
   }
}

void menu(){
     printf("1 - Insere no Inicio da Lista\n");
     printf("2 - Insere no Fim da Lista\n");
     printf("8 - Escreve a Lista\n");
     printf("0 - Fim\n");
}

int main(){
  struct nodo *inicio;
  int existe=0, pos=0;
  resp='n';
  inicio=NULL;

  menu();
  fflush(stdin);
  printf("Digite sua opcao:\n");
  resp=getch();
  while((resp>='1') && (resp<='8')){
     switch(resp){
        case '1': printf("Digite o valor:\n");
                  scanf("%d",&valor);
                  fflush(stdin);
                  insere(valor,&inicio);
                  break;

        case '2': printf("Digite o valor:\n");
                  scanf("%d",&valor);
                  fflush(stdin);
                  insereFim(valor,&inicio);
                  break;

        case '8': escreve(inicio);
                  break;
     }

     menu();
     fflush(stdin);
	 printf("Digite sua opcao:\n");
	 resp=getch();
  }
}
