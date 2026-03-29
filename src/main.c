#include <stdio.h>
#include "cliente.h"
#include "util.h"
#include "lista.h"
#include "fila.h"
#include "lista_dupla.h"

void cadastrar_cliente(ListaDupla *cadastrados)
{
    Cliente c;

    if (cliente_criar(&c))
    {
        lista_dupla_inserir_final(cadastrados, c);
    }
}

void processar_cliente_sem_compra(Lista *arquivados)
{
    Cliente c;
    int opcao;
    limpar_tela();

    printf("\nO cliente nao comprou o produto.\n");
    printf("Deseja arquivar ou excluir?\n");
    printf("1 - Arquivar\n");
    printf("2 - Excluir\n");

    opcao = ler_int("Escolha uma opcao: ");

    if (opcao == 1)
    {
        if (lista_inserir_final(arquivados, c))
        {
            printf("\nCliente arquivado com sucesso.\n");
        }
        else
        {
            printf("\nFalha ao arquivar cliente.\n");
        }
    }
    else if (opcao == 2)
    {
        printf("\nCliente excluido definitivamente do sistema.\n");
    }
    else
    {
        printf("\nOpcao invalida. Nenhuma acao foi realizada.\n");
    }

    pausar_enter();
}

void relatorio_numero_clientes_aguardando_contato(ListaDupla *cadastrados)
{
    limpar_tela();
    printf("\n============================================================\n");
    printf("   NÚMERO DE CLIENTES AGUARDANDO CONTATO\n");
    printf("============================================================\n");
    printf("%d clientes", cadastrados->count);
    printf("============================================================\n");
    pausar_enter();
}

void relatorio_listar_clientes_aguardando_contato(ListaDupla *cadastrados)
{
    limpar_tela();
    printf("\n==================================================\n");
    printf("   CLIENTES AGUARDANDO CONTATO\n");
    printf("==================================================\n");
    lista_dupla_listar_clientes(cadastrados);
    printf("==================================================\n");
    pausar_enter();
}

void menu_relatorios(ListaDupla *cadastrados)
{
    limpar_tela();
    printf("\n========================================\n");
    printf("   MENU - RELATÓRIOS\n");
    printf("========================================\n");
    printf("1 - Numero de clientes que estao aguardando contato.\n");
    printf("2 - Listar clientes aguardando contato\n");
    printf("3 - Voltar\n");
    printf("========================================\n");

    int opcao = ler_int("Escolha uma opcao: ");

    switch (opcao)
    {
    case 1:
        relatorio_numero_clientes_aguardando_contato(cadastrados);
        break;

    case 2:
        relatorio_listar_clientes_aguardando_contato(cadastrados);
        pausar_enter();
        break;

    case 3:
        pausar_enter();
        return;
        break;
    default:
        printf("\nOpcao invalida.\n");
        menu_relatorios(cadastrados);
    }
}

int main(void)
{
    Lista *arquivados = lista_inicializar();
    ListaDupla *cadastrados = lista_dupla_inicializar();
    int opcao;

    if (arquivados == NULL || cadastrados == NULL)
    {
        printf("\nErro: memoria insuficiente para inicializar estruturas.\n");
        lista_liberar(arquivados);
        lista_dupla_liberar(cadastrados);
        return 1;
    }

    do
    {
        limpar_tela();
        printf("\n========================================\n");
        printf(" SISTEMA DE CAPTACAO DE CLIENTES\n");
        printf("========================================\n");
        printf("1 - Cadastrar cliente\n");
        printf("2 - Realizar contato\n");
        printf("3 - Relatorios\n");
        printf("4 - Sair\n");
        printf("========================================\n");

        opcao = ler_int("Escolha uma opcao: ");

        switch (opcao)
        {
        case 1:
            cadastrar_cliente(cadastrados);
            break;

        case 2:
            printf("\nModulo de contato ainda nao implementado.\n");
            pausar_enter();
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
    return 0;
}