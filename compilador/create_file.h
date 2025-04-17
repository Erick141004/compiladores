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
void gerar_codigo(NO *raiz, FILE* assembly, LISTA *data, int *valor_temp);

#endif