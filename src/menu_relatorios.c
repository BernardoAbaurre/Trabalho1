#include <stdio.h>
#include "menu_relatorios.h"
#include "util.h"

static void relatorio_numero_clientes_aguardando_contato(ListaDupla *cadastrados)
{
    limpar_tela();
    printf("\n");
    exibir_separador();
    printf("   NUMERO DE CLIENTES AGUARDANDO CONTATO\n");
    exibir_separador();
    printf("%d clientes", cadastrados->count);
    exibir_separador();
    pausar_enter();
}

static void relatorio_listar_clientes_aguardando_contato(ListaDupla *cadastrados)
{
    limpar_tela();
    printf("\n");
    exibir_separador();
    printf("   CLIENTES AGUARDANDO CONTATO\n");
    exibir_separador();
    lista_dupla_listar_clientes(cadastrados);
    exibir_separador();
    pausar_enter();
}

void menu_relatorios(ListaDupla *cadastrados)
{
    int opcao;

    if (cadastrados == NULL)
    {
        return;
    }

    limpar_tela();
    printf("\n");
    exibir_separador();
    printf("   MENU - RELATORIOS\n");
    exibir_separador();
    printf("1 - Numero de clientes que estao aguardando contato.\n");
    printf("2 - Listar clientes aguardando contato\n");
    printf("3 - Voltar\n");
    exibir_separador();

    opcao = ler_int("Escolha uma opcao: ");

    switch (opcao)
    {
    case 1:
        relatorio_numero_clientes_aguardando_contato(cadastrados);
        break;

    case 2:
        relatorio_listar_clientes_aguardando_contato(cadastrados);
        break;

    case 3:
        pausar_enter();
        return;

    default:
        printf("\nOpcao invalida.\n");
        menu_relatorios(cadastrados);
    }
}
