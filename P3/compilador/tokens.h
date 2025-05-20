#ifndef TOKENS_H 
#define TOKENS_H

#include <stdint.h>
#include <wctype.h>
#include <wchar.h>

typedef enum{ 
    TK_VAR, TK_ATRIBUICAO, TK_NUM,
    TK_SOMA, TK_MULT, TK_SUB, TK_DIV, 
    TK_EPAREN, TK_DPAREN,
    TK_ERROR, TK_ENDFILE, TK_ASPAS, TK_DESCON
} TokenType;

typedef struct{
    TokenType tipo;
    wchar_t lexema[64];
} Token;

void pular_espacos(wchar_t*, int*);
Token proximo_token(wchar_t*, int*);
void consumir_token(TokenType, Token*, wchar_t*, int*);

#endif