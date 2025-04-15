#include "tokens.h"
#include <string.h>
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

void error(const char *msg) {
    fprintf(stderr, "Erro: %s\n", msg);
    exit(EXIT_FAILURE);
}

void parse_expressao2(uint8_t *content, int *pos_atual, Token *token){
    if(token->tipo == TK_NUM){
        printf("LDC %s\n", token->lexema);
        consumir_token(TK_NUM, token, content, pos_atual);
    } else if(token->tipo == TK_VAR){
        printf("LDA %s\n", token->lexema);
        consumir_token(TK_VAR, token, content, pos_atual);
    } else if(token->tipo == TK_EPAREN){
        consumir_token(TK_EPAREN, token, content, pos_atual);
        parse_expressao(content, pos_atual, token);
        consumir_token(TK_DPAREN, token, content, pos_atual);
    } else{
        error("erro ao fazer o parser - Token inesperado");
    }
}

void parse_expressao1(uint8_t *content, int *pos_atual, Token *token){
    parse_expressao2(content, pos_atual, token);

    while(token->tipo == TK_MULT || token->tipo == TK_DIV){
        TokenType op = token->tipo;
        
        consumir_token(op, token, content, pos_atual);
        
        if (op == TK_MULT)
            printf("MUL %s\n", token->lexema);
        else
            printf("DIV %s\n", token->lexema);

        parse_expressao2(content, pos_atual, token);

    }
}  

void parse_expressao(uint8_t *content, int *pos_atual, Token *token){
    parse_expressao1(content, pos_atual, token);

    while(token->tipo == TK_SOMA || token->tipo == TK_SUB){
        TokenType op = token->tipo;
        consumir_token(op, token, content, pos_atual);
        
        if (op == TK_SOMA)
            printf("SOMA %s\n", token->lexema);
        else
            printf("SUB %s\n", token->lexema);

        parse_expressao1(content, pos_atual, token);
    }
}

void parse_atribuicao(uint8_t *content, int *pos_atual, Token *token){
    Token atual = *token;
    consumir_token(TK_VAR, token, content, pos_atual);
    consumir_token(TK_ATRIBUICAO, token, content, pos_atual);
    printf("; Processando atribuição para %s\n", atual.lexema);
    parse_expressao(content, pos_atual, token);
    printf("STA %s\n", atual.lexema);
}

void parse_statement(uint8_t *content, int *pos_atual, Token *token){
    parse_atribuicao(content, pos_atual, token);

    while(token->tipo == TK_NOVALINHA){
        consumir_token(TK_NOVALINHA, token, content, pos_atual);
        if(token->tipo == TK_VAR){
            parse_atribuicao(content, pos_atual, token);
        }
    }
}

void parse_res(uint8_t *content, int *pos_atual, Token *token){
    consumir_token(TK_RES, token, content, pos_atual);
    consumir_token(TK_ATRIBUICAO, token, content, pos_atual);
    printf("; Processando instrução RES\n");
    parse_expressao(content, pos_atual, token);
    printf("STA RES\n");
}

void parse_header(uint8_t *content, int *pos_atual, Token *token){
    consumir_token(TK_PROG, token, content, pos_atual);
    pular_espacos(content, pos_atual);
    consumir_token(TK_ASPAS, token, content, pos_atual);

    if (token->tipo != TK_VAR)
        error("Esperava identificador no label do programa.");
    
    printf("; Definindo o programa: %s\n", token->lexema);
    
    consumir_token(TK_VAR, token, content, pos_atual);
    consumir_token(TK_ASPAS, token, content, pos_atual);
    pular_espacos(content, pos_atual);
    consumir_token(TK_DOISPONTOS, token, content, pos_atual);
    consumir_token(TK_NOVALINHA, token, content, pos_atual);
}

void parse_program(uint8_t *content, int *pos_atual, Token *token){
    parse_header(content, pos_atual, token);
    consumir_token(TK_INICIO, token, content, pos_atual);
    consumir_token(TK_NOVALINHA, token, content, pos_atual);
    parse_statement(content, pos_atual, token);
    parse_res(content, pos_atual, token);
    consumir_token(TK_NOVALINHA, token, content, pos_atual);
    consumir_token(TK_FIM, token, content, pos_atual);
}