#ifndef CODE_H
#define CODE_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "interface.h"

typedef struct DATA DATA;
typedef struct LISTA LISTA;

typedef struct{
    uint8_t *instrucao;
    struct DATA *data; 
} CODE;

CODE* criar_code(uint8_t *content, int *start_index, long file_size, LISTA *l_data);
void ler_code(uint8_t *content, int *start_index, long file_size, LISTA *l_code, LISTA *l_data);

#endif