# Sistema de Captacao de Clientes (Trabalho 1)

Este projeto implementa, em C, um sistema de console para cadastro e acompanhamento de clientes em um fluxo comercial simples.

O objetivo principal do sistema e organizar clientes em diferentes etapas do atendimento usando estruturas de dados classicas:

- lista duplamente encadeada para clientes aguardando contato;
- fila para clientes que compraram;
- lista simplesmente encadeada para clientes arquivados.

## 1. Visao Geral

O programa apresenta um menu principal com 4 opcoes:

1. Cadastrar cliente
2. Realizar contato
3. Relatorios
4. Sair

Durante a execucao, os dados ficam em memoria RAM. Nao ha persistencia em arquivo ou banco de dados.

## 2. Requisitos e Compilacao

### 2.1. Requisitos

- Compilador C (ex.: GCC)
- Ambiente de terminal (Windows, Linux ou macOS)

### 2.2. Compilacao manual

No diretorio raiz do projeto, execute:

```bash
gcc -fdiagnostics-color=always -g -Wall -I include \
	src/cliente.c \
	src/main.c \
	src/lista.c \
	src/lista_dupla.c \
	src/fila.c \
	src/menu_cadastro.c \
	src/menu_realizar_contato.c \
	src/menu_relatorios.c \
	src/menu_finalizar_atendimento.c \
	src/util.c \
	-o programa.exe
```

Observacao: a task de build do VS Code usa lista fixa de arquivos .c. Se novos modulos forem criados em src/, eles precisam ser adicionados manualmente na task.

## 3. Fluxo Funcional da Aplicacao

### 3.1. Estado inicial

Ao iniciar, o sistema cria 3 estruturas:

- cadastrados (ListaDupla): clientes aguardando contato
- compradores (FilaClientes): clientes que compraram
- arquivados (Lista): clientes que nao compraram, mas foram arquivados

Se alguma alocacao falhar, o sistema imprime erro de memoria, libera o que foi criado e encerra.

### 3.2. Cadastro de cliente

Ao escolher a opcao de cadastro:

1. O sistema coleta dados do cliente:
   - codigo
   - nome
   - idade
   - e-mail
   - telefone
   - data de cadastro (dd/mm/aaaa)
2. A data e validada (formato e data real) e convertida para dias desde epoch.
3. O cliente e inserido no fim da lista duplamente encadeada de aguardando contato.

### 3.3. Realizar contato

Se houver clientes aguardando, o sistema abre uma navegacao pela lista dupla:

- proximo cliente
- cliente anterior
- busca por nome exato
- finalizar atendimento do cliente atual

Ao finalizar atendimento:

- Se comprou: remove da lista de aguardando e enfileira em compradores.
- Se nao comprou:
  - pergunta se deseja arquivar;
  - remove da lista de aguardando;
  - se arquivar = sim, insere no fim da lista de arquivados;
  - caso contrario, o cliente e descartado do sistema.

Depois de finalizar um cliente, se ainda houver clientes aguardando, a navegacao volta para o primeiro da lista.

### 3.4. Relatorios

O menu de relatorios atual opera sobre clientes aguardando contato:

1. Exibe quantidade de clientes aguardando contato.
2. Lista todos os clientes aguardando contato.

### 3.5. Encerramento

Ao sair do menu principal, o sistema libera toda a memoria das 3 estruturas e encerra.

## 4. Estruturas de Dados (Detalhado)

## 4.1. Registro de cliente

Estrutura Cliente:

- codigo: identificador numerico
- nome: texto com limite de TAM_NOME
- idade: inteiro
- email: texto com limite de TAM_EMAIL
- telefone: texto com limite de TAM_TEL
- dataCadastro: inteiro representando dias desde epoch (resultado da conversao de data)

Uso principal:

- unidade de dados movida entre lista dupla, fila e lista simples.

## 4.2. Lista duplamente encadeada (aguardando contato)

Estruturas:

- NoListaDupla: armazena Cliente e ponteiros ant/prox
- ListaDupla: ponteiros primeiro/ultimo + count

Operacoes principais:

- inicializar lista
- inserir cliente no final
- buscar por nome exato
- remover no conhecido
- listar clientes
- liberar memoria

Por que lista dupla aqui:

- permite navegacao para frente e para tras no menu de contato;
- remocao eficiente quando ja se tem ponteiro para o no atual.

## 4.3. Fila encadeada (compradores)

Estruturas:

- NoFila: cliente + ponteiro prox
- FilaClientes: ponteiros inicio/fim + tamanho

Operacoes principais:

- enfileirar no fim
- desenfileirar do inicio
- consultar frente
- verificar vazia
- liberar fila

Semantica:

- politica FIFO (First In, First Out).

No fluxo atual, clientes que compram vao para essa fila. Ela e mantida em memoria, embora nao exista ainda menu de relatorio/consumo dessa fila no main.

## 4.4. Lista simplesmente encadeada (arquivados)

Estruturas:

- NoLista: cliente + ponteiro prox
- Lista: ponteiros primeiro/ultimo + count

Operacoes principais:

- inserir no final
- listar
- buscar por nome exato
- remover no conhecido
- liberar memoria

Papel no fluxo:

- guardar clientes que nao compraram, mas que o operador escolheu arquivar.

## 5. Modulos e Responsabilidades (100% dos arquivos)

## 5.1. Arquivos de cabecalho (include)

### include/cliente.h

- Define constantes de tamanho de campos de texto.
- Declara struct Cliente.
- Declara funcoes:
  - cliente_criar
  - cliente_imprimir

### include/fila.h

- Define NoFila e FilaClientes.
- Declara operacoes da fila:
  - fila_inicializar
  - fila_vazia
  - fila_enfileirar
  - fila_desenfileirar
  - fila_frente
  - fila_liberar

### include/lista.h

- Define NoLista e Lista (lista simplesmente encadeada).
- Declara operacoes:
  - lista_inicializar
  - lista_inserir_final
  - listar_clientes
  - lista_buscar_por_nome
  - lista_remover
  - lista_liberar

### include/lista_dupla.h

- Define NoListaDupla e ListaDupla.
- Declara operacoes:
  - lista_dupla_inicializar
  - lista_dupla_inserir_final
  - lista_dupla_buscar_por_nome
  - lista_dupla_remover
  - lista_dupla_listar_clientes
  - lista_dupla_liberar

### include/menu_cadastro.h

- Declara menu_cadastro(ListaDupla \*cadastrados).
- Encapsula fluxo de cadastro e insercao em aguardando contato.

### include/menu_realizar_contato.h

- Declara menu_realizar_contato(ListaDupla *aguardando, FilaClientes *compradores, Lista \*arquivados).
- Encapsula fluxo de navegacao e acao sobre cliente em atendimento.

### include/menu_finalizar_atendimento.h

- Declara menu_finalizar_atendimento(...).
- Encapsula decisao de finalizacao (comprou / nao comprou + arquivar).

### include/menu_relatorios.h

- Declara menu_relatorios(ListaDupla \*cadastrados).
- Encapsula relatorios de aguardando contato.

### include/util.h

- Declara funcoes utilitarias de I/O e interface:
  - limpar_buffer
  - ler_string
  - ler_int
  - converter_data_para_dias
  - exibir_separador
  - pausar_enter
  - limpar_tela

## 5.2. Arquivos de implementacao (src)

### src/main.c

- Ponto de entrada do programa.
- Inicializa estruturas principais.
- Mostra menu principal em loop.
- Encaminha chamadas para:
  - menu_cadastro
  - menu_realizar_contato
  - menu_relatorios
- Realiza liberacao final de memoria.

### src/cliente.c

- Implementa criacao e exibicao de cliente.

cliente_criar:

- coleta campos do usuario;
- valida e converte data de cadastro;
- retorna 1 em sucesso e 0 se ponteiro for invalido.

cliente_imprimir:

- imprime dados formatados do cliente;
- calcula dias desde cadastro comparando com data atual;
- trata caso de data futura.

### src/lista_dupla.c

- Implementa lista duplamente encadeada de clientes aguardando contato.

Funcoes implementadas:

- lista_dupla_inicializar
- lista_dupla_inserir_final
- lista_dupla_buscar_por_nome
- lista_dupla_remover
- lista_dupla_listar_clientes
- lista_dupla_liberar

Detalhes importantes:

- count e mantido atualizado em insercoes/remocoes;
- remocao ajusta corretamente ponteiros de vizinhos e extremidades.

### src/fila.c

- Implementa fila encadeada para compradores.

Funcoes implementadas:

- fila_inicializar
- fila_vazia
- fila_enfileirar
- fila_desenfileirar
- fila_frente
- fila_liberar

Detalhes importantes:

- atualiza inicio/fim de forma consistente;
- fila_liberar consome a fila usando desenfileirar.

### src/lista.c

- Implementa lista simplesmente encadeada para arquivados.

Funcoes implementadas:

- lista_inicializar
- lista_inserir_final
- listar_clientes
- lista_buscar_por_nome
- lista_remover
- lista_liberar

Detalhes importantes:

- usa ponteiro para ultimo para insercao em O(1);
- remocao percorre para encontrar no alvo e atualiza primeiro/ultimo.

### src/menu_cadastro.c

- Implementa fluxo de cadastro.
- Valida ponteiro de estrutura de destino.
- Chama cliente_criar e, se sucesso, insere no fim da lista de aguardando.

### src/menu_realizar_contato.c

- Implementa interface de atendimento sobre a lista dupla.
- Permite navegacao bidirecional, busca por nome e finalizacao.
- Chama menu_finalizar_atendimento para executar transicao de estado do cliente.
- Trata caso de lista vazia antes de entrar no loop.

### src/menu_finalizar_atendimento.c

- Implementa regras de negocio de fechamento de atendimento.

Fluxo interno:

- pergunta se cliente comprou;
- se comprou:
  - remove de aguardando;
  - enfileira em compradores;
- se nao comprou:
  - pergunta se deseja arquivar;
  - remove de aguardando;
  - opcionalmente insere em arquivados;
  - ou descarta cliente.

### src/menu_relatorios.c

- Implementa menu de relatorios (escopo atual: aguardando contato).

Relatorios disponiveis:

- quantidade de clientes aguardando;
- listagem completa de aguardando.

### src/util.c

- Implementa utilitarios de entrada, validacao e interface.

Funcoes implementadas:

- limpar_buffer: consome caracteres restantes da entrada
- ler_string: leitura segura com fgets + remocao de \n
- ler_int: loop ate receber inteiro valido
- exibir_separador: imprime linha visual
- converter_data_para_dias:
  - valida formato dd/mm/aaaa
  - valida intervalo basico de dia/mes/ano
  - valida data real com mktime/localtime
  - converte para dias desde epoch
- pausar_enter: pausa fluxo ate ENTER
- limpar_tela: usa cls no Windows e clear em outros SOs

## 5.3. Demais arquivos

### LICENSE

- Licenca MIT do projeto.

### README.md

- Este documento.

## 6. Complexidade das Operacoes

Considerando n elementos na estrutura:

- ListaDupla inserir final: O(1)
- ListaDupla buscar por nome: O(n)
- ListaDupla remover por ponteiro para no: O(1)
- Lista simples inserir final (com ponteiro ultimo): O(1)
- Lista simples buscar por nome: O(n)
- Lista simples remover por ponteiro para no (com busca interna): O(n)
- Fila enfileirar: O(1)
- Fila desenfileirar: O(1)

## 7. Jornada de um Cliente no Sistema

Resumo do ciclo de vida:

1. Cliente e cadastrado.
2. Cliente entra em aguardando contato (lista dupla).
3. Atendimento e realizado.
4. Cliente pode ir para:
   - compradores (fila), se comprou;
   - arquivados (lista simples), se nao comprou e operador arquivou;
   - removido definitivamente, se nao comprou e operador nao arquivou.

Representacao textual:

Cadastro -> Aguardando contato -> Finalizar atendimento
Finalizar atendimento -> Compradores (se comprou)
Finalizar atendimento -> Arquivados (se nao comprou e arquivar)
Finalizar atendimento -> Removido (se nao comprou e nao arquivar)

## 8. Comportamento de Entrada e Validacao

- Inteiros sao lidos com validacao (repetindo pergunta em caso invalido).
- Strings usam leitura limitada por tamanho do buffer.
- Data exige formato dd/mm/aaaa e data real valida.
- Busca de cliente por nome usa comparacao exata (case-sensitive).

## 9. Limitacoes Atuais

- Dados sao apenas em memoria (sem salvar/carregar).
- Nao ha menu dedicado para visualizar fila de compradores.
- Nao ha menu dedicado para listar arquivados no fluxo principal.
- Busca por nome exige correspondencia exata.

## 10. Sugestoes de Evolucao

- Persistencia em arquivo (CSV, binario ou banco).
- Relatorios para compradores e arquivados.
- Busca por nome parcial e sem diferenca de maiuscula/minuscula.
- Validacoes adicionais (email/telefone).
- Separacao maior entre camada de apresentacao e regras de negocio.

## 11. Conclusao

O projeto organiza um funil simples de atendimento com estruturas de dados classicas e fluxo claro de transicao de estado dos clientes. A arquitetura modular por arquivos facilita manutencao, testes e extensao futura.
