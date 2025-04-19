#include <stdlib.h>
#include "sort.h"
#include "lista.h"
#include "heap.h"
#include "lista_encadeada.h"


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


// retorna um índice j, no qual será colocado o pivô, tal que:
//     > lista[inicio] ... lista[j-1] <= lista[j]
//     > lista[j+1] ... lista[fim] > lista[j]
// O(n)
static int particao(Lista lista, int inicio, int fim) {
    int pivo = lista->vetor[inicio];
    int i = inicio + 1;
    int j = fim;

    // procedimentos são repetidos até que i > j
    while (i <= j) {
        // i avança até encontrar um elemento maior que o pivô
        while (i <= j && lista->vetor[i] <= pivo) {
            i++;
        }
        // j recua até encontrar um elemento menor ou igual ao pivô
        while (lista->vetor[j] > pivo) {
            j--;
        }
        // troca os elementos em i e j
        if (i <= j) {
            lista_swap(lista, i, j);
            i = i + 1;
            j = j - 1;
        }
    }

    lista_swap(lista, inicio, j);
    return j;
}


void quick_sort(Lista lista, int inicio, int fim) {
    if (inicio < fim) {
        int j = particao(lista, inicio, fim);
        // chama quicksort nas partições esquerda e direita
        quick_sort(lista, inicio, j - 1);
        quick_sort(lista, j + 1, fim);
    }
}


void heap_sort(Lista lista) {
    // cria um heap binário
    Heap heap = heap_cria(lista->n_elem);
    if (heap == NULL) return;

    // insere todos os elementos da lista no heap
    for (int i = 0; i < lista->n_elem; i++) {
        heap_insere(heap, lista->vetor[i]);
    }

    // remove todos os elementos do heap e os inserem de volta na lista
    for (int i = 0; i < lista->n_elem; i++) {
        lista->vetor[i] = heap_remove_min(heap);
    }

    heap_destroi(heap);
}


void counting_sort(Lista lista) {
    // descobre o limite superior do intervalo de números da lista
    int lim_sup = lista_max(lista);
    // inicializa o vetor de número de instâncias de cada elemento na lista
    int c[lim_sup+1];
    for (int i = 0; i < lim_sup+1; i++) {
        c[i] = 0;
    }
    // percorre a lista para contar o número de instâncias de cada elemento na lista
    for (int i = 0; i < lista->n_elem; i++) {
        c[ lista->vetor[i] ]++;
    }
    // realiza a soma acumulado do vetor de n_instâncias
    for (int i = 1; i <= lim_sup; i++) {
        c[i] += c[i-1];
    }
    // ordenação da lista
    int aux[lista->cap];
    for (int i = lista->n_elem - 1; i >= 0; i--) {
        c[lista->vetor[i]]--;
        aux[c[lista->vetor[i]]] = lista->vetor[i];  // rasclart 0-0. pag 48
    }
    // copia a lista auxiliar para a original
    for (int i = 0; i < lista->n_elem; i++) {
        lista->vetor[i] = aux[i];
    }
}


void bucket_sort(Lista lista) {
    // a ideia do método é dividir o intervalo que vai de 0 - k em n subintervalos de mesmo tamanho.
    // cada subintervalo estará associado a uma lista encadeada que irá conter os elementos da
    // lista original que pertencem àquele subintervalo. Em seguida, ordenamos as listas encadeadas
    // usando um método de ordenação qualquer (de preferência estável).

    // bucket: vetor de listas encadeadas. Se k é o maior elemento da lista,
    // cada posição do bucket apontará para uma lista na qual serão inseridos os elementos
    // da lista que pertencem ao intervalo [i*(k+1)/n, (i+1)*(k=1)/n]
    Lista_encadeada bucket[lista->n_elem];
    for (int i = 0; i < lista->n_elem; i++) {
        bucket[i] = lista_encadeada_cria(sizeof(int));
    }
    
    // construindo as listas encadeadas
    int k = lista_max(lista);
    for (int i = lista->n_elem - 1; i >= 0; i--) {
        // 0-0: ta uma bagunça do caraleo essa implementação de lista encadeada
        int num = lista->vetor[i];
        lista_encadeada_insere(bucket[lista->vetor[i] * lista->n_elem / (k + 1)], &num);
    }

    // ordenando e concatenando as listas encadeadas
    int j = 0;
    for (int i = 0; i < lista->n_elem; i++) {
        // ordena a lista em bucket[i]
        lista_encadeada_sort(bucket[i]);
        void *removido = malloc(sizeof(int));
        while (!lista_encadeada_vazia(bucket[i])) {
            lista_encadeada_remove(bucket[i], removido);
            lista->vetor[j] = *(int*) removido;
            j++;
        }
        free(removido);
        lista_encadeada_destroi(bucket[i]);
    }
}