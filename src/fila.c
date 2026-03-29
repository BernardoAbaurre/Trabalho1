#include <stdlib.h>
#include "fila.h"

FilaClientes *fila_inicializar()
{
    FilaClientes *fila = malloc(sizeof(FilaClientes));

    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;

    return fila;
}

int fila_vazia(const FilaClientes *fila)
{
    return fila->inicio == NULL;
}

int fila_enfileirar(FilaClientes *fila, Cliente c)
{
    NoFila *novo = (NoFila *)malloc(sizeof(NoFila));

    if (novo == NULL)
    {
        return 0;
    }

    novo->dados = c;
    novo->prox = NULL;

    if (fila_vazia(fila))
    {
        fila->inicio = novo;
    }
    else
    {
        fila->fim->prox = novo;
    }

    fila->fim = novo;
    fila->tamanho++;
    return 1;
}

int fila_desenfileirar(FilaClientes *fila, Cliente *c)
{
    NoFila *removido;

    if (fila_vazia(fila))
    {
        return 0;
    }

    removido = fila->inicio;
    *c = removido->dados;
    fila->inicio = removido->prox;

    if (fila->inicio == NULL)
    {
        fila->fim = NULL;
    }

    fila->tamanho--;
    free(removido);
    return 1;
}

int fila_frente(const FilaClientes *fila, Cliente *c)
{
    if (fila_vazia(fila))
    {
        return 0;
    }

    *c = fila->inicio->dados;
    return 1;
}

void fila_liberar(FilaClientes *fila)
{
    Cliente descartado;

    while (fila_desenfileirar(fila, &descartado))
    {
    }
}
