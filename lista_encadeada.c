#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_encadeada.h"


// inicializa uma lista_encadeada de dados de tamanho "tam_dado"
Lista_encadeada lista_encadeada_cria(int tam_dado)
{
    // aloca memória para o descritor da lista_encadeada
    Lista_encadeada novaLista_encadeada = (Lista_encadeada) malloc(sizeof(struct _Lista_encadeada));
    if (novaLista_encadeada == NULL)
    {
        printf("Erro na alocação de memória para o descritor da lista_encadeada\n");
        return NULL;
    }
    // inicializa os descritores da lista_encadeada
    novaLista_encadeada->n_elem = 0;
    novaLista_encadeada->tam_dado = tam_dado;
    novaLista_encadeada->pri = NULL;

    return novaLista_encadeada;
}


// retorna true se uma lista_encadeada estiver vazia, false caso contrário
bool lista_encadeada_vazia(Lista_encadeada self)
{
    return self->n_elem == 0;
}


// retorna o número de elementos na lista_encadeada
int lista_encadeada_len(Lista_encadeada self)
{
    return self->n_elem;
}


// cria um nó para a lista_encadeada
static NoLista_encadeada cria_no(void *pdado, int tam_dado)
{
    // aloca memória para um novo nó
    NoLista_encadeada novo_no = (NoLista_encadeada) malloc(sizeof(struct _noLista_encadeada));
    if (novo_no == NULL)
    {
        printf("Erro na alocação de memória para nó da lista_encadeada\n");
        return NULL;
    }
    novo_no->dado = malloc(tam_dado);
    if (novo_no->dado == NULL)
    {
        printf("Erro na alocação de memória para nó da lista_encadeada\n");
        free(novo_no);
        return NULL;
    }

    // copia o dado em *pdado para o nó
    memmove(novo_no->dado, pdado, tam_dado);
    novo_no->prox == NULL;

    return novo_no;
}


// insere um elemento no início da lista_encadeada
void lista_encadeada_insere(Lista_encadeada self, void *pdado)
{
    // verifica se o dado passado é válido
    if (pdado == NULL)
    {
        printf("Dado inválido para inserção\n");
        return;
    }

    // cria um novo nó e encadea-o na lista_encadeada
    NoLista_encadeada novo_no = cria_no(pdado, self->tam_dado);
    if (novo_no == NULL) return;
    novo_no->prox = self->pri;
    self->pri = novo_no;

    // incrementa o número de elementos da lista_encadeada
    self->n_elem++;
}


// insere um elemento no índice pos da lista_encadeada
void lista_encadeada_insere_pos(Lista_encadeada self, void* pdado, int pos)
{
    // verifica se o dado passado é válido
    if (pdado == NULL)
    {
        printf("Dado inválido para inserção\n");
        return;
    }

    // verifica se o índice passado é válido
    if (pos >= self->n_elem)
    {
        printf("índice de inserção inválido\n");
        return;
    }

    // apoio para índice negativo (-1 = último índice)
    if (pos < 0)
    {
        pos += self->n_elem;
    }

    // percorre a lista_encadeada até o índice em pos
    NoLista_encadeada p = self->pri;
    NoLista_encadeada p_ant;
    for (int i = 0; i < pos; i++)
    {
        p_ant = p;
        p = p->prox;
    }

    // insere um nó em pos
    NoLista_encadeada novo_no = cria_no(pdado, self->tam_dado);
    if (novo_no == NULL) return;
    p_ant->prox = novo_no;
    novo_no->prox = p;

    self->n_elem++;
}


// remove o elemento no início da lista_encadeada e copia seu dado para um ponteiro
void lista_encadeada_remove(Lista_encadeada self, void *removido)
{
    // verifica se a lista_encadeada está vazia
    if (lista_encadeada_vazia(self))
    {
        printf("Lista_encadeada vazia, não se pode remover elementos\n");
        return;
    }

    // copia o dado do primeiro elemento para *removido
    if (removido != NULL)
    {
        memmove(removido, self->pri->dado, self->tam_dado);
    }

    // desencadeia o primeiro nó e libera-o
    NoLista_encadeada temp = self->pri;
    self->pri = self->pri->prox;
    free(temp->dado);
    free(temp);

    // decrementa o número de elementos na lista_encadeada
    self->n_elem--;
}


// remove o elemento no indice pos da lista_encadeada e copia seu dado para um ponteiro
void lista_encadeada_remove_pos(Lista_encadeada self, void *removido, int pos)
{
    // verifica se o índice de remoção é válido
    if (pos >= self->n_elem)
    {
        printf("Índice de remoção inválido\n");
        return;
    }

    // percorre a lista_encadeada até o índice de remoção
    NoLista_encadeada p = self->pri;
    NoLista_encadeada p_ant;
    for (int i = 0; i < pos; i++)
    {
        p_ant = p;
        p = p->prox;
    }

    // copia o dado do nó a ser removido para o ponteiro
    if (removido != NULL)
    {
        memmove(removido, p->dado, self->tam_dado);
    }

    // desencadeia e libera o nó em pos
    NoLista_encadeada temp = p;
    p_ant->prox = p->prox;
    free(temp->dado);
    free(temp);

    self->n_elem--;
}


// verifica se n1 é maior que n2
static bool valor_maior(void *n1, void *n2)
{
    float a = *(float*)n1;
    float b = *(float*)n2;
    return a >= b;
}


// libera toda a memória alocada para uma lista_encadeada
void lista_encadeada_destroi(Lista_encadeada self)
{
    // percorre a lista_encadeada, liberando cada nó
    NoLista_encadeada p = self->pri;
    while (p != NULL)
    {
        NoLista_encadeada temp = p->prox;
        free(p->dado);
        free(p);
        p = temp;
    }
    // libera o descritor da lista_encadeada
    free(self);
}


// funções abaixo são usadas na função de sort da lista_encadeada
// https://www.geeksforgeeks.org/merge-sort-for-linked-list/


static void front_back_split(NoLista_encadeada origem, NoLista_encadeada *p_dianteiro, NoLista_encadeada *p_traseiro)
{
    /* Split the nodes of the given list into front and back halves,
    and return the two lists using the reference parameters.
    If the length is odd, the extra node should go in the front list.
    Uses the fast/slow pointer strategy. */

    NoLista_encadeada fast;
    NoLista_encadeada slow;
    slow = origem;
    fast = origem->prox;

    /* Advance 'fast' two nodes, and advance 'slow' one node */
    while (fast != NULL)
    {
        fast = fast->prox;
        if (fast != NULL)
        {
            slow = slow->prox;
            fast = fast->prox;
        }
    }

    /* 'slow' is before the midpoint in the list, so split it in two at that point. */
    *p_dianteiro = origem;
    *p_traseiro = slow->prox;
    slow->prox = NULL;
}


NoLista_encadeada sorted_merge(NoLista_encadeada a, NoLista_encadeada b)
{
    NoLista_encadeada result = NULL;

    /* Base cases */
    if (a == NULL) return b;
    if (b == NULL) return a;

    /* Pick either a or b, and recur */
    if (valor_maior(a->dado, b->dado))
    {
        result = b;
        result->prox = sorted_merge(a, b->prox);
    }
    else
    {
        result = a;
        result->prox = sorted_merge(a->prox, b);
    }
    return(result);
}


static void merge_sort(NoLista_encadeada *ponteiro_cabeca)
{
    // ponteiros para nós
    NoLista_encadeada cabeca = *ponteiro_cabeca;
    NoLista_encadeada a;
    NoLista_encadeada b;

    /* Base case -- length 0 or 1 */
    if (cabeca == NULL || cabeca->prox == NULL)
    {
        return;
    }

    /* Split head into 'a' and 'b' sublists */
    front_back_split(cabeca, &a, &b);

    /* Recursively sort the sublists */
    merge_sort(&a);
    merge_sort(&b);

    /* answer = merge the two sorted lists together */
    *ponteiro_cabeca = sorted_merge(a, b);
}


// organiza os elementos da lista_encadeada em ordem crescente
void lista_encadeada_sort(Lista_encadeada self)
{
    merge_sort(&self->pri);
}


// imprime uma lista_encadeada (apoio para os principais tipos de dados)
void lista_encadeada_imprime(Lista_encadeada self, char* tipo)
{
    if (lista_encadeada_vazia(self))
    {
        printf("[]\n");
        return;
    }

    NoLista_encadeada p = self->pri;
    printf("[");
    
    if (strcmp(tipo, "char") == 0)
    {
        while (p->prox != NULL)
        {
            printf("%c, ", *(char*)p->dado);
            p = p->prox;
        }
        printf("%c]\n", *(char*)p->dado);
    }
    else if (strcmp(tipo, "str") == 0)
    {
        while (p->prox != NULL)
        {
            printf("%s, ", (char*)p->dado);
            p = p->prox;
        }
        printf("%s]\n", (char*)p->dado);
    }
    else if (strcmp(tipo, "int") == 0)
    {
        while (p->prox != NULL)
        {
            printf("%d, ", *(int*)p->dado);
            p = p->prox;
        }
        printf("%d]\n", *(int*)p->dado);
    }
    else if (strcmp(tipo, "float") == 0)
    {
        while (p->prox != NULL)
        {
            printf("%.1f, ", *(float*)p->dado);
            p = p->prox;
        }
        printf("%.1f]\n", *(float*)p->dado);
    }
}