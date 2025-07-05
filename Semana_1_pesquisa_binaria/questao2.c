#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct mod{
    char nome[50];
    int posicao;
}mod;

void insertion(mod lista_pacotes[], int n) { //ordena uma lista linear tipo mod com base no nome(string)
    for (int i = 1; i < n; i++) {
        mod aux = lista_pacotes[i];
        int j = i - 1;
        
        while (j >= 0 && strcmp(lista_pacotes[j].nome, aux.nome) > 0) {
            lista_pacotes[j + 1] = lista_pacotes[j];  
            j--;
        }
        lista_pacotes[j + 1] = aux;  
    }
}

int busca_binaria(char* valor, mod lista[], int esq, int dir) { //algoritmo de busca binaria a partir de uma string
    int meio;

    while (esq <= dir) {
        meio = (esq + dir) / 2;
        
        int cmp = strcmp(lista[meio].nome, valor);

        if (cmp == 0) {  
            return meio;
        } 
        else if (cmp < 0) {  
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
    getchar();
    mod *lista_pacotes = (mod *)malloc(n * sizeof(mod));

    for(int i=0;i<n;i++){ // faz a leitura dos dados ref aos n pacotes e armazena na posição "i" de uma lista linear do tipo mod
        fgets(lista_pacotes[i].nome, 50, stdin);
        lista_pacotes[i].nome[strcspn(lista_pacotes[i].nome, "\n")] = 0;
        lista_pacotes[i].posicao = i + 1; //incrementa a posicao de acordo com cada pacote de modificações informado
    }
    
    insertion(lista_pacotes,n);

    char chave[50];
    scanf("%s",chave);

    int res=  busca_binaria(chave,lista_pacotes,0,n-1);//encontra a posicao do elemento "chave" em lista_pacotes

    printf("Posição: %d\n",lista_pacotes[res].posicao);

    free(lista_pacotes);

        return 0;
    }

    


