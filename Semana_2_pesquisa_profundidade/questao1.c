#include <stdio.h>
#include <stdlib.h>

typedef struct TipoNo *TipoApontador; //define um ponteiro para um nó

typedef struct TipoNo{
    int chave;
    TipoApontador esq,dir;
}TipoNo; //o nó armazena um valor chave e também dois ponteiros para os seus filhos

void inicializa(TipoApontador *no){ //inicializa um nó raiz com valor nulo
    *no=NULL; 
}

int pesquisa_pre_ordem(TipoApontador *no){ //a partir de recursividade, imprime os elementos presentes na árvore seguindo o método "Pré-ordem": raiz -> esquerda -> direita
    
    int x;
    if(*no==NULL){
        return 0;
    }

    printf("%d ",x=(*no)->chave); 

    pesquisa_pre_ordem(&(*no)->esq);

    pesquisa_pre_ordem(&(*no)->dir);

    return 1;
}

void pesquisa_em_ordem(TipoApontador *no){ //a partir de recursividade, imprime os elementos presentes na árvore seguindo o método "Em ordem": esquerda -> raiz -> direita
    
    if(*no==NULL){
        return;
    }
    pesquisa_em_ordem(&(*no)->esq);

    printf("%d ",(*no)->chave); 

    pesquisa_em_ordem(&(*no)->dir);

    return;
}

int pesquisa_pos_ordem(TipoApontador *no){ //a partir de recursividade, imprime os elementos presentes na árvore seguindo o método "Pós-ordem": esquerda -> direita -> raiz
    
    int x;
    if(*no==NULL){
        return 0;
    }

    pesquisa_pos_ordem(&(*no)->esq);

    pesquisa_pos_ordem(&(*no)->dir);

    printf("%d ",x=(*no)->chave); 

    return 1;
}

void insere(int x,TipoApontador*no){ //faz a insercao na árvore, respeitando as condições de: maiores à direita e menores à esquerda de cada raiz
    if(*no==NULL){
        *no=(TipoApontador)malloc(sizeof(TipoNo));
        (*no)->chave=x;
        (*no)->esq=NULL;
        (*no)->dir=NULL;
        return;
    }
    if(x<(*no)->chave){
        insere(x,&(*no)->esq);
        return;
    }
    if(x>(*no)->chave){
        insere(x,&(*no)->dir);
    }
    else{
        printf("Registro não encontrado\n");
    }

}

int main(){
    TipoApontador noRaiz;
    int n,valor;
    inicializa(&noRaiz);

    scanf("%d",&n);
    for (int i=0;i<n;i++){
        scanf("%d",&valor);
        insere(valor,&noRaiz);
    }

    printf("Pré-Ordem: ");
    pesquisa_pre_ordem(&noRaiz);
    printf("\n");

    printf("Em Ordem: ");
    pesquisa_em_ordem(&noRaiz);
    printf("\n");

    printf("Pós-Ordem: ");
    pesquisa_pos_ordem(&noRaiz);
    printf("\n");


    return 0;
}

int contador (TipoApontador*no){
    if (*no==NULL){
        return 0;
    }
    return 1+ contador((*no)->esq)+contador((*no)->dir); 
}


