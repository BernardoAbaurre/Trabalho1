#include <stdio.h>
#include <time.h>
#include "cliente.h"
#include "util.h"

int cliente_coletar_dados_efetivacao(Cliente *cliente)
{

    printf("\n");
    exibir_separador();
    printf(" DADOS COMPLEMENTARES - CLIENTE EFETIVO\n");
    exibir_separador();

    ler_string("Data de nascimento (dd/MM/YYYY): ", cliente->dataNascimento, TAM_DATA);

    ler_string("CPF: ", cliente->cpf, TAM_CPF);
    ler_string("Rua: ", cliente->rua, TAM_RUA);
    ler_string("Numero: ", cliente->numero, TAM_NUMERO);
    ler_string("Bairro: ", cliente->bairro, TAM_BAIRRO);
    ler_string("Cidade: ", cliente->cidade, TAM_CIDADE);
    ler_string("Estado: ", cliente->estado, TAM_ESTADO);
    ler_string("CEP: ", cliente->cep, TAM_CEP);

    cliente->efetivo = 1;
    return 1;
}

int cliente_criar(Cliente *cliente)
{
    char dataInformada[16];
    int dataValida;

    if (cliente == NULL)
    {
        return 0;
    }

    printf("\n");
    exibir_separador();
    printf(" DADOS DO CLIENTE\n");
    exibir_separador();
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

    cliente->efetivo = 0;
    cliente->dataNascimento[0] = '\0';
    cliente->cpf[0] = '\0';
    cliente->rua[0] = '\0';
    cliente->numero[0] = '\0';
    cliente->bairro[0] = '\0';
    cliente->cidade[0] = '\0';
    cliente->estado[0] = '\0';
    cliente->cep[0] = '\0';

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

    if (cliente.efetivo)
    {
        printf("Status   : Cliente efetivo\n");
        printf("Nasc.    : %s\n", cliente.dataNascimento);
        printf("CPF      : %s\n", cliente.cpf);
        printf("Endereco : %s, %s, %s, %s - %s, CEP %s\n",
               cliente.rua,
               cliente.numero,
               cliente.bairro,
               cliente.cidade,
               cliente.estado,
               cliente.cep);
    }
}
