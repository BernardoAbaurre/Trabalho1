#ifndef LISTA_H
#define LISTA_H

#include "cliente.h"

typedef struct NoLista
{
    Cliente dados;
    struct NoLista *prox;
} NoLista;

typedef struct Lista
{
    NoLista *primeiro;
    NoLista *ultimo;
    int count;
} Lista;

Lista *lista_inicializar(void);
int lista_inserir_final(Lista *lista, Cliente c);
void listar_clientes(const Lista *lista);
NoLista *lista_buscar_por_nome(Lista *lista, const char *nome);
int lista_remover(Lista *lista, NoLista *no);
void lista_liberar(Lista *lista);

#endif