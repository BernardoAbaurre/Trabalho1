#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "util.h"

static int lista_vazia(const Lista *lista)
{
    return lista == NULL || lista->primeiro == NULL;
}

static NoLista *criar_no(Cliente c)
{
    NoLista *novo;

    novo = (NoLista *)malloc(sizeof(NoLista));

    if (novo == NULL)
    {
        return NULL;
    }

    novo->dados = c;
    novo->prox = NULL;
    return novo;
}

Lista *lista_inicializar(void)
{
    Lista *lista;

    lista = (Lista *)malloc(sizeof(Lista));

    if (lista == NULL)
    {
        return NULL;
    }

    lista->primeiro = NULL;
    lista->ultimo = NULL;
    lista->count = 0;

    return lista;
}

int lista_inserir_final(Lista *lista, Cliente c)
{
    NoLista *novo;

    if (lista == NULL)
    {
        return 0;
    }

    novo = criar_no(c);

    if (novo == NULL)
    {
        return 0;
    }

    if (lista_vazia(lista))
    {
        lista->primeiro = novo;
    }
    else
    {
        lista->ultimo->prox = novo;
    }

    lista->ultimo = novo;
    lista->count++;

    return 1;
}

void listar_clientes(const Lista *lista)
{
    NoLista *atual;

    if (lista_vazia(lista))
    {
        printf("\nNenhum cliente arquivado.\n");
        return;
    }

    printf("\n");
    exibir_separador();
    printf(" CLIENTES ARQUIVADOS\n");
    exibir_separador();
    atual = lista->primeiro;

    while (atual != NULL)
    {
        cliente_imprimir(atual->dados);

        atual = atual->prox;
    }

    printf("----------------------------------------\n");
}

NoLista *lista_buscar_por_nome(Lista *lista, const char *nome)
{
    NoLista *atual;

    if (lista_vazia(lista) || nome == NULL)
    {
        return NULL;
    }

    atual = lista->primeiro;

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

int lista_remover(Lista *lista, NoLista *no)
{
    NoLista *atual;
    NoLista *anterior = NULL;

    if (lista_vazia(lista) || no == NULL)
    {
        return 0;
    }

    atual = lista->primeiro;

    while (atual != NULL && atual != no)
    {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL)
    {
        return 0;
    }

    if (anterior == NULL)
    {
        lista->primeiro = atual->prox;
    }
    else
    {
        anterior->prox = atual->prox;
    }

    if (lista->ultimo == atual)
    {
        lista->ultimo = anterior;
    }

    free(atual);
    lista->count--;

    return 1;
}

void lista_liberar(Lista *lista)
{
    NoLista *atual;
    NoLista *proximo;

    if (lista == NULL)
    {
        return;
    }

    atual = lista->primeiro;

    while (atual != NULL)
    {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }

    free(lista);
}