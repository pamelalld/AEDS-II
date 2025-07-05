//receber um valor x que indica a quantidade de alunos recebidos
//organizar os alunos em dois carros cada um contendo no maximo 3 alunos
//mostrar a distribuicao entre os carros
//pesquisar a ocorrência de nomes
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define VAZIO  "!!!!!!!!!!"
#define RETIRADO  "**********"
#define M  6
#define N  11   

typedef unsigned int TipoApontador;
typedef char TipoChave[N];
typedef unsigned TipoPesos[N];
typedef struct TipoItem {
  
  TipoChave Chave;
} TipoItem;
typedef unsigned int TipoIndice;
typedef TipoItem TipoDicionario[M];
TipoDicionario Tabela;
TipoPesos p;
TipoItem Elemento;
int j, i;

void GeraPesos(TipoPesos p)
{  
  int i; struct timeval semente;
  
  gettimeofday(&semente,NULL); 
  srand((int)(semente.tv_sec + 1000000 * semente.tv_usec));
  for (i = 0; i < N; i++)
     p[i] = 1 + (int) (10000.0 * rand()/(RAND_MAX + 1.0));
}

TipoIndice h(TipoChave Chave, TipoPesos p)
{ int i; unsigned int Soma = 0; int comp = strlen(Chave);
  for (i = 0; i < comp; i++)
    Soma += (unsigned int)Chave[i] * p[i];
  return (Soma % M);
}

void Inicializa(TipoDicionario T)
{ int i;
 for (i = 0; i < M; i++) memcpy(T[i].Chave, VAZIO, N);
} 

TipoApontador Pesquisa(TipoChave Ch, TipoPesos p, TipoDicionario T)
{ unsigned int  i = 0; unsigned int  Inicial;
  Inicial = h(Ch, p);
  while (strcmp(T[(Inicial + i) % M].Chave,VAZIO) != 0 &&
         strcmp (T[(Inicial + i) % M].Chave, Ch) != 0 && i < M) 
    i++;
  if (strcmp( T[(Inicial + i) % M].Chave, Ch) == 0)  
  return ((Inicial + i) % M);
  else return M; 
} 

void Insere(TipoItem x, TipoPesos p, TipoDicionario T)
{ unsigned int i = 0; unsigned int Inicial;
  if (Pesquisa(x.Chave, p, T) < M) 
  { printf("Elemento ja esta presente\n"); return; }
  Inicial = h(x.Chave, p);
  while (strcmp(T[(Inicial + i) % M].Chave,VAZIO) != 0 &&
         strcmp(T[(Inicial + i) % M].Chave, RETIRADO) != 0 && i < M) 
     i++;
  if (i < M) 
  { strcpy(T[(Inicial + i) % M].Chave, x.Chave);
      
  }
  else printf(" Tabela cheia\n");
} 

void Distribui_alunos(TipoDicionario tabela)
{ int  i, j=0, k=0;
  char carro_um[3][N];
  char carro_dois[3][N];
  for (i = 0; i < M; i++) 
  { //No carro 1 estarão os nomes de índices pares e no carro dois os índices ímpares
    if (strcmp(tabela[i].Chave, "!!!!!!!!!!") != 0) {
      if (i%2==0 && j<3) {
          strcpy(carro_um[j], tabela[i].Chave);
          j++;
      } else if (i%2!=0 && k<3) {
          strcpy(carro_dois[k], tabela[i].Chave);
          k++;
      }
    }
  }   
    printf("Primeiro carro:");
    for (i = 0; i < j; i++) {
        printf(" %s -", carro_um[i]);
    }
    printf("\n");
    printf("Segundo carro:");
    for (i = 0; i < k; i++) {
        printf(" %s -", carro_dois[i]);
    }
    printf("\n");
  }

void LerPalavra(char *p, int Tam)
{ char c; int i, j;
  fflush(stdin); j=0;
  while (((c=getchar())!='\n') && (j < (Tam - 1))) p[j++]= c;
  p[j] = '\0';
  while(c != '\n') c = getchar();

  for(i = j - 1;(i >= 0 && p[i] == ' ');i--) p[i] = '\0';
}

int main(int argc, char *argv[])
{ 
  int loops;

  Inicializa(Tabela);

  GeraPesos(p);

  scanf("%d",&loops);
  while (getchar() != '\n');

  for (int k=0;k<loops;k++){
    LerPalavra(Elemento.Chave, N);
    Insere(Elemento, p, Tabela);
  }

  Distribui_alunos(Tabela);

  LerPalavra(Elemento.Chave, N);
  while (strcmp(Elemento.Chave, "0") != 0) 
    { i = Pesquisa(Elemento.Chave, p, Tabela);
      if (i < M) printf("Aluno Confirmado \n");
      else printf("Aluno Não Confirmado \n");
      LerPalavra(Elemento.Chave, N);
    }

  return 0;
}  


