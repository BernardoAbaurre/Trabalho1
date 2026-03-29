#include <stdio.h>
#include <time.h>
#include "cliente.h"
#include "util.h"

int cliente_criar(Cliente *cliente)
{
    char dataInformada[16];
    int dataValida;

    if (cliente == NULL)
    {
        return 0;
    }

    printf("\n=== DADOS DO CLIENTE ===\n");
    cliente->codigo = ler_int("Codigo: ");
    ler_string("Nome: ", cliente->nome, TAM_NOME);
    cliente->idade = ler_int("Idade: ");
    ler_string("E-mail: ", cliente->email, TAM_EMAIL);
    ler_string("Telefone: ", cliente->telefone, TAM_TEL);

    do
    {
        ler_string("Data de cadastro (dd/mm/aaaa): ", dataInformada, sizeof(dataInformada));
        dataValida = converter_data_para_dias(dataInformada, &cliente->dataCadastro);

        if (!dataValida)
        {
            printf("Data invalida. Use o formato dd/mm/aaaa e uma data real a partir de 1970.\n");
        }
    } while (!dataValida);

    return 1;
}

void cliente_imprimir(const Cliente cliente)
{
    const int segundos_por_dia = 86400;
    time_t agora;
    int dias_hoje;
    int dias_desde_cadastro;

    agora = time(NULL);
    dias_hoje = (agora == (time_t)-1) ? cliente.dataCadastro : (int)(agora / segundos_por_dia);
    dias_desde_cadastro = dias_hoje - cliente.dataCadastro;

    printf("----------------------------------------\n");
    printf("Codigo   : %d\n", cliente.codigo);
    printf("Nome     : %s\n", cliente.nome);
    printf("Idade    : %d\n", cliente.idade);
    printf("E-mail   : %s\n", cliente.email);
    printf("Telefone : %s\n", cliente.telefone);
    if (dias_desde_cadastro >= 0)
    {
        printf("Cadastro : ha %d dia(s)\n", dias_desde_cadastro);
    }
    else
    {
        printf("Cadastro : em %d dia(s) (data futura)\n", -dias_desde_cadastro);
    }

}
