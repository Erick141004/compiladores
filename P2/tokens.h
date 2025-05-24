#ifndef TOKENS_H 
#define TOKENS_H

#include <stdint.h>

typedef enum{
    //palavras reservadas
    TK_PROG, TK_INICIO, TK_FIM,
    TK_IF, TK_ELSE, TK_ELSEIF,
    TK_WHILE, TK_DO, TK_FOR,
    TK_FUNCAO, TK_INT, TK_FLOAT, TK_CHAR, TK_VOID,

    //tratamento variaveis
    TK_VAR, TK_NUM,
    TK_ATRIBUICAO,

    //operacoes
    TK_SOMA, TK_SUB, TK_MULT, TK_DIV,
    TK_MAIOR, TK_MENOR, TK_MAIORIGUAL, TK_MENORIGUAL, TK_IGUAL, TK_DIFERENTE,
    TK_AND, TK_OR, TK_NOT,

    //simbolos
    TK_EPAREN, TK_DPAREN,
    TK_ECHAVE, TK_DCHAVE,
    TK_PONTOVIRGULA, TK_VIRGULA, TK_DOISPONTOS,
    TK_ASPAS,
    TK_NOVALINHA,

    //tratamento
    TK_ENDFILE, TK_DESCON, TK_ERROR
} TokenType;

typedef struct{
    TokenType tipo;
    char lexema[64];
} Token;

void pular_espacos(uint8_t*, int*);
Token ler_numero(uint8_t*, int*);
Token identificador_ou_reservada(uint8_t*, int*);
Token proximo_token(uint8_t*, int*);
void consumir_token(TokenType, Token*, uint8_t*, int*);

#endif