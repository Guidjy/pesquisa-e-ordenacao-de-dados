#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <stdio.h>
#include "lista.h"
#include "sort.h"


int main() {
    srand(time(NULL));
    // cria uma nova lista
    Lista lista1 = lista_cria(20);
    lista_preenche(lista1, 50);
    lista_imprime(lista1);
    merge_sort(lista1, 0, lista1->n_elem-1);
    lista_imprime(lista1);
    lista_destroi(lista1);
    return 0;
}