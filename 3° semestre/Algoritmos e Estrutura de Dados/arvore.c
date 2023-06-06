#include <stdio.h>

typedef struct noA{
    int info;
    struct noA *esq;
    struct noA *dir;
} TNoA;

void posOrdem(TNoA* a, char d){
  if (a!= NULL){
    if(d == 'e'){
      posOrdem(a->esq, d);
      posOrdem(a->dir, d);
      printf("%d\n",a->info);
    } else if (d == 'd'){
      posOrdem(a->dir, d);
      posOrdem(a->esq, d);
      printf("%d\n",a->info);
    }
  }
}

void central(TNoA* a, char d){
  if (a!= NULL){
    if(d == 'e'){
      central(a->esq, d);
      printf("%d\n",a->info);
      central(a->dir, d);
    } else if (d == 'd'){
      central(a->dir, d);
      printf("%d\n",a->info);
      central(a->esq, d);
    }
  }
}

void preordem(TNoA* a, char d){
  if (a!= NULL){
    if(d == 'e'){
      printf("%d\n",a->info);
      preordem(a->esq, d);
      preordem(a->dir, d);
    } else if (d == 'd'){
      printf("%d\n",a->info);
      preordem(a->dir, d);
      preordem(a->esq, d);
    }
  }
}

void escreveFolhas(TNoA* a){
  if (a!= NULL){
    if(a->esq == NULL && a->dir == NULL){
        printf("%d\n",a->info);
    }
    escreveFolhas(a->esq);
    escreveFolhas(a->dir);
  }
}

TNoA *criaNo(char ch) {
  TNoA *novo;
  novo = (TNoA *) malloc(sizeof(TNoA));
  novo->info = ch;
  novo->esq = NULL;
  novo->dir = NULL;
  return novo;
}

int main(void) {
  TNoA *raiz;
  raiz = criaNo(5);
  //No da esquerda
  raiz->esq = criaNo(10);
  raiz->esq->esq = criaNo(2);
  raiz->esq->dir = criaNo(8);
  raiz->esq->dir->esq = criaNo(3);
  //No da direita
  raiz->dir = criaNo(7);
  raiz->dir->dir = criaNo(1);

  printf("PRE-ORDEM\n");
  printf("ESQUERDA: \n");
  preordem(raiz, 'e');
  printf("DIREITA: \n");
  preordem(raiz, 'd');
  printf("\n-------------------------------------\n\n");
  printf("CENTRAL\n");
  printf("ESQUERDA: \n");
  central(raiz, 'e');
  printf("DIREITA: \n");
  central(raiz, 'd');
  printf("\n-------------------------------------\n\n");
  printf("POS-ORDEM\n");
  printf("ESQUERDA: \n");
  posOrdem(raiz, 'e');
  printf("DIREITA: \n");
  posOrdem(raiz, 'd');

  printf("\n\n\n");
  printf("ESCREVE FOLHAS:\n");
  escreveFolhas(raiz);
};