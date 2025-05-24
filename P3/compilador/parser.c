#include "tokens.h"
#include <string.h>
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

void error(const char *msg) {
    fprintf(stderr, "Erro: %s\n", msg);
    exit(EXIT_FAILURE);
}

NO* parse_expressao2(wchar_t *content, int *pos_atual, Token *token){
    Token t = *token;
    
    if(token->tipo == TK_NUM){
        //printf("LDC %s\n", token->lexema);
        consumir_token(TK_NUM, token, content, pos_atual);
        return inserir_no_variavel(t.lexema, NUM);
    } else if(token->tipo == TK_VAR){
        //printf("LDA %s\n", token->lexema);
        consumir_token(TK_VAR, token, content, pos_atual);
        return inserir_no_variavel(t.lexema, VAR);
    } else if(token->tipo == TK_EPAREN){
        consumir_token(TK_EPAREN, token, content, pos_atual);
        NO* no = parse_expressao(content, pos_atual, token);
        consumir_token(TK_DPAREN, token, content, pos_atual);
        return no;
    } else{
        //error("erro ao fazer o parser - Token inesperado");
        return NULL;
    }
}

NO* parse_expressao1(wchar_t *content, int *pos_atual, Token *token){
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

NO* parse_expressao(wchar_t *content, int *pos_atual, Token *token){
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

NO* parse_atribuicao(wchar_t *content, int *pos_atual, Token *token){
    Token atual = *token;

    NO* no_raiz = inserir_no_variavel(atual.lexema, ATRIB);

    consumir_token(TK_VAR, token, content, pos_atual);
    consumir_token(TK_ATRIBUICAO, token, content, pos_atual);
    //printf("; Processando atribuição para %s\n", atual.lexema);
    no_raiz->filho_esq = parse_expressao(content, pos_atual, token);
    no_raiz->filho_esq->no_pai = no_raiz;

    // DATA *d;

    // if(tem_filhos(no_raiz->filho_esq)){
    //     d = criar_data(atual.lexema, "DB", no_raiz->filho_esq->valor, false);
    // } else {
    //     d = criar_data(atual.lexema, "DB", NULL, true);
    // }

    //adicionar_no(variaveis, d);

    //printf("STA %s\n", atual.lexema);

    return no_raiz;
}
