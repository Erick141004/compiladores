#include "tokens.h"
#include <string.h>
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"
#include "lista.h"
#include "codificador.h"

void error(const char *msg) {
    fprintf(stderr, "Erro: %s\n", msg);
    exit(EXIT_FAILURE);
}

NO* parse_expressao2(uint8_t *content, int *pos_atual, Token *token){
    Token t = *token;
    
    if(token->tipo == TK_NUM){
        printf("LDC %s\n", token->lexema);
        consumir_token(TK_NUM, token, content, pos_atual);
        return inserir_no_variavel(t.lexema, NUM);
    } else if(token->tipo == TK_VAR){
        printf("LDA %s\n", token->lexema);
        consumir_token(TK_VAR, token, content, pos_atual);
        return inserir_no_variavel(t.lexema, VAR);
    } else if(token->tipo == TK_EPAREN){
        consumir_token(TK_EPAREN, token, content, pos_atual);
        NO* no = parse_expressao(content, pos_atual, token);
        consumir_token(TK_DPAREN, token, content, pos_atual);
        return no;
    } else{
        error("erro ao fazer o parser - Token inesperado");
        return NULL;
    }
}

NO* parse_expressao1(uint8_t *content, int *pos_atual, Token *token){
    NO* esq = parse_expressao2(content, pos_atual, token);

    while(token->tipo == TK_MULT || token->tipo == TK_DIV){
        TokenType op = token->tipo;
        
        consumir_token(op, token, content, pos_atual);
        NO* dir = parse_expressao2(content, pos_atual, token);

        NO *no_pai;
        if (op == TK_MULT)
            no_pai = inserir_no_operacao(esq, dir, '*');
        else
            no_pai = inserir_no_operacao(esq, dir, '/');

        esq = no_pai;
    }

    return esq;
}  

NO* parse_expressao(uint8_t *content, int *pos_atual, Token *token){
    NO* esq = parse_expressao1(content, pos_atual, token);

    while(token->tipo == TK_SOMA || token->tipo == TK_SUB){
        TokenType op = token->tipo;
        consumir_token(op, token, content, pos_atual);
        NO* dir = parse_expressao1(content, pos_atual, token);

        NO *no_pai;
        if (op == TK_SOMA)
            no_pai = inserir_no_operacao(esq, dir, '+');
        else
            no_pai = inserir_no_operacao(esq, dir, '-');

        esq = no_pai;
    }

    return esq;
}

NO* parse_atribuicao(uint8_t *content, int *pos_atual, Token *token, LISTA* variaveis){
    Token atual = *token;

    NO* no_raiz = inserir_no_variavel(atual.lexema, ATRIB);

    consumir_token(TK_VAR, token, content, pos_atual);
    consumir_token(TK_ATRIBUICAO, token, content, pos_atual);
    printf("; Processando atribuição para %s\n", atual.lexema);
    no_raiz->filho_esq = parse_expressao(content, pos_atual, token);
    no_raiz->filho_esq->no_pai = no_raiz;

    DATA *d;

    if(tem_filhos(no_raiz->filho_esq)){
        d = criar_data(atual.lexema, "DB", no_raiz->filho_esq->valor, false);
    } else {
        d = criar_data(atual.lexema, "DB", NULL, true);
    }

    adicionar_no(variaveis, d);

    printf("STA %s\n", atual.lexema);

    return no_raiz;
}

NO* parse_statement(uint8_t *content, int *pos_atual, Token *token, LISTA* variaveis){
    NO* raiz = parse_atribuicao(content, pos_atual, token, variaveis);

    while(token->tipo == TK_NOVALINHA){
        consumir_token(TK_NOVALINHA, token, content, pos_atual);
        if(token->tipo == TK_VAR){
            NO* prox = parse_atribuicao(content, pos_atual, token, variaveis);
            raiz = inserir_no_seq(raiz, prox);
        }
    }

    return raiz;
}

NO* parse_res(uint8_t *content, int *pos_atual, Token *token, LISTA* variaveis){
    NO* res = inserir_no_variavel("RES", ATRIB);

    consumir_token(TK_RES, token, content, pos_atual);
    consumir_token(TK_ATRIBUICAO, token, content, pos_atual);
    printf("; Processando instrução RES\n");

    res->filho_esq = parse_expressao(content, pos_atual, token);
    res->filho_esq->no_pai = res;

    DATA* d;

    if(tem_filhos(res->filho_esq)){
        d = criar_data("RES", "DB", res->filho_esq->valor, false);
    } else {
        d = criar_data("RES", "DB", NULL, true);
    }

    adicionar_no(variaveis, d);

    printf("STA RES\n");

    return res;
}

uint8_t* parse_header(uint8_t *content, int *pos_atual, Token *token){
    consumir_token(TK_PROG, token, content, pos_atual);
    pular_espacos(content, pos_atual);
    consumir_token(TK_ASPAS, token, content, pos_atual);

    if (token->tipo != TK_VAR)
        error("Esperava identificador no label do programa.");
    
    uint8_t *nome_programa = (uint8_t *)malloc(strlen(token->lexema) + 1);
    strcpy(nome_programa, token->lexema);

    printf("; Definindo o programa: %s\n", token->lexema);
    
    consumir_token(TK_VAR, token, content, pos_atual);
    consumir_token(TK_ASPAS, token, content, pos_atual);
    pular_espacos(content, pos_atual);
    consumir_token(TK_DOISPONTOS, token, content, pos_atual);
    consumir_token(TK_NOVALINHA, token, content, pos_atual);

    return nome_programa;
}

NO* parse_program(uint8_t *content, int *pos_atual, Token *token, LISTA *variaveis){
    uint8_t *nome = parse_header(content, pos_atual, token);
    consumir_token(TK_INICIO, token, content, pos_atual);
    consumir_token(TK_NOVALINHA, token, content, pos_atual);
    
    NO* no_atribuicao = parse_statement(content, pos_atual, token, variaveis);
    NO* no_res = parse_res(content, pos_atual, token, variaveis);
    
    consumir_token(TK_NOVALINHA, token, content, pos_atual);
    consumir_token(TK_FIM, token, content, pos_atual);

    NO* no_raiz = inserir_no_seq(no_atribuicao, no_res);
    no_raiz->valor = (uint8_t *)malloc(sizeof(uint8_t) * strlen(nome) + 1);
    strcpy(no_raiz->valor, nome);

    return no_raiz;
}