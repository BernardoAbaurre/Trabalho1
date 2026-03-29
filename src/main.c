#include <stdio.h>
#include "cliente.h"
#include "util.h"
#include "lista_arquivados.h"

static Cliente ler_cliente(void) {
    Cliente c;

    printf("\n=== DADOS DO CLIENTE ===\n");
    c.codigo = ler_int("Codigo: ");
    ler_string("Nome: ", c.nome, TAM_NOME);
    c.idade = ler_int("Idade: ");
    ler_string("E-mail: ", c.email, TAM_EMAIL);
    ler_string("Telefone: ", c.telefone, TAM_TEL);

    return c;
}

static void processar_cliente_sem_compra(No **arquivados) {
    Cliente c;
    int opcao;
    limpar_tela();

    printf("\n=== CLIENTE NAO COMPROU ===\n");
    c = ler_cliente();

    printf("\nO cliente nao comprou o produto.\n");
    printf("Deseja arquivar ou excluir?\n");
    printf("1 - Arquivar\n");
    printf("2 - Excluir\n");

    opcao = ler_int("Escolha uma opcao: ");

    if (opcao == 1) {
        *arquivados = inserir_final(*arquivados, c);
        printf("\nCliente arquivado com sucesso.\n");
    } else if (opcao == 2) {
        printf("\nCliente excluido definitivamente do sistema.\n");
    } else {
        printf("\nOpcao invalida. Nenhuma acao foi realizada.\n");
    }

    pausar_enter();
}

static void menu_arquivados(No **arquivados) {
    int opcao;
    char nome[TAM_NOME];
    No *encontrado;
    int removido;

    do {
        limpar_tela();
        printf("\n========================================\n");
        printf("   MENU - CLIENTES ARQUIVADOS\n");
        printf("========================================\n");
        printf("1 - Listar clientes arquivados\n");
        printf("2 - Buscar cliente por nome\n");
        printf("3 - Remover cliente arquivado por nome\n");
        printf("4 - Quantidade de clientes arquivados\n");
        printf("0 - Voltar ao menu principal\n");
        printf("========================================\n");

        opcao = ler_int("Escolha uma opcao: ");

        switch (opcao) {
            case 1:
                listar_clientes(*arquivados);
                pausar_enter();
                break;

            case 2:
                ler_string("Digite o nome para buscar: ", nome, TAM_NOME);
                encontrado = buscar_por_nome(*arquivados, nome);

                if (encontrado != NULL) {
                    printf("\nCliente encontrado:\n");
                    printf("----------------------------------------\n");
                    printf("Codigo   : %d\n", encontrado->dados.codigo);
                    printf("Nome     : %s\n", encontrado->dados.nome);
                    printf("Idade    : %d\n", encontrado->dados.idade);
                    printf("E-mail   : %s\n", encontrado->dados.email);
                    printf("Telefone : %s\n", encontrado->dados.telefone);
                    printf("----------------------------------------\n");
                } else {
                    printf("\nCliente nao encontrado.\n");
                }
                pausar_enter();
                break;

            case 3:
                ler_string("Digite o nome para remover: ", nome, TAM_NOME);
                *arquivados = remover_por_nome(*arquivados, nome, &removido);

                if (removido) {
                    printf("\nCliente removido da lista de arquivados.\n");
                } else {
                    printf("\nCliente nao encontrado.\n");
                }
                pausar_enter();
                break;

            case 4:
                printf("\nTotal de clientes arquivados: %d\n", contar_clientes(*arquivados));
                pausar_enter();
                break;

            case 0:
                printf("\nVoltando ao menu principal...\n");
                break;

            default:
                printf("\nOpcao invalida.\n");
                pausar_enter();
        }

    } while (opcao != 0);
}

int main(void) {
    No *arquivados = NULL;
    int opcao;

    do {
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

        switch (opcao) {
            case 1:
                processar_cliente_sem_compra(&arquivados);
                break;

            case 2:
                printf("\nModulo de contato ainda nao implementado.\n");
                pausar_enter();
                break;

            case 3:
                menu_arquivados(&arquivados);
                break;

            case 4:
                printf("\nEncerrando o sistema...\n");
                break;

            default:
                printf("\nOpcao invalida.\n");
                pausar_enter();
        }

    } while (opcao != 4);

    liberar_lista(arquivados);
    return 0;
}