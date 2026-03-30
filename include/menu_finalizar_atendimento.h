#ifndef MENU_FINALIZAR_ATENDIMENTO_H
#define MENU_FINALIZAR_ATENDIMENTO_H

#include "lista_dupla.h"
#include "fila.h"
#include "lista.h"

void menu_finalizar_atendimento(ListaDupla *aguardando_contato,
                                FilaClientes *compradores,
                                Lista *arquivados,
                                NoListaDupla *no_cliente);

#endif
