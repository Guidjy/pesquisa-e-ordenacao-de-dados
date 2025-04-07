#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>

typedef struct _lista *Lista;

// cria uma lista que suporta "tamanho" elementos
Lista lista_cria(int tamanho);

// libera tgoda a memória alocada para uma lista
void lista_destroi(Lista lista);

// retorna true se a lista estiver cheia
bool lista_cheia(Lista lista);

// insere um inteiro na lista
void lista_insere(Lista lista, int num);

// preenche a lista com valores aleatórios em um intervalo
void lista_preenche(Lista lista, int intervalo);

// imprime os elementos de uma Lista
void lista_imprime(Lista lista);

#endif