#include "tokens.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

void pular_espacos(uint8_t *content, int *pos_atual){
    while(content[*pos_atual] == ' ' || content[*pos_atual] == '\t' || content[*pos_atual] == '\n'){
        (*pos_atual)++;
    }
}

Token proximo_token(uint8_t *content, int *pos_atual){
    pular_espacos(content, pos_atual);
    char c = content[*pos_atual];
    
    Token prox_token; 

    if(c == '\0'){
        prox_token.tipo = TK_ENDFILE;
        strcpy(prox_token.lexema, "EOF");
        return prox_token;
    }

    if(isalpha(c)){
        prox_token.tipo = TK_STR;
        return prox_token;
    }

    if (isdigit(c) || (c == '-' && isdigit(content[*pos_atual + 1]))) {
        prox_token.tipo = number();
        return;
    }

    switch (c)
    {
        case '=':
            prox_token.tipo = TK_ATRIBUICAO;
            strcpy(prox_token.lexema, "=");
            (*pos_atual)++;
            break;
        case '+':
            prox_token.tipo = TK_SOMA;
            strcpy(prox_token.lexema, "+");
            (*pos_atual)++;
            break;
        case '-':
            prox_token.tipo = TK_SUB;
            strcpy(prox_token.lexema, "-");
            (*pos_atual)++;
            break;
        case '*':
            prox_token.tipo = TK_MULT;
            strcpy(prox_token.lexema, "*");
            (*pos_atual)++;
            break;
        case '/':
            prox_token.tipo = TK_DIV;
            strcpy(prox_token.lexema, "/");
            (*pos_atual)++;
            break;
        case '(':
            prox_token.tipo = TK_EPAREN;
            strcpy(prox_token.lexema, "(");
            (*pos_atual)++;
            break;
        case ')':
            prox_token.tipo = TK_DPAREN;
            strcpy(prox_token.lexema, ")");
            (*pos_atual)++;
            break;
        case '\"':
            prox_token.tipo = TK_ASPAS;
            strcpy(prox_token.lexema, "\"");
            (*pos_atual)++;
            break;
        case ':':
            prox_token.tipo = TK_DOISPONTOS;
            strcpy(prox_token.lexema, ":");
            (*pos_atual)++;
            break;
        default:
            prox_token.tipo = TK_DESCON;
            prox_token.lexema[0] = c;
            prox_token.lexema[1] = '\0';
            (*pos_atual)++;
            break;
    }

    return prox_token;
}   

void consumir_token(TokenType esperado, Token *token_atual, uint8_t *content, int *pos_atual){
    if(esperado == token_atual->tipo){
        *token_atual = proximo_token(content, pos_atual);
    } else {
        fprintf(stderr, "Erro de sintaxe: esperava token do tipo %d, mas encontrou %d (\"%s\")\n",
                esperado, token_atual->tipo, token_atual->lexema);
        exit(EXIT_FAILURE);
    }
}