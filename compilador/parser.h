#ifndef PARSER_H
#define PARSER_H

#include "tokens.h"
#include <stdint.h>

void parse_program(uint8_t *content, int *pos_atual, Token *token);
void parse_header(uint8_t *content, int *pos_atual, Token *token);
void parse_res(uint8_t *content, int *pos_atual, Token *token);
void parse_atribuicao(uint8_t *content, int *pos_atual, Token *token);
void parse_statement(uint8_t *content, int *pos_atual, Token *token);
void parse_expressao(uint8_t *content, int *pos_atual, Token *token);
void parse_expressao1(uint8_t *content, int *pos_atual, Token *token);
void parse_expressao2(uint8_t *content, int *pos_atual, Token *token);

#endif