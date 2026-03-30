#include <stdio.h>
#include "menu_realizar_contato.h"
#include "menu_finalizar_atendimento.h"
#include "util.h"


void menu_realizar_contato(ListaDupla *aguardando,
                           FilaClientes *compradores,
                           Lista *arquivados)
{
    NoListaDupla *atual;
    int opcao;

    if (aguardando->count == 0)
    {
        limpar_tela();
        printf("\n Nenhum cliente aguardando contato.\n");
        pausar_enter();
        return;
    }

    atual = aguardando->primeiro;

    do
    {
        limpar_tela();
        cliente_imprimir(atual->dados);
        printf(" Clientes na fila: %d\n\n", aguardando->count);
        printf(" 1. Proximo cliente\n");
        printf(" 2. Cliente anterior\n");
        printf(" 3. Buscar por nome\n");
        printf(" 4. Finalizar atendimento\n");
        printf(" 5. Voltar ao menu principal\n");
        exibir_separador();

        opcao = ler_int(" Opcao: ");

        switch (opcao)
        {
        case 1:
            if (atual->prox)
            {
                atual = atual->prox;
            }
            else
            {
                printf("\n Este e o ultimo cliente da lista.\n");
                pausar_enter();
            }
            break;

        case 2:
            if (atual->ant)
            {
                atual = atual->ant;
            }
            else
            {
                printf("\n Este e o primeiro cliente da lista.\n");
                pausar_enter();
            }
            break;

        case 3:
        {
            char nome_busca[100];
            NoListaDupla *resultado;

            ler_string(" Nome exato: ", nome_busca, sizeof(nome_busca));
            resultado = lista_dupla_buscar_por_nome(aguardando, nome_busca);

            if (resultado)
            {
                atual = resultado;
                printf("\n Cliente encontrado.\n");
            }
            else
            {
                printf("\n Cliente nao encontrado. Permanecendo no atual.\n");
            }

            pausar_enter();
            break;
        }

        case 4:
            menu_finalizar_atendimento(aguardando, compradores, arquivados, atual);

            if (aguardando->count == 0)
            {
                printf("\n Fila de contatos vazia.\n");
                pausar_enter();
            }
            else
            {
                atual = aguardando->primeiro;
            }
            break;

        case 5:
            break;

        default:
            printf("\n Opcao invalida.\n");
            pausar_enter();
        }

    } while (opcao != 5);
}
