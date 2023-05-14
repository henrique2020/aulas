//Exemplo com inicio passado como parâmetro
struct nodo{
  int info;
  struct nodo *prox;
};

typedef struct nodo Elemento;


void insereinicio(Elemento **ini,int valor){
    Elemento *novo;
    
    novo=(Elemento*) malloc(sizeof(Elemento));
    novo->info=valor;
    novo->prox=NULL;
    
    if(*ini==NULL)
        *ini=novo;
    else{
        novo->prox=*ini;
        *ini=novo;
    }    
}

void exibelista(Elemento *ini){
    Elemento *aux=ini;

    printf("\nLista:\n");    
    while(aux!=NULL){
        printf("%d ",aux->info);
        aux=aux->prox;
    }
    printf("\n\n");
}

int main(){
    Elemento *inicio=NULL;
    
    insereinicio(&inicio,5);
    insereinicio(&inicio,2);
    exibelista(inicio);
    insereinicio(&inicio,7);
    insereinicio(&inicio,10);
    insereinicio(&inicio,1);
    insereinicio(&inicio,3);
    exibelista(inicio);
}