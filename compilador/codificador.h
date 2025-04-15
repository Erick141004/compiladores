#ifndef CODIFICADOR_H
#define CODIFICADOR_H

#include <stdint.h>
#include <stdbool.h>

typedef struct data
{
    uint8_t *nome_variavel;
    uint8_t *tipo_variavel;
    int valor;
    bool expressao;
} DATA;

typedef struct code
{
    uint8_t *instrucao;
} CODE;




#endif