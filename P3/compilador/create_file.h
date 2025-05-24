#ifndef CREATE_FILE_COMPILER_H
#define CREATE_FILE_COMPILER_H

#include "arvore.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <wchar.h>

void criar_arquivo(NO *raiz);
void mover_para_celula(FILE *f, int alvo, int atual); 
void gerar_soma_bf(FILE *f, int a, int b, int res, int *cel_atual);
void gerar_sub_bf(FILE *f, int a, int b, int res, int *cel_atual);
void gerar_mult_bf(FILE *f, int a, int b, int res, int tmp1, int tmp2, int *cel_atual); 
void gerar_div_bf(FILE *f, int a, int b, int res, int valor, int *cel_atual);
void gerar_valor_bf(FILE *f, int cel, int valor, int *cel_atual, bool divisao, char sinal);
void gerar_char_utf8_bf(FILE *file, wchar_t wc, int *cel_atual);
void gerar_texto_utf8_bf(FILE *file, const wchar_t* texto, int *cel_atual);
void gerar_codigo_bf(NO *raiz, FILE *file_bf, int *cel_atual, int *prox_cel_livre);


#endif