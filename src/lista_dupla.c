#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lista_dupla.h"

static int lista_dupla_vazia(const ListaDupla *fila)
{
    return fila == NULL || fila->primeiro == NULL;
}

ListaDupla *lista_dupla_inicializar(void)
{
    ListaDupla *fila = (ListaDupla *)malloc(sizeof(ListaDupla));

    if (fila == NULL)
    {
        return NULL;
    }

    fila->primeiro = NULL;
    fila->ultimo = NULL;
    fila->count = 0;

    return fila;
}

int lista_dupla_inserir_final(ListaDupla *fila, Cliente c)
{
    NoListaDupla *novo;

    if (fila == NULL)
    {
        return 0;
    }

    novo = (NoListaDupla *)malloc(sizeof(NoListaDupla));

    if (novo == NULL)
    {
        return 0;
    }

    novo->dados = c;
    novo->ant = fila->ultimo;
    novo->prox = NULL;

    if (lista_dupla_vazia(fila))
    {
        fila->primeiro = novo;
    }
    else
    {
        fila->ultimo->prox = novo;
    }

    fila->ultimo = novo;
    fila->count++;

    return 1;
}

NoListaDupla *lista_dupla_buscar_por_nome(ListaDupla *fila, const char *nome)
{
    NoListaDupla *atual;

    if (lista_dupla_vazia(fila) || nome == NULL)
    {
        return NULL;
    }

    atual = fila->primeiro;

    while (atual != NULL)
    {
        if (strcmp(atual->dados.nome, nome) == 0)
        {
            return atual;
        }

        atual = atual->prox;
    }

    return NULL;
}

int lista_dupla_remover(ListaDupla *fila, NoListaDupla *no)
{
    if (lista_dupla_vazia(fila) || no == NULL)
    {
        return 0;
    }

    if (no->ant != NULL)
    {
        no->ant->prox = no->prox;
    }
    else
    {
        fila->primeiro = no->prox;
    }

    if (no->prox != NULL)
    {
        no->prox->ant = no->ant;
    }
    else
    {
        fila->ultimo = no->ant;
    }

    fila->count--;
    free(no);

    return 1;
}

void lista_dupla_listar_clientes(const ListaDupla *fila)
{
    NoListaDupla *atual;

    if (lista_dupla_vazia(fila))
    {
        printf("\nNenhum cliente aguardando contato.\n");
        return;
    }

    atual = fila->primeiro;

    while (atual != NULL)
    {
        cliente_imprimir(atual->dados);
        atual = atual->prox;
    }
}

void lista_dupla_liberar(ListaDupla *fila)
{
    NoListaDupla *atual;
    NoListaDupla *proximo;

    if (fila == NULL)
    {
        return;
    }

    atual = fila->primeiro;

    while (atual != NULL)
    {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }

    free(fila);
}
