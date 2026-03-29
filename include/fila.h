#ifndef FILA_H
#define FILA_H

#include "cliente.h"

typedef struct NoFila
{
    Cliente dados;
    struct NoFila *prox;
} NoFila;

typedef struct
{
    NoFila *inicio;
    NoFila *fim;
    int tamanho;
} FilaClientes;

FilaClientes *fila_inicializar(void);
int fila_vazia(const FilaClientes *fila);
int fila_enfileirar(FilaClientes *fila, Cliente c);
int fila_desenfileirar(FilaClientes *fila, Cliente *c);
int fila_frente(const FilaClientes *fila, Cliente *c);
void fila_liberar(FilaClientes *fila);

#endif /* FILA_H */
