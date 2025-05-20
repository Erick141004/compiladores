#include "tokens.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void pular_espacos(wchar_t *content, int *pos_atual){
    while(content[*pos_atual] == ' ' || content[*pos_atual] == '\t'){
        (*pos_atual)++;
    }
}

Token ler_numero(wchar_t *content, int *pos_atual){
    Token tk;
    int start = *pos_atual;

    if(content[*pos_atual] == '-')
        (*pos_atual)++;

    while(iswdigit(content[*pos_atual])){
        (*pos_atual)++;
    }

    int len = *pos_atual - start;
    wcsncpy(tk.lexema, content + start, len);
    tk.lexema[len] = L'\0';
    tk.tipo = TK_NUM;

    return tk;
}

Token identificador_ou_reservada(wchar_t *content, int *pos_atual){
    Token tk;

    int start = *pos_atual;

    while(iswalpha(content[*pos_atual])){
        (*pos_atual)++;
    }

    int len = *pos_atual - start;
    wcsncpy(tk.lexema, content + start, len);
    tk.lexema[len] = L'\0';
    
    tk.tipo = TK_VAR;
    
    return tk;
}

Token proximo_token(wchar_t *content, int *pos_atual){
    pular_espacos(content, pos_atual);
    wchar_t c = content[*pos_atual];
    
    Token prox_token;

    if(c == '\0'){
        prox_token.tipo = TK_ENDFILE;
        wcscpy(prox_token.lexema, L"EOF");
        return prox_token;
    }

    if(iswalpha(c)){
        prox_token = identificador_ou_reservada(content, pos_atual);
        return prox_token;
    }

    if (iswdigit(c) || (c == '-' && iswdigit(content[*pos_atual + 1]))) {
        prox_token = ler_numero(content, pos_atual);
        return prox_token;
    }

    switch (c)
    {
        case '=':
            prox_token.tipo = TK_ATRIBUICAO;
            wcscpy(prox_token.lexema, L"=");
            (*pos_atual)++;
            break;
        case '+':
            prox_token.tipo = TK_SOMA;
            wcscpy(prox_token.lexema, L"+");
            (*pos_atual)++;
            break;
        case '-':
            prox_token.tipo = TK_SUB;
            wcscpy(prox_token.lexema, L"-");
            (*pos_atual)++;
            break;
        case '*':
            prox_token.tipo = TK_MULT;
            wcscpy(prox_token.lexema, L"*");
            (*pos_atual)++;
            break;
        case '/':
            prox_token.tipo = TK_DIV;
            wcscpy(prox_token.lexema, L"/");
            (*pos_atual)++;
            break;
        case '(':
            prox_token.tipo = TK_EPAREN;
            wcscpy(prox_token.lexema, L"(");
            (*pos_atual)++;
            break;
        case ')':
            prox_token.tipo = TK_DPAREN;
            wcscpy(prox_token.lexema, L")");
            (*pos_atual)++;
            break;
        default:
            prox_token.tipo = TK_DESCON;
            prox_token.lexema[0] = c;
            prox_token.lexema[1] = L'\0';
            (*pos_atual)++;
            break;
    }

    return prox_token;
}   

void consumir_token(TokenType esperado, Token *token_atual, wchar_t *content, int *pos_atual){
    if(esperado == token_atual->tipo){
        *token_atual = proximo_token(content, pos_atual);
    } else {
        fwprintf(stderr, L"Erro de sintaxe: esperava token do tipo %d, mas encontrou %d (\"%ls\")\n",
            esperado, token_atual->tipo, token_atual->lexema);
        exit(EXIT_FAILURE);
    }
}