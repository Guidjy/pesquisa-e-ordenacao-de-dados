#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <stdio.h>
#include "lista.h"
#include "sort.h"
#include "heap.h"


int main() {
    srand(time(NULL));
    // cria uma nova lista
    Lista lista1 = lista_cria(20);
    lista_preenche(lista1, 50);
    lista_imprime(lista1);
    quick_sort(lista1, 0, lista1->n_elem-1);
    lista_imprime(lista1);

    Heap heap1 = heap_cria(20);
    for (int i = 0; i < 20; i++) {
        heap_insere(heap1, rand() % 50);
    }
    heap_imprime(heap1);
    while(!heap_vazio(heap1)) {
        int removido = heap_remove_min(heap1);
        printf("%d, ", removido);
    }
    printf("\n");


    lista_destroi(lista1);
    heap_destroi(heap1);
    return 0;
}