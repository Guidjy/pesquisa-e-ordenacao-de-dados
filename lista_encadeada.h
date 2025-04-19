#ifndef Lista_encadeada_H_
#define Lista_encadeada_H_

#include <stdbool.h>

// estrutura de um nó da lista_encadeada
struct _noLista_encadeada
{
    void *dado;              // ponteiro para o dado armazenado no nó
    struct _noLista_encadeada *prox;  // ponteiro para o próximo nó da lista_encadeada
};
typedef struct _noLista_encadeada *NoLista_encadeada;


// estrutura do descritor da lista_encadeada
struct _Lista_encadeada
{
    int n_elem;    // número de elementos na lista_encadeada
    int tam_dado;  // tamanho (em bytes) do dado armazenado na lista_encadeada
    NoLista_encadeada pri;  // ponteiro para o primeiro nó da lista_encadeada
};

typedef struct _Lista_encadeada *Lista_encadeada;

// inicializa uma lista_encadeada de dados de tamanho "tam_dado"
Lista_encadeada lista_encadeada_cria(int tam_dado);

// retorna true se uma lista_encadeada estiver vazia, false caso contrário
bool lista_encadeada_vazia(Lista_encadeada self);

// retorna o número de elementos na lista_encadeada
int lista_encadeada_len(Lista_encadeada self);

// insere um elemento no início da lista_encadeada
// obs: o dado a ser inserido deve ser passado por referência
void lista_encadeada_insere(Lista_encadeada self, void *pdado);

// insere um elemento no índice pos da lista_encadeada
void lista_encadeada_insere_pos(Lista_encadeada self, void *pdado, int pos);

// remove o elemento no início da lista_encadeada
// copia o dado do elemento removido para o ponteiro passado
void lista_encadeada_remove(Lista_encadeada self, void *removido);

// remove o elemento no indice pos da lista_encadeada
// copia o dado do elemento removido para o ponteiro passado
void lista_encadeada_remove_pos(Lista_encadeada self, void *removido, int pos);

// organiza os elementos da lista_encadeada em ordem crescente
void lista_encadeada_sort(Lista_encadeada self);

// libera toda a memória alocada para uma lista_encadeada
void lista_encadeada_destroi(Lista_encadeada self);

// imprime uma lista_encadeada (apoio para "char", "str", "int" e "float")
void lista_encadeada_imprime(Lista_encadeada self, char *tipo);

#endif