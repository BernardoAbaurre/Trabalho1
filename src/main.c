#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "lista.h"
#include "fila.h"
#include "lista_dupla.h"
#include "menu_cadastro.h"
#include "menu_realizar_contato.h"
#include "menu_relatorios.h"

int main(void)
{
    Lista *arquivados = lista_inicializar();
    ListaDupla *cadastrados = lista_dupla_inicializar();
    FilaClientes *compradores = fila_inicializar();
    int opcao;

    if (arquivados == NULL || cadastrados == NULL || compradores == NULL)
    {
        printf("\nErro: memoria insuficiente para inicializar estruturas.\n");
        lista_liberar(arquivados);
        lista_dupla_liberar(cadastrados);
        fila_liberar(compradores);
        free(compradores);
        return 1;
    }

    do
    {
        limpar_tela();
        printf("\n");
        exibir_separador();
        printf(" SISTEMA DE CAPTACAO DE CLIENTES\n");
        exibir_separador();
        printf("1 - Cadastrar cliente\n");
        printf("2 - Realizar contato\n");
        printf("3 - Relatorios\n");
        printf("4 - Sair\n");
        exibir_separador();

        opcao = ler_int("Escolha uma opcao: ");

        switch (opcao)
        {
        case 1:
            menu_cadastro(cadastrados);
            break;

        case 2:
            menu_realizar_contato(cadastrados, compradores, arquivados);
            break;

        case 3:
            menu_relatorios(cadastrados);
            break;

        case 4:
            printf("\nEncerrando o sistema...\n");
            pausar_enter();
            break;

        default:
            printf("\nOpcao invalida.\n");
            pausar_enter();
        }

    } while (opcao != 4);

    lista_liberar(arquivados);
    lista_dupla_liberar(cadastrados);
    fila_liberar(compradores);
    free(compradores);
    return 0;
}