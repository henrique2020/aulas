#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

struct nodo{
  int info;
  struct nodo *prox;
}elemento;

struct nodo *inicio;
char resp;
int valor;

// Procedimento para inserção no inicio da lista
void insere(int dado)
{
  struct nodo *pnovo;
  pnovo=(struct nodo*)malloc(sizeof(elemento));
  pnovo->info=dado;
  pnovo->prox=NULL;  
  if(inicio == NULL){
     inicio = pnovo;
  }
  else{
     pnovo->prox=inicio;
	 inicio=pnovo;   
  }
}

// Procedimento para inserção no fim da lista
void insereFim(int dado)
{
  struct nodo *pnovo;

  pnovo=(struct nodo*)malloc(sizeof(elemento));
  pnovo->info=dado;
  pnovo->prox=NULL;  

  struct nodo *atual = inicio;
  if(inicio == NULL){
     inicio = pnovo;
  }
  else{
	  while(atual->prox != NULL){
		  atual = atual->prox;
	  }
      atual->prox = pnovo;   
  }
}
//Procedimento que retorna o tamanho da lista
int tamanhoLista()
{
  struct nodo *primeiro = inicio;
  int res=0;
  
  while(primeiro != NULL){
	 res++;
	 primeiro=primeiro->prox;
  }
  return res;
}

// Procedimento para consultar um valor na lista
int consulta(int valor)
{
  int resp = 0;  
  struct nodo *atual = inicio;
  while(atual != NULL){
	 if(atual->info == valor){
        resp = 1;
     }
	 atual = atual->prox;
  }
  return resp;
}

// Procedimento para inserção no meio da lista
void insereMeio(int dado, int pos)
{
  struct nodo *pnovo;
  struct nodo *atual = inicio;
  struct nodo *ant = inicio;
  int i=0;
  int tamanho=0;
  
  pnovo=(struct nodo*)malloc(sizeof(elemento));
  pnovo->info=dado;
  pnovo->prox=NULL;  

  tamanho = tamanhoLista();
  if(tamanho == 0){
     inicio = pnovo;
  }
  else{
       if(pos <= 1){ //insere no inicio
          insere(valor);
       }
       else{
            if(pos >= tamanho){
               insereFim(valor);
            }
            else{ //posicao válida
               for(i=1;i<pos;i++){
                  ant = atual;
                  atual = atual->prox;
               }
               ant->prox = pnovo;
               pnovo->prox = atual;   
            }
       }
  }
}

// Procedimento para excluir um valor do inicio da lista
void exclui()
{
  int resp = 0;  
  struct nodo *atual = inicio;
  if(inicio != NULL){
    inicio = inicio->prox;
    free(atual); //libera o espaço ocupado na memória
  }
  else{
     printf("Lista Vazia\n");  
  }
}

// Procedimento para excluir um valor do fim da lista
void excluiFim()
{
  int resp = 0;  
  struct nodo *atual = inicio;
  struct nodo *ant = NULL;
  if(inicio != NULL){
     while(atual->prox != NULL){
        ant = atual;
        atual = atual->prox;
     }
     ant->prox = NULL;
     free(atual);
  }
  else{
     printf("Lista Vazia\n");  
  }
}

// Procedimento para excluir um valor da lista
void excluiValor(int valor)
{
  int resp = 0;  
  struct nodo *atual = inicio;
  struct nodo *ant = NULL;
  
  if(inicio != NULL){ //Lista existe
     if(consulta(valor) != 1){ // Verifica se o valor existe na lista
        printf("Valor %d nao existe na lista\n",valor);
     }
     else{
          if(inicio->prox == NULL){ //testa se a lista só possui um elemento
          // Valor existe na lista, mas a lista só possui um elemento
             free(inicio);
             inicio = NULL;
          }
          else{
               if(atual->info == valor){ //Lista possui vários elementos e o elemento a ser excluido é o primeiro
                  exclui();
               }
               else{ //acha o valor a ser excluído
                  while(atual->info != valor){
                     ant = atual;
                     atual = atual->prox;
                  }
                  ant->prox = atual->prox;
                  free(atual);
               }
          }  
     }
  }
  else{
     printf("Lista Vazia\n");  
  }
}



// Procedimento para escrever a lista na tela
void escreve()
{
  struct nodo *primeiro = inicio;
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
     printf("3 - Insere no Meio da Lista\n");
     printf("4 - Exclui no Inicio da Lista\n");
     printf("5 - Exclui no Fim da Lista\n");
     printf("6 - Exclui um valor Lista\n");
     printf("7 - Consulta um valor\n");
     printf("8 - Escreve a Lista\n");
     printf("0 - Fim\n");
}

int main(){
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
                  insere(valor);
                  break;
                  
        case '2': printf("Digite o valor:\n");
                  scanf("%d",&valor);
                  fflush(stdin);
                  insereFim(valor);
                  break;
                  
        case '3': printf("Digite o valor:\n");
                  scanf("%d",&valor);
                  fflush(stdin);
                  
                  printf("Digite a posicao:\n");
                  scanf("%d",&pos);
                  fflush(stdin);
                  insereMeio(valor,pos);
                  break;
                  
        case '4': exclui();
                  break;
                  
        case '5': excluiFim();
                  break;
                  
        case '6': printf("Digite o valor:\n");
                  scanf("%d",&valor);
                  fflush(stdin);
                  excluiValor(valor);
                  break;
        case '7': printf("Digite o valor:\n");
                  scanf("%d",&valor);
                  fflush(stdin);
                  existe = consulta(valor);
                  if(existe==1)
                     printf("Valor %d esta presente na lista\n",valor);
                  else
                     printf("Valor %d nao esta presente na lista\n",valor);
                  break;
        case '8': escreve();
                  break;       
     }              
                   
     menu();
     fflush(stdin);             
	 printf("Digite sua opcao:\n");
	 resp=getch();
  }
}
