#ifndef CREATE_FILE_COMPILER_H
#define CREATE_FILE_COMPILER_H

#include "lista.h"
#include "arvore.h"
#include "codificador.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void criar_arquivo(LISTA *lista_data, NO *raiz);
void gerar_data(LISTA *lista_data, FILE* assembly);
void gerar_codigo(NO *raiz, FILE* assembly, LISTA*data, int *valor_temp, int *qtd_linhas, bool *ja_computou);
void escrever_valor(FILE *assembly, NO *raiz, int valor_temp, NO* filho, int *qtd_linhas, LISTA *lista);
int gerar_multiplicacao(FILE *assembly, int *qtd_linhas);
int gerar_subtracao(FILE *assembly, int *qtd_linhas);

#endif