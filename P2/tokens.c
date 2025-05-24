#include "tokens.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void pular_espacos(uint8_t *content, int *pos_atual){
    while(content[*pos_atual] == ' ' || content[*pos_atual] == '\t'){
        (*pos_atual)++;
    }
}

Token ler_numero(uint8_t *content, int *pos_atual){
    Token tk;
    int start = *pos_atual;

    if(content[*pos_atual] == '-')
        (*pos_atual)++;

    while(isdigit(content[*pos_atual])){
        (*pos_atual)++;
    }

    int len = *pos_atual - start;
    strncpy(tk.lexema, (char*)(content + start), len);
    tk.lexema[len] = '\0';
    tk.tipo = TK_NUM;

    return tk;
}

Token identificador_ou_reservada(uint8_t *content, int *pos_atual){
    Token tk;
    int start = *pos_atual;

    while(isalpha(content[*pos_atual])){
        (*pos_atual)++;
    }

    int len = *pos_atual - start;
    strncpy(tk.lexema, (char*)(content + start), len);
    tk.lexema[len] = '\0';

    if(strcmp(tk.lexema, "PROGRAMA") == 0) tk.tipo = TK_PROG;
    else if(strcmp(tk.lexema, "INICIO") == 0) tk.tipo = TK_INICIO;
    else if(strcmp(tk.lexema, "FIM") == 0) tk.tipo = TK_FIM;
    else if(strcmp(tk.lexema, "if") == 0) tk.tipo = TK_IF;
    else if(strcmp(tk.lexema, "else") == 0) tk.tipo = TK_ELSE;
    else if(strcmp(tk.lexema, "else if") == 0) tk.tipo = TK_ELSEIF;
    else if(strcmp(tk.lexema, "while") == 0) tk.tipo = TK_WHILE;
    else if(strcmp(tk.lexema, "do") == 0) tk.tipo = TK_DO;
    else if(strcmp(tk.lexema, "for") == 0) tk.tipo = TK_FOR;
    else if(strcmp(tk.lexema, "funcao") == 0) tk.tipo = TK_FUNCAO;
    else if(strcmp(tk.lexema, "int") == 0) tk.tipo = TK_INT;
    else if(strcmp(tk.lexema, "float") == 0) tk.tipo = TK_FLOAT;
    else if(strcmp(tk.lexema, "char") == 0) tk.tipo = TK_CHAR;
    else if(strcmp(tk.lexema, "void") == 0) tk.tipo = TK_VOID;
    else tk.tipo = TK_VAR;

    return tk;
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
        return identificador_ou_reservada(content, pos_atual);
    }

    if(isdigit(c) || (c == '-' && isdigit(content[*pos_atual + 1]))){
        return ler_numero(content, pos_atual);
    }

    char next = content[*pos_atual + 1];
    if(c == '&' && next == '&') {
        prox_token.tipo = TK_AND;
        strcpy(prox_token.lexema, "&&");
        *pos_atual += 2;
        return prox_token;
    } else if(c == '|' && next == '|') {
        prox_token.tipo = TK_OR;
        strcpy(prox_token.lexema, "||");
        *pos_atual += 2;
        return prox_token;
    } else if(c == '=' && next == '=') {
        prox_token.tipo = TK_IGUAL;
        strcpy(prox_token.lexema, "==");
        *pos_atual += 2;
        return prox_token;
    } else if(c == '!' && next == '=') {
        prox_token.tipo = TK_DIFERENTE;
        strcpy(prox_token.lexema, "!=");
        *pos_atual += 2;
        return prox_token;
    } else if(c == '>' && next == '=') {
        prox_token.tipo = TK_MAIORIGUAL;
        strcpy(prox_token.lexema, ">=");
        *pos_atual += 2;
        return prox_token;
    } else if(c == '<' && next == '=') {
        prox_token.tipo = TK_MENORIGUAL;
        strcpy(prox_token.lexema, "<=");
        *pos_atual += 2;
        return prox_token;
    }

    switch(c){
        case '=': prox_token.tipo = TK_ATRIBUICAO; 
	  	 	strcpy(prox_token.lexema, "="); 
	 	 	break;
        case '+': prox_token.tipo = TK_SOMA; 
	  	 	strcpy(prox_token.lexema, "+"); 
	 	 	break;
        case '-': prox_token.tipo = TK_SUB; 
	  	 	strcpy(prox_token.lexema, "-"); 
	 	 	break;
        case '*': prox_token.tipo = TK_MULT; 
	  	 	strcpy(prox_token.lexema, "*"); 
	 	 	break;
        case '/': prox_token.tipo = TK_DIV; 
	  	 	strcpy(prox_token.lexema, "/"); 
	 	 	break;
        case '(': prox_token.tipo = TK_EPAREN; 
	  	 	strcpy(prox_token.lexema, "("); 
	 	 	break;
        case ')': prox_token.tipo = TK_DPAREN; 
	  	 	strcpy(prox_token.lexema, ")"); 
	 	 	break;
        case '{': prox_token.tipo = TK_ECHAVE; 
	  	 	strcpy(prox_token.lexema, "{"); 
	 	 	break;
        case '}': prox_token.tipo = TK_DCHAVE; 
	  	 	strcpy(prox_token.lexema, "}"); 
	 	 	break;
        case ';': prox_token.tipo = TK_PONTOVIRGULA; 
	  	 	strcpy(prox_token.lexema, ";"); 
	 	 	break;
        case ',': prox_token.tipo = TK_VIRGULA; 
	  	 	strcpy(prox_token.lexema, ","); 
	 	 	break;
        case ':': prox_token.tipo = TK_DOISPONTOS; 
	  	 	strcpy(prox_token.lexema, ":"); 
	 	 	break;
        case '"': prox_token.tipo = TK_ASPAS; 
	  	 	strcpy(prox_token.lexema, "\""); 
	 	 	break;
        case '\n': prox_token.tipo = TK_NOVALINHA; 
	  	 	strcpy(prox_token.lexema, "\n"); 
	 	 	break;
        default:
            prox_token.tipo = TK_DESCON;
            prox_token.lexema[0] = c;
            prox_token.lexema[1] = '\0';
    }

    (*pos_atual)++;
    return prox_token;
}

void consumir_token(TokenType esperado, Token *token_atual, uint8_t *content, int *pos_atual){
    if(esperado == token_atual->tipo){
        *token_atual = proximo_token(content, pos_atual);
    } else {
        fprintf(stderr, "Erro: esperava token %d, encontrou %d (\"%s\")\n", esperado, token_atual->tipo, token_atual->lexema);
        exit(EXIT_FAILURE);
    }
}
