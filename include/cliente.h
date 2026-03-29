#ifndef CLIENTE_H
#define CLIENTE_H

#define TAM_NOME 100
#define TAM_EMAIL 100
#define TAM_TEL 30

typedef struct {
    int codigo;
    char nome[TAM_NOME];
    int idade;
    char email[TAM_EMAIL];
    char telefone[TAM_TEL];
} Cliente;

#endif