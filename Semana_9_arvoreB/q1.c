#include<stdlib.h>
#include<stdio.h>
#define M 2
#define MM  (M * 2)
#define FALSE 0
#define TRUE  1

typedef long TipoChave;
typedef struct TipoRegistro {
  TipoChave Chave;
} TipoRegistro;
typedef struct TipoPagina* TipoApontador;
typedef struct TipoPagina {
  short n;
  TipoRegistro r[MM];
  TipoApontador p[MM + 1];
} TipoPagina;

void Inicializa(TipoApontador *Dicionario)
{  *Dicionario = NULL; }

void InsereNaPagina(TipoApontador Ap, 
                    TipoRegistro Reg, TipoApontador ApDir)
{ short NaoAchouPosicao;
  int k;
  k = Ap->n;  NaoAchouPosicao = (k > 0);
  while (NaoAchouPosicao) 
    { if (Reg.Chave >= Ap->r[k-1].Chave) 
      { NaoAchouPosicao = FALSE;
        break;
      }
      Ap->r[k] = Ap->r[k-1];
      Ap->p[k+1] = Ap->p[k];
      k--;
      if (k < 1) NaoAchouPosicao = FALSE;
    }
  Ap->r[k] = Reg; 
  Ap->p[k+1] = ApDir;
  Ap->n++;
} 

void Ins(TipoRegistro Reg /*REGISTRO A INSERIR*/, TipoApontador Ap /*PONTEIRO PARA PAG ATUAL*/, short *Cresceu /*FLAG*/, 
         TipoRegistro *RegRetorno /*REGISTRO QUE IRA SUBIR NO SPLIT*/,  TipoApontador *ApRetorno /*APONTA PARA NOVA PAGINA*/)
{ long i = 1; long j;
  TipoApontador ApTemp;
  if (Ap == NULL) // INSERÇÃO EM SUBÁRVORE VAZIA
  { *Cresceu = TRUE; (*RegRetorno) = Reg; (*ApRetorno) = NULL;
    return;
  }
  while (i < Ap->n && Reg.Chave > Ap->r[i-1].Chave)  i++; //BUSCANDO A POSIÇÃO PARA INSERIR
  if (Reg.Chave == Ap->r[i-1].Chave) 
  { printf(" Erro: Registro ja esta presente\n"); *Cresceu = FALSE; //NÃO PERMITE A INSERÇÃO DE CHAVES REPETIDAS
    return;
  }
  if (Reg.Chave < Ap->r[i-1].Chave) i--;
  Ins(Reg, Ap->p[i], Cresceu, RegRetorno, ApRetorno); //CHAMA RECURSIVAMENTE PARA AP->P[I]
  if (!*Cresceu) return; //SE A ÁRVORE NÃO CRESCEU EM ALTURA, ENECERRA A FUNÇÃO
  if (Ap->n < MM)   // SE A PAG ATUAL TEM ESPAÇO, INSERE O REGISTRO
    { InsereNaPagina(Ap, *RegRetorno, *ApRetorno);
      *Cresceu = FALSE;
      return;
    }

    //SPLIT

    printf("Iniciando split\n"); 
    //INDICA A NECESSIDADE DE REALIZAR UM SPLIT PARA INSERIR A CHAVE, 
    //QUANDO ESSA MENSAGEM É PRINTADA MULTIPLAS VEZES EM SEQUENCIA SIGNIFICA QUE FOI NECESSARIO 
    //REALIZAR SPLITS EM CADEIA POIS A FUNCAO FOI CHAMADA RECURSIVAMENTE


  ApTemp = (TipoApontador)malloc(sizeof(TipoPagina));
  ApTemp->n = 0;  ApTemp->p[0] = NULL; 
  if (i < M + 1)  //INSERE NA METADE ESQ
  { InsereNaPagina(ApTemp, Ap->r[MM-1], Ap->p[MM]);
    Ap->n--;
    InsereNaPagina(Ap, *RegRetorno, *ApRetorno);
  } 
  else InsereNaPagina(ApTemp, *RegRetorno, *ApRetorno); //INSERE NA METADE DIR
  for (j = M + 2; j <= MM; j++) 
    InsereNaPagina(ApTemp, Ap->r[j-1], Ap->p[j]); //INSERE OS ELEMENTOS QUE SOBRARAM NA NOVA PAG
  *RegRetorno = Ap->r[M];  *ApRetorno = ApTemp; //SOBE A CHAVE DO MEIO
}

void Insere(TipoRegistro Reg/*REG A SER INSERIDO*/, TipoApontador *Ap/*APONTA PARA RAIZ DA ARVORE*/)
{ short Cresceu;
  TipoRegistro RegRetorno;
  TipoPagina *ApRetorno, *ApTemp;
  Ins(Reg, *Ap, &Cresceu, &RegRetorno, &ApRetorno);
  if (Cresceu) //CRIA UMA NOVA RAIZ E AUMENTA UM NÍVEL 
  { ApTemp = (TipoPagina *)malloc(sizeof(TipoPagina));
    ApTemp->n = 1; 
    ApTemp->r[0] = RegRetorno;
    ApTemp->p[1] = ApRetorno;
    ApTemp->p[0] = *Ap;  *Ap = ApTemp;
  }
}

void ImprimeI(TipoApontador p, int nivel)
{ long i;
  if (p == NULL) return;
  printf("Nivel %d : ", nivel);
  for (i = 0; i < p->n; i++)
    printf("%ld ",(long)p->r[i].Chave);
  putchar('\n');
  nivel++;
  for (i = 0; i <= p->n; i++)
    ImprimeI(p->p[i], nivel);
} 

void Imprime(TipoApontador p)
{ int  n = 0; ImprimeI(p, n); } 

int main(int argc, char *argv[])
{ TipoRegistro x;
  TipoPagina *D;
  Inicializa(&D);

  int elementos[] = {20, 10, 40, 50, 30, 55, 3, 11, 4, 28, 36, 33, 52, 17, 25, 13, 45, 9, 43, 8, 48};

  int n = sizeof(elementos) / sizeof(elementos[0]);

  for (int i = 0; i < n; i++) { //CADA VALOR CONTIDO NA LISTA "ELEMENTOS É INSERIDO NA ÁRVORE"
    x.Chave = elementos[i];
    printf(" \n");
    printf("inserindo %ld\n", x.Chave);
    Insere(x, &D);
    Imprime(D); //APOS SER FEITA A INSERÇÃO DA CHAVE, É PRINTADO O ESTADO ATUAL DE TODOS OS NIVEIS
    //ASSIM É POSSIVEL ACOMPANHAR A CONFIGURACAO DA ARVORE A CADA INSERCAO, ALEM DE QUE TAMBÉM É MOSTRADO AS SITUAÇÕES ONDE FOI NECESSÁRIO A REALIZAÇÃO DE "SPLITS"
  }

  return 0;
}