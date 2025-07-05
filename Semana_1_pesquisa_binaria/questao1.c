#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct livro{ //estrutura livro que guarda a etiqueta, nome do livro e a posição que ocupa
    int etiqueta;
    char nome[50];
    int posicao;
}livro;

void insertion(livro livros[], int n) { //algoritmo de ordenação para os livros
    for (int i = 1; i < n; i++) {
        livro aux= livros[i];
        int j = i - 1;

        while (j >= 0 && livros[j].etiqueta > aux.etiqueta) {
            livros[j + 1] = livros[j];
            j--;
        }
        livros[j + 1] = aux;
    }
}

int busca_binaria(int valor, livro livros[],int esq, int dir) { //algoritmo de busca binaria a partir da etiqueta
    int meio;
    
    while (esq <= dir) {
        meio = (esq + dir) / 2;
        
        if (livros[meio].etiqueta == valor) {
            return meio; 
        } 
        
        else if (livros[meio].etiqueta < valor) {
            esq = meio + 1; 
        } 
        
        else {
            dir = meio - 1; 
        }
    }
    return -1;
}

int main (){

    int n;
    scanf("%d",&n);
    livro livros[n];

    for(int i=0;i<n;i++){ // faz a leitura dos dados ref aos n livros e armazena na posição "i" de uma lista linear do tipo livro
        scanf("%d ", &livros[i].etiqueta);
        fgets(livros[i].nome, 50, stdin);
        livros[i].nome[strcspn(livros[i].nome, "\n")] = 0;
        livros[i].posicao = i + 1; //incrementa a posicao de acordo com cada livro informado
    }

    insertion(livros,n);

    int chave;
    scanf("%d",&chave);

    int posicao=busca_binaria(chave,livros,0,n-1);

    printf("Posição: %d, Livro: %s",livros[posicao].posicao,livros[posicao].nome);

    return 0;
}