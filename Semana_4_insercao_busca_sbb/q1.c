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


void EE(TipoApontador *Ap);
void ED(TipoApontador *Ap);
void DD(TipoApontador *Ap);
void DE(TipoApontador *Ap);
void IInsere(TipoAluno *aluno, TipoApontador *Ap, Inclinacao *IAp, short *Fim);
void Insere(TipoAluno *aluno, TipoApontador *Ap);
void BuscaOrdem(TipoApontador Ap_raiz, TipoApontador maior);
TipoApontador BuscaMaior(TipoApontador Ap_raiz);
int alturaSBB(TipoApontador* no);



int main(){

    TipoApontador raiz=NULL;
    int n;
    scanf("%d",&n);
    
    for (int i=0;i<n;i++){
        TipoAluno *aluno=(TipoAluno*)malloc(sizeof(TipoAluno));
        scanf("%s %d",aluno->nome,&aluno->altura);
        Insere(aluno,&raiz);
    }

    int x= alturaSBB(&raiz);

    printf("%d",x);
    //TipoApontador maior=BuscaMaior(raiz);
    //BuscaOrdem(raiz,maior);
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

int alturaSBB(TipoApontador* no) {
    if ((*no) == NULL) {
        return -1;
    }

    int he = alturaSBB(&(*no)->esq);
    int hd = alturaSBB(&(*no)->dir);

    // Se a ligação é vertical, soma 1. Se for horizontal, mantém.
    if ((*no)->BitE == 0) {
        he += 1;
    }

    if ((*no)->BitD == 0) {
        hd += 1;
    }
    if(he<hd){
      return hd;
    }else{
      return he;
    }
}

