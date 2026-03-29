#ifndef LISTA_DUPLA_H
#define LISTA_DUPLA_H

#include "cliente.h"

typedef struct NoListaDupla
{
    Cliente dados;
    struct NoListaDupla *ant;
    struct NoListaDupla *prox;
} NoListaDupla;

typedef struct ListaDupla
{
    NoListaDupla *primeiro;
    NoListaDupla *ultimo;
    int count;
} ListaDupla;

ListaDupla *lista_dupla_inicializar(void);
int lista_dupla_inserir_final(ListaDupla *fila, Cliente c);
NoListaDupla *lista_dupla_buscar_por_nome(ListaDupla *fila, const char *nome);
int lista_dupla_remover(ListaDupla *fila, NoListaDupla *no);
void lista_dupla_listar_clientes(const ListaDupla *fila);
void lista_dupla_liberar(ListaDupla *fila);

#endif /* LISTA_DUPLA_H */
