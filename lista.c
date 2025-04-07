#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "lista.h"


struct _lista {
    int cap;         // capacidade máxima da lista
    int n_elem;      // número de elementos na lista
    int *elementos;  // lista de inteiros
};
// typedef struct lista *Lista; >>> lista.h


Lista lista_cria(int tamanho) {
    // aloca memória para a estrutura de uma nova lista
    Lista nova = (Lista) malloc(sizeof(struct _lista));
    if (nova == NULL) {
        printf("Erro na alocação de memória para a struct da lista\n");
        return NULL;
    }
    nova->cap = tamanho;
    nova->n_elem = 0;
    // aloca memória para os elementos da lista
    nova->elementos = (int*) malloc(sizeof(int) * tamanho);
    if (nova->elementos == NULL) {
        printf("Erro na alocação de memória para os elementos da lista");
        free(nova);
        return NULL;
    }
    return nova;
}


void lista_destroi(Lista lista) {
    free(lista->elementos);
    free(lista);
}


bool lista_cheia(Lista lista) {
    return lista->n_elem == lista->cap;
}


void lista_insere(Lista lista, int num) {
    if (lista_cheia(lista)) {
        printf("Lista cheia. Não se pode inserir elementos\n");
        return;
    }
    lista->elementos[lista->n_elem] = num;
    lista->n_elem++;
}


void lista_preenche(Lista lista, int intervalo) {
    for (int i = 0; i < lista->cap; i++) {
        lista->elementos[i] = rand() % intervalo;
    }
    lista->n_elem = lista->cap;
}


void lista_imprime(Lista lista) {
    printf("[");
    for (int i = 0; i < lista->n_elem - 1; i++) {
        printf("%d, ", lista->elementos[i]);
    }
    printf("%d]\n", lista->elementos[lista->n_elem - 1]);
}