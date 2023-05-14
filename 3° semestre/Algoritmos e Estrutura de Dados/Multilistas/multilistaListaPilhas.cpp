#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

struct pilha{
  int valor;
  struct pilha *proxp;
};

struct nodo{
  int idpilha;
  struct pilha *topo;
  struct nodo *prox;
};


char resp;
int valor;

// Procedimento para inserção no inicio da lista
void insere(int numpilha, struct nodo **ini)
{
  struct nodo *pnovo;
  pnovo=(struct nodo*)malloc(sizeof(struct nodo));
  pnovo->idpilha=numpilha;
  pnovo->topo=NULL;
  pnovo->prox=NULL;
  if(ini == NULL){
     *ini = pnovo;
  }
  else{
     pnovo->prox=*ini;
	 *ini=pnovo;
  }
  printf("\ninseriu nodo com a pilha %d na lista\n\n",numpilha);
}

void empilha(int pilha, int dado, struct nodo *ini)
{
  struct pilha *pnovo;
  
  while(ini != NULL && ini->idpilha!=pilha){
     ini = ini->prox;
  }
  if(ini != NULL){
  	pnovo=(struct pilha*)malloc(sizeof(struct pilha));
  	pnovo->valor=dado;
    pnovo->proxp=ini->topo;
	ini->topo=pnovo;
	printf("\nempilhou %d na pilha %d\n\n",dado,pilha);
  }
  else
  	printf("\nnão achou a pilha\n\n");
}


int main(){
  struct nodo *inicio;
  inicio=NULL;

  insere(1,&inicio);
  insere(2,&inicio);
  insere(3,&inicio);     
  empilha(2,5,inicio);
  empilha(2,7,inicio);
}
