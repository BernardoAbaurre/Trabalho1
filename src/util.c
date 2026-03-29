// Este modulo foi criado para evitar repeticao de codigo em funcoes
// que leem dados do usuario, como ler_string e ler_int.
// Ele tambem inclui funcoes auxiliares para limpar o buffer,
// pausar a execucao e limpar a tela antes dos menus.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "util.h"

void limpar_buffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

void ler_string(const char *msg, char *dest, int tamanho)
{
    printf("%s", msg);

    if (fgets(dest, tamanho, stdin) != NULL)
    {
        dest[strcspn(dest, "\n")] = '\0';
    }
}

int ler_int(const char *msg)
{
    int valor;
    int lidos;

    do
    {
        printf("%s", msg);
        lidos = scanf("%d", &valor);
        limpar_buffer();

        if (lidos != 1)
        {
            printf("Entrada invalida. Digite um numero inteiro.\n");
        }
    } while (lidos != 1);

    return valor;
}

int converter_data_para_dias(const char *data, int *dias)
{
    const int segundos_por_dia = 86400;
    int dia;
    int mes;
    int ano;
    char extra;
    struct tm data_tm = {0};
    time_t timestamp;
    struct tm *validada;

    if (data == NULL || dias == NULL)
    {
        return 0;
    }

    if (sscanf(data, "%d/%d/%d%c", &dia, &mes, &ano, &extra) != 3)
    {
        return 0;
    }

    if (ano < 1970 || mes < 1 || mes > 12 || dia < 1 || dia > 31)
    {
        return 0;
    }

    data_tm.tm_mday = dia;
    data_tm.tm_mon = mes - 1;
    data_tm.tm_year = ano - 1900;
    data_tm.tm_isdst = -1;

    timestamp = mktime(&data_tm);

    if (timestamp == (time_t)-1)
    {
        return 0;
    }

    validada = localtime(&timestamp);

    if (validada == NULL)
    {
        return 0;
    }

    if (validada->tm_mday != dia || validada->tm_mon != (mes - 1) || validada->tm_year != (ano - 1900))
    {
        return 0;
    }

    *dias = (int)(timestamp / segundos_por_dia);
    return 1;
}

void pausar_enter(void)
{
    printf("\nPressione ENTER para continuar...");
    getchar();
}

void limpar_tela(void)
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}