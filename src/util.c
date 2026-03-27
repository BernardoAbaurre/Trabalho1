// Este modulo foi criado para evitar repeticao de codigo em funcoes
// que leem dados do usuario, como ler_string e ler_int.
// Ele tambem inclui funcoes auxiliares para limpar o buffer,
// pausar a execucao e limpar a tela antes dos menus.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "util.h"

void limpar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

void ler_string(const char *msg, char *dest, int tamanho) {
    printf("%s", msg);

    if (fgets(dest, tamanho, stdin) != NULL) {
        dest[strcspn(dest, "\n")] = '\0';
    }
}

int ler_int(const char *msg) {
    int valor;
    int lidos;

    do {
        printf("%s", msg);
        lidos = scanf("%d", &valor);
        limpar_buffer();

        if (lidos != 1) {
            printf("Entrada invalida. Digite um numero inteiro.\n");
        }
    } while (lidos != 1);

    return valor;
}

void pausar_enter(void) {
    printf("\nPressione ENTER para continuar...");
    getchar();
}

void limpar_tela(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}