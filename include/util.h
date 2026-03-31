//    Essa classe foi criada para evitar a repetição de código em funções que leem dados do usuário,
// como ler_string e ler_int. Ela também inclui uma função para limpar o buffer de entrada,
// o que é útil para evitar problemas com entradas anteriores afetando as próximas leituras.
// A função pausar_enter é usada para pausar a execução do programa até que o usuário pressione Enter,
// o que pode ser útil para dar ao usuário tempo para ler mensagens antes de continuar.
#ifndef UTIL_H
#define UTIL_H

void limpar_buffer(void);
void ler_string(const char *msg, char *dest, int tamanho);
int ler_int(const char *msg);
int perguntar_sim_nao(const char *pergunta);
int converter_data_para_dias(const char *data, int *dias);
void exibir_separador(void);
void pausar_enter(void);
void limpar_tela(void);

#endif