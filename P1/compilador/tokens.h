#ifndef TOKENS_H 
#define TOKENS_H

#include <stdint.h>

typedef enum{
    TK_PROG, TK_INICIO, TK_FIM, TK_RES,
    TK_VAR, TK_ATRIBUICAO, TK_NUM, TK_STR,
    TK_NOVALINHA, TK_SOMA, TK_MULT,
    TK_SUB, TK_DIV, TK_EPAREN, TK_DPAREN,
    TK_ERROR, TK_ENDFILE, TK_DOISPONTOS, TK_ASPAS, TK_DESCON
} TokenType;

typedef struct{
    TokenType tipo;
    char lexema[64];
} Token;

void pular_espacos(uint8_t*, int*);
Token proximo_token(uint8_t*, int*);
void consumir_token(TokenType, Token*, uint8_t*, int*);

#endif