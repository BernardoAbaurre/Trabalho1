#ifndef CLIENTE_H
#define CLIENTE_H

#define TAM_NOME 100
#define TAM_EMAIL 100
#define TAM_TEL 30
#define TAM_DATA 16
#define TAM_CPF 20
#define TAM_RUA 100
#define TAM_NUMERO 20
#define TAM_BAIRRO 60
#define TAM_CIDADE 60
#define TAM_ESTADO 30
#define TAM_CEP 20

typedef struct
{
    int codigo;
    char nome[TAM_NOME];
    int idade;
    char email[TAM_EMAIL];
    char telefone[TAM_TEL];
    int dataCadastro;
    int efetivo;
    char dataNascimento[TAM_DATA];
    char cpf[TAM_CPF];
    char rua[TAM_RUA];
    char numero[TAM_NUMERO];
    char bairro[TAM_BAIRRO];
    char cidade[TAM_CIDADE];
    char estado[TAM_ESTADO];
    char cep[TAM_CEP];
} Cliente;

int cliente_criar(Cliente *cliente);
int cliente_coletar_dados_efetivacao(Cliente *cliente);
void cliente_imprimir(Cliente cliente);

#endif