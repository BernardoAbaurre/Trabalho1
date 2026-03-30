#include <stddef.h>
#include "menu_cadastro.h"
#include "cliente.h"

void menu_cadastro(ListaDupla *cadastrados)
{
    Cliente c;

    if (cadastrados == NULL)
    {
        return;
    }

    if (cliente_criar(&c))
    {
        lista_dupla_inserir_final(cadastrados, c);
    }
}
