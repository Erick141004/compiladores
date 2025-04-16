#ifndef CODIFICADOR_H
#define CODIFICADOR_H

#include <stdint.h>
#include <stdbool.h>

typedef struct data
{
    uint8_t *nome_variavel;
    uint8_t *tipo_variavel;
    uint8_t *valor;
    bool expressao;
} DATA;

typedef struct code
{
    uint8_t *instrucao;
} CODE;

DATA *criar_data(uint8_t *nome, uint8_t *tipo_variavel, uint8_t *valor, bool expressao);
void limpar_data(DATA* data);

#endif