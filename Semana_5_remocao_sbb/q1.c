#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0

typedef struct TipoAluno {
    char nome[30];
    int altura;
}TipoAluno;

typedef enum {
    Vertical, Horizontal
} Inclinacao;

typedef struct TipoNo *TipoApontador;

typedef struct TipoNo{
    TipoAluno *chave;
    TipoApontador esq,dir;
    Inclinacao BitE, BitD;
}TipoNo;

//Funções de inserção
void EE(TipoApontador *Ap);
void ED(TipoApontador *Ap);
void DD(TipoApontador *Ap);
void DE(TipoApontador *Ap);
void IInsere(TipoAluno *aluno, TipoApontador *Ap, Inclinacao *IAp, short *Fim);
void Insere(TipoAluno *aluno, TipoApontador *Ap);
//Funções de pesquisa
void BuscaOrdem(TipoApontador Ap_raiz, TipoApontador maior);
void Busca_Nome(TipoApontador* Ap_raiz,char chave[],float* altura);
TipoApontador BuscaMaior(TipoApontador Ap_raiz);
//Funções de remoção
void esqCurto(TipoApontador *Ap, short *Fim);
void dirCurto(TipoApontador *Ap, short *Fim);
void Antecessor(TipoApontador q, TipoApontador *r, short *Fim);
void IRetira(int x, TipoApontador *Ap, short *Fim);
void Retira(int x, TipoApontador *Ap);

int main(){

    TipoApontador raiz=NULL;
    int n,f;
    scanf("%d",&n);
    //Lê os dados e realiza a inserção dos alunos na árvore
    for (int i=0;i<n;i++){
        TipoAluno *aluno=(TipoAluno*)malloc(sizeof(TipoAluno));
        scanf("%s %d",aluno->nome,&aluno->altura);
        Insere(aluno,&raiz);
    }

    char key[30];
    int altura_chave;
    scanf("%d",&f);
    //Lê os nomes e realiza a remoção deles
    for (int j=0;j<f;j++){
        scanf("%s",key);
        //Como a árvore foi construída com base na altura e queremos encontrar um nome, realiza-se a busca da altura desse indivíduo percorrendo todos os nós da árvore até encontrá-la
        //Em seguida, a remoção desse elemento é feita utilizando a altura. obs: desconsiderando a existência de chaves repetidas!!
        Busca_Nome(&raiz,key,&altura_chave);
        Retira(altura_chave,&raiz);
    }
    //Auxilia na formatação da saída
    TipoApontador maior=BuscaMaior(raiz);
    //Imprime a nova listagem em ordem (com base na altura) após alterações realizadas
    BuscaOrdem(raiz,maior);
    return 0;
}

void EE(TipoApontador *Ap)
{ TipoApontador Ap1;
  Ap1 = (*Ap)->esq; (*Ap)->esq = Ap1->dir; Ap1->dir = *Ap;
  Ap1->BitE = Vertical; (*Ap)->BitE = Vertical; *Ap = Ap1;
}  

void ED(TipoApontador *Ap)
{ TipoApontador Ap1, Ap2;
  Ap1 = (*Ap)->esq; Ap2 = Ap1->dir; Ap1->BitD = Vertical;
  (*Ap)->BitE = Vertical; Ap1->dir = Ap2->esq; Ap2->esq = Ap1;
  (*Ap)->esq = Ap2->dir; Ap2->dir = *Ap; *Ap = Ap2;
}

void DD(TipoApontador *Ap){
  TipoApontador Ap1;
  Ap1 = (*Ap)->dir; (*Ap)->dir = Ap1->esq; Ap1->esq = *Ap;
  Ap1->BitD = Vertical; (*Ap)->BitD = Vertical; *Ap = Ap1;
}

void DE(TipoApontador *Ap)
{ TipoApontador Ap1, Ap2;
  Ap1 = (*Ap)->dir; Ap2 = Ap1->esq; Ap1->BitE = Vertical;
  (*Ap)->BitD = Vertical; Ap1->esq = Ap2->dir; Ap2->dir = Ap1;
  (*Ap)->dir = Ap2->esq; Ap2->esq = *Ap; *Ap = Ap2;
}

void IInsere(TipoAluno* aluno, TipoApontador *Ap, Inclinacao *IAp, short *Fim){ 
    if (*Ap == NULL) 
    { *Ap = (TipoApontador)malloc(sizeof(TipoNo));
      *IAp = Horizontal; (*Ap)->chave = aluno;
      (*Ap)->BitE = Vertical; (*Ap)->BitD = Vertical;
      (*Ap)->esq = NULL; (*Ap)->dir = NULL;
      *Fim = FALSE;
      return;
    }
    if (aluno->altura < (*Ap)->chave->altura) 
    { IInsere(aluno, &(*Ap)->esq, &(*Ap)->BitE, Fim);
      if (*Fim) return;
      if ((*Ap)->BitE != Horizontal) 
      { *Fim = TRUE; return; }
      if ((*Ap)->esq->BitE == Horizontal) 
      { EE(Ap); *IAp = Horizontal; return; }
      if ((*Ap)->esq->BitD == Horizontal) 
      { ED(Ap); *IAp = Horizontal; }
      return;
    }
    if (aluno->altura<= (*Ap)->chave->altura) 
    { printf("Erro: chave ja esta na arvore\n");
      *Fim = TRUE;
      return;
    }
    IInsere(aluno, &(*Ap)->dir, &(*Ap)->BitD, Fim);
    if (*Fim) return;
    if ((*Ap)->BitD != Horizontal) 
    { *Fim = TRUE;  return; }
    if ((*Ap)->dir->BitD == Horizontal) 
    { DD(Ap); *IAp = Horizontal; return;}
    if ((*Ap)->dir->BitE == Horizontal) 
    { DE(Ap); *IAp = Horizontal; }
}  

void Insere(TipoAluno *aluno, TipoApontador *Ap)
{ short Fim;
  Inclinacao IAp;
  IInsere(aluno, Ap, &IAp, &Fim);
} 

void BuscaOrdem(TipoApontador Ap_raiz,TipoApontador maior){

    if (Ap_raiz==NULL){
        return;
    }

    BuscaOrdem(Ap_raiz->esq,maior);

    if (Ap_raiz==maior){
        printf("%s\n",Ap_raiz->chave->nome);
    }
    else{
      printf("%s - ",Ap_raiz->chave->nome);
    }

    BuscaOrdem(Ap_raiz->dir,maior);

    return;
}

TipoApontador BuscaMaior(TipoApontador Ap_raiz){ 

  if (Ap_raiz==NULL){
    return NULL;
  }
  if(Ap_raiz->dir==NULL){
    return Ap_raiz;
  }
  return BuscaMaior(Ap_raiz->dir);
}

void esqCurto(TipoApontador *Ap, short *Fim)
{ 
  TipoApontador Ap1;
  if ((*Ap)->BitE == Horizontal) 
  { (*Ap)->BitE = Vertical; *Fim = TRUE; return; }
  if ((*Ap)->BitD == Horizontal) 
  { Ap1 = (*Ap)->dir; (*Ap)->dir = Ap1->esq; Ap1->esq = *Ap; *Ap = Ap1;
    if ((*Ap)->esq->dir->BitE == Horizontal) 
    { DE(&(*Ap)->esq); (*Ap)->BitE = Horizontal;}
    else if ((*Ap)->esq->dir->BitD == Horizontal) 
         { DD(&(*Ap)->esq); (*Ap)->BitE = Horizontal; }
    *Fim = TRUE;
    return;
  }
  (*Ap)->BitD = Horizontal;
  if ((*Ap)->dir->BitE == Horizontal) { DE(Ap); *Fim = TRUE; return; }
  if ((*Ap)->dir->BitD == Horizontal) {  DD(Ap); *Fim = TRUE; }
} 

void dirCurto(TipoApontador *Ap, short *Fim)
{ 
  TipoApontador Ap1;
  if ((*Ap)->BitD == Horizontal)
  { (*Ap)->BitD = Vertical; *Fim = TRUE; return; }
  if ((*Ap)->BitE == Horizontal) 
  { Ap1 = (*Ap)->esq; (*Ap)->esq = Ap1->dir; Ap1->dir = *Ap; *Ap = Ap1;
    if ((*Ap)->dir->esq->BitD == Horizontal) 
    { ED(&(*Ap)->dir); (*Ap)->BitD = Horizontal; } 
    else if ((*Ap)->dir->esq->BitE == Horizontal) 
         { EE(&(*Ap)->dir); (*Ap)->BitD = Horizontal;}
    *Fim = TRUE;
    return;
  }
  (*Ap)->BitE = Horizontal;
  if ((*Ap)->esq->BitD == Horizontal) { ED(Ap); *Fim = TRUE; return; }
  if ((*Ap)->esq->BitE == Horizontal) { EE(Ap); *Fim = TRUE; }
}  

void Antecessor(TipoApontador q, TipoApontador *r, short *Fim)
{ if ((*r)->dir != NULL) 
  { Antecessor(q, &(*r)->dir, Fim);
    if (!*Fim) dirCurto(r, Fim);
    return;
  }
  q->chave = (*r)->chave; q = *r; *r = (*r)->esq; free(q);
  if (*r != NULL) *Fim = TRUE;
}

void IRetira(int x, TipoApontador *Ap, short *Fim)
{ TipoNo *Aux;
  if (*Ap == NULL) 
  { printf("Chave nao esta na arvore\n"); *Fim = TRUE; return; }
  if (x < (*Ap)->chave->altura) 
  { IRetira(x, &(*Ap)->esq, Fim);
    if (!*Fim) esqCurto(Ap, Fim);
    return;
  }
  if (x > (*Ap)->chave->altura) 
  { IRetira(x, &(*Ap)->dir, Fim);
    if (!*Fim) dirCurto(Ap, Fim);
    return;
  }
  *Fim = FALSE; Aux = *Ap;
  if (Aux->dir == NULL) 
  { *Ap = Aux->esq;  free(Aux);
    if (*Ap != NULL) *Fim = TRUE;
    return;
  }
  if (Aux->esq == NULL) 
  { *Ap = Aux->dir; free(Aux);
    if (*Ap != NULL) *Fim = TRUE;
    return;
  }
  Antecessor(Aux, &Aux->esq, Fim);
  if (!*Fim) esqCurto(Ap, Fim); 
} 

void Retira(int x, TipoApontador *Ap)
{ short Fim;
  IRetira(x, Ap, &Fim);
} 

void Busca_Nome(TipoApontador* Ap_raiz,char chave[],float* altura){
    
    if(*Ap_raiz==NULL){
      printf("não encontrado");
      return;
    }

    if (strcmp((*Ap_raiz)->chave->nome,chave)==0){
      *altura=(*Ap_raiz)->chave->altura;
      return;
    }

    if ((*Ap_raiz)->dir!=NULL){
      Busca_Nome(&(*Ap_raiz)->dir,chave,altura);
    }
    if((*Ap_raiz)->esq!=NULL){
      Busca_Nome(&(*Ap_raiz)->esq,chave,altura);
    }
}