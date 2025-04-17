#ifndef PARSER_H
#define PARSER_H

#include "arvore.h"
#include "tokens.h"
#include "lista.h"
#include <stdint.h>

NO* parse_program(uint8_t *content, int *pos_atual, Token *token, LISTA *variaveis);
uint8_t* parse_header(uint8_t *content, int *pos_atual, Token *token);
NO* parse_res(uint8_t *content, int *pos_atual, Token *token, LISTA *variaveis);
NO* parse_atribuicao(uint8_t *content, int *pos_atual, Token *token, LISTA *variaveis);
NO* parse_statement(uint8_t *content, int *pos_atual, Token *token, LISTA *variaveis);
NO* parse_expressao(uint8_t *content, int *pos_atual, Token *token);
NO* parse_expressao1(uint8_t *content, int *pos_atual, Token *token);
NO* parse_expressao2(uint8_t *content, int *pos_atual, Token *token);

#endif