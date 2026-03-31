#include <stdio.h>
#include "menu_finalizar_atendimento.h"
#include "util.h"

static void finalizar_como_comprador(ListaDupla *aguardando_contato,
                                     FilaClientes *compradores,
                                     NoListaDupla *no_cliente)
{
    Cliente c;

    c = no_cliente->dados;

    cliente_coletar_dados_efetivacao(&c);

    if (!lista_dupla_remover(aguardando_contato, no_cliente))
    {
        printf("\n Falha ao remover cliente da lista de aguardando.\n");
        return;
    }

    if (!fila_enfileirar(compradores, c))
    {
        printf("\n Falha ao mover cliente para a fila de compradores.\n");
        return;
    }

    printf("\n Cliente movido para a fila de compradores!\n");
}

static void finalizar_como_nao_comprador(ListaDupla *aguardando_contato,
                                         Lista *arquivados,
                                         NoListaDupla *no_cliente)
{
    int arquivar;
    Cliente cliente;

    arquivar = perguntar_sim_nao(" Deseja arquivar os dados para contato futuro?");

    cliente = no_cliente->dados;

    if (!lista_dupla_remover(aguardando_contato, no_cliente))
    {
        printf("\n Falha ao remover cliente da lista de aguardando.\n");
        return;
    }

    if (arquivar == 1)
    {
        if (lista_inserir_final(arquivados, cliente))
        {
            printf("\n Cliente arquivado.\n");
        }
        else
        {
            printf("\n Falha ao arquivar cliente.\n");
        }
    }
    else
    {
        printf("\n Cliente removido do sistema.\n");
    }
}

void menu_finalizar_atendimento(ListaDupla *aguardando_contato,
                                FilaClientes *compradores,
                                Lista *arquivados,
                                NoListaDupla *no_cliente)
{
    limpar_tela();
    exibir_separador();
    printf("   FINALIZAR ATENDIMENTO - %s\n", no_cliente->dados.nome);
    exibir_separador();

    int comprou = perguntar_sim_nao(" O cliente comprou o produto?");

    if (comprou == 1)
    {
        finalizar_como_comprador(aguardando_contato, compradores, no_cliente);
    }
    else
    {
        finalizar_como_nao_comprador(aguardando_contato, arquivados, no_cliente);
    }

    pausar_enter();
}
