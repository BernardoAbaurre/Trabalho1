#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_arquivados.h"

static No *criar_no(Cliente c) {
    No *novo = (No *)malloc(sizeof(No));

    if (novo == NULL) {
        printf("Erro: memoria insuficiente.\n");
        return NULL;
    }

    novo->dados = c;
    novo->prox = NULL;
    return novo;
}

No *inserir_final(No *lista, Cliente c) {
    No *novo = criar_no(c);

    if (novo == NULL) {
        return lista;
    }

    if (lista == NULL) {
        return novo;
    }

    No *aux = lista;
    while (aux->prox != NULL) {
        aux = aux->prox;
    }

    aux->prox = novo;
    return lista;
}

void listar_clientes(No *lista) {
    if (lista == NULL) {
        printf("\nNenhum cliente arquivado.\n");
        return;
    }

    printf("\n=== CLIENTES ARQUIVADOS ===\n");

    while (lista != NULL) {
        printf("----------------------------------------\n");
        printf("Codigo   : %d\n", lista->dados.codigo);
        printf("Nome     : %s\n", lista->dados.nome);
        printf("Idade    : %d\n", lista->dados.idade);
        printf("E-mail   : %s\n", lista->dados.email);
        printf("Telefone : %s\n", lista->dados.telefone);

        lista = lista->prox;
    }

    printf("----------------------------------------\n");
}

No *buscar_por_nome(No *lista, const char *nome) {
    while (lista != NULL) {
        if (strcmp(lista->dados.nome, nome) == 0) {
            return lista;
        }
        lista = lista->prox;
    }

    return NULL;
}

No *remover_por_nome(No *lista, const char *nome, int *removido) {
    No *atual = lista;
    No *anterior = NULL;

    *removido = 0;

    while (atual != NULL && strcmp(atual->dados.nome, nome) != 0) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        return lista;
    }

    if (anterior == NULL) {
        lista = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    free(atual);
    *removido = 1;

    return lista;
}

int contar_clientes(No *lista) {
    int cont = 0;

    while (lista != NULL) {
        cont++;
        lista = lista->prox;
    }

    return cont;
}

void liberar_lista(No *lista) {
    No *temp;

    while (lista != NULL) {
        temp = lista;
        lista = lista->prox;
        free(temp);
    }
}