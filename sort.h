#ifndef SORT_H
#define SORT_H

#include "lista.h"

// médio: O(N²) - melhor: O(n) - pior: O(n²)
void bubble_sort(Lista lista);

// médio: O(N²) - melhor: O(n) - pior: O(n²)
void insertion_sort(Lista lista);

// O(n²)
void selection_sort(Lista lista);

void shell_sort(Lista lista);

#endif  