#ifndef LISTA_ARQUIVADOS_H
#define LISTA_ARQUIVADOS_H

#include "cliente.h"

typedef struct No {
    Cliente dados;
    struct No *prox;
} No;

No *inserir_final(No *lista, Cliente c);
void listar_clientes(No *lista);
No *buscar_por_nome(No *lista, const char *nome);
No *remover_por_nome(No *lista, const char *nome, int *removido);
int contar_clientes(No *lista);
void liberar_lista(No *lista);

#endif