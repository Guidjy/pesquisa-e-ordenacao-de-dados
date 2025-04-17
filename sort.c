#include "lista.h"
#include "sort.h"


void bubble_sort(Lista lista) {
    for (int i = 1; i < lista->n_elem; i++) {
        for (int j = 0; j < lista->n_elem - 1; j++) {
            if (lista->vetor[j] > lista->vetor[j+1]) {
                lista_swap(lista, j, j+1);
            }
        }
    }
}


void insertion_sort(Lista lista) {
    // percorre a parte da direita, começando do 1 pois o elemento em 0 está na parte da esquerda (ordenada)
    for (int i = 1; i < lista->n_elem; i++) {
        int pivo = lista->vetor[i];
        int j = i - 1;  // índice do elemento mais a direita da parte da direita
        // percorre a parte esquerda, deslocando cada elemento um índice para a direita, até achar um elemento menor que o pivo
        while (j >= 0 && lista->vetor[j] > pivo) {
            lista->vetor[j+1] = lista->vetor[j];
            j--;
        }
        // insere o pivo na parte da direita
        lista->vetor[j+1] = pivo;
    }
}


void selection_sort(Lista lista) {
    // até n_elem - 1 porque en n - 1 iterações está ordenado
    for (int i = 0; i < lista->n_elem - 1; i++) {
        // assumimos que o mínimo é o primeiro elemento
        int min = i;
        for (int j = i + 1; j < lista->n_elem; j++) {
            if (lista->vetor[j] < lista->vetor[min]) {
                min = j;
            }
        }
        lista_swap(lista, i, min);
    }
}


void shell_sort(Lista lista) {
    // Calcula o maior intervalo h da sequência de Knuth (1, 4, 13, 40, ...)
    int h = 1;
    while (h < lista->n_elem) {
        h = 3 * h + 1;
    }

    // executa o shellsort usando h decrescentes
    while (h > 1) {
        h /= 3;

        for (int i = h; i < lista->n_elem; i++) {
            int pivo = lista->vetor[i];
            int j = i - h;
            while (j >= 0 && lista->vetor[j] > pivo) {
                lista->vetor[j+h] = lista->vetor[j];
                j -= h;
            }
            lista->vetor[j+h] = pivo;
        }
    }
}