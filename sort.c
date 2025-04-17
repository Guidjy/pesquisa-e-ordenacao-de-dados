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

        // percorre a lista a partir de h
        for (int i = h; i < lista->n_elem; i++) {
            int pivo = lista->vetor[i];
            int j = i - h;
            // inserção adaptada para h-elementos
            while (j >= 0 && lista->vetor[j] > pivo) {
                lista->vetor[j+h] = lista->vetor[j];
                j -= h;
            }
            lista->vetor[j+h] = pivo;
        }
    }
}


static void merge(Lista lista, int inicio, int meio, int fim) {
    int i = inicio;
    int j = meio + 1;
    int k = 0;
    int aux[fim - inicio + 1];  // tamanho correto do subvetor

    // mistura os dois subvetores ordenados
    while (i <= meio && j <= fim) {
        if (lista->vetor[i] <= lista->vetor[j]) {
            aux[k++] = lista->vetor[i++];
        } else {
            aux[k++] = lista->vetor[j++];
        }
    }

    // copia o que sobrou do primeiro subvetor (se sobrou)
    while (i <= meio) {
        aux[k++] = lista->vetor[i++];
    }

    // copia o que sobrou do segundo subvetor (se sobrou)
    while (j <= fim) {
        aux[k++] = lista->vetor[j++];
    }

    // copia de volta para o vetor original
    for (i = 0; i < k; i++) {
        lista->vetor[inicio + i] = aux[i];
    }
}



void merge_sort(Lista lista, int inicio, int fim) {
    if (inicio < fim) {
        int meio = (inicio + fim) / 2;

        merge_sort(lista, inicio, meio);
        merge_sort(lista, meio + 1, fim);
        
        merge(lista, inicio, meio, fim);
    }
}
