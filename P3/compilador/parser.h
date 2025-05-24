#ifndef PARSER_H
#define PARSER_H

#include "arvore.h"
#include "tokens.h"
#include <stdint.h>
#include <wctype.h>
#include <wchar.h>

NO* parse_atribuicao(wchar_t *content, int *pos_atual, Token *token);
NO* parse_expressao(wchar_t *content, int *pos_atual, Token *token);
NO* parse_expressao1(wchar_t *content, int *pos_atual, Token *token);
NO* parse_expressao2(wchar_t *content, int *pos_atual, Token *token);

#endif