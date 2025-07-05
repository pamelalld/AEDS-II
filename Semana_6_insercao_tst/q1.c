#include <stdio.h>
#include <stdlib.h>

typedef struct TipoNo* TipoApontador;

typedef struct TipoNo{

    char data;
    unsigned EndOfString:1;
    TipoApontador left,right,equal;

}TipoNo;

TipoApontador inicializa_no(char data);
void libera_tst(TipoApontador* root);
void insere_tst(TipoApontador* root,char* word);
int busca_tst(TipoApontador root,char* word);

int main(){

    int n=0;
    char nome[30];
     TipoApontador root=NULL;

    scanf("%d",&n);
    while (n!=0){
    
        for(int i=0;i<n;i++){
            scanf("%s",nome);
            insere_tst(&root,nome);
        }

        scanf("%s",nome);

        if(busca_tst(root,nome)){
            printf("Pessoa Encontrada\n");
        }
        else{
            printf("Pessoa Não Encontrada\n");
        }
        libera_tst(&root); //"reinicia" a árvore
        scanf("%d",&n);
    }
}

TipoApontador inicializa_no(char data){//inicializa um novo nó, alocando memória e atribuindo valores

    TipoApontador temp=(TipoApontador)malloc(sizeof(TipoNo));
    temp->data=data;
    temp->EndOfString=0;
    temp->left=temp->equal=temp->right=NULL;

    return temp;
}

void insere_tst(TipoApontador* root,char* word){ //insere a palavra na árvore, um caractere por nó, respeitando as regras da tst
    if(*root==NULL){
        *root= inicializa_no(*word);
    }
    if((*word)<(*root)->data){
        insere_tst(&((*root)->left),word);
    }
    else if((*word)>(*root)->data){
        insere_tst(&((*root)->right),word);
    }
    else{
        if (*(word+1)){
            insere_tst(&((*root)->equal),word+1);
        }
        else{
            (*root)->EndOfString=1;
        }
    }
}

int busca_tst(TipoApontador root,char* word){ //busca um nome na árvore
    if(root==NULL){
        return 0;
    }
    if(*word<(root)->data){
        return busca_tst(root->left,word);
    }
    else if (*word>(root)->data){
        return busca_tst(root->right,word);
    }
    else{
        if(*(word+1)=='\0'){
            return root->EndOfString;
        }
        return busca_tst((root)->equal,word+1);
    }
}

void libera_tst(TipoApontador* root){ // a partir de uma busca em pos-ordem, retira todas as flags "endOfString" para que estrutura da árvore possa ser reutilizada com uma nova listagem de pessoas
    if ((*root)==NULL){
        return;
    }
    libera_tst(&(*root)->left);
    libera_tst(&(*root)->equal);
    libera_tst(&(*root)->right);

    if ((*root)->EndOfString){
        (*root)->EndOfString=0;
    }

}