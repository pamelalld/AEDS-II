#include <stdio.h>
#include <stdlib.h>

typedef struct TipoNo *TipoApontador;

typedef struct TipoNo{
    int chave;
    TipoApontador esq,dir;
}TipoNo;

void Ordem_Remove(TipoApontador* no);
void Insere(TipoApontador* no,int x);
void Antecessor(TipoApontador q, TipoApontador *r);
void Remove(int x,TipoApontador* no);
int Pesquisa_ordem(TipoApontador *no);

int main(){

    TipoApontador raiz=NULL;
    int n,elemento;

    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&elemento);
        Insere(&raiz,elemento);
    }
    
    Ordem_Remove(&raiz);

    return 0;
}

void Ordem_Remove(TipoApontador* no){

    if(*no==NULL){
        return;
    }
    Ordem_Remove(&(*no)->esq);
    printf("%d ",(*no)->chave); 
    Ordem_Remove(&(*no)->dir);
    Remove((*no)->chave,no);
    //Com o uso recursivo de remoção dentro de "Em ordem" não consegui encontrar uma forma de evitar erro de segmentação e ao mesmo tempo manter a ideia principal da implementação estudada.
    //Pensei em fazer com que a função de remoção me retornasse um ponteiro para nó após realizar os ajustes na árvore, para garantir que eu não perdesse acesso ao filho à direita  
    //mas optei por manter a busca e impressão dos elementos seguindo o método "em ordem" e fazer a remoção através de "Pós-ordem"
}
void Remove(int x,TipoApontador* no){
    TipoApontador Aux;
    if (*no == NULL) 
    { printf("Erro : Registro nao esta na arvore\n");
    return;
    }
    if (x < (*no)->chave) { Remove(x, &(*no)->esq); return; }
    if (x > (*no)->chave) { Remove(x, &(*no)->dir); return; }
    if ((*no)->dir == NULL) 
    { Aux = *no;  *no = (*no)->esq;
    
    free(Aux);
        return;
    }
    if ((*no)->esq != NULL) 
    { Antecessor(*no, &(*no)->esq);
        return;
    }
    Aux = *no;  *no = (*no)->dir;
    
    free(Aux);
}
void Antecessor(TipoApontador q, TipoApontador *r){

    if ((*r)->dir != NULL){ 
    Antecessor(q, &(*r)->dir);
    return;
    }
    
    q->chave = (*r)->chave;
    q = *r; 
    *r = (*r)->esq;
    
    free(q);
}

void Insere(TipoApontador* no,int x){

    if(*no==NULL){
        *no=(TipoApontador)malloc(sizeof(TipoNo));
        (*no)->chave=x;
        (*no)->esq=NULL;
        (*no)->dir=NULL;
        return;
    }
    if(x<(*no)->chave){
        Insere(&(*no)->esq,x);
        return;
    }
    if(x>(*no)->chave){
        Insere(&(*no)->dir,x);
    }
    else{
        printf("Registro não encontrado\n");
    }
}

int Pesquisa_ordem(TipoApontador *no){ 
    
    if(*no==NULL){
        return 0;
    }
    Pesquisa_ordem(&(*no)->esq);

    printf("%d ",(*no)->chave); 

    Pesquisa_ordem(&(*no)->dir);

    return 1;
}
