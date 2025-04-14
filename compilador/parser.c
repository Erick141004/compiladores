#include "tokens.h"
#include "parser.h"

void parse_num(){
    
}

void parse_var(){
    
}

void parse_espacos(){
    
}

void parse_mult(){
    
}

void parse_adicao(){
    
}

void parse_expressao2(){
    
}

void parse_expressao1(){
    
}

void parse_expressao(){

}

void parse_atribuicao(){

}


void parse_statement(){
    
}

void parse_res(){
    
}

void parse_fim(){
    
}

void parse_inicio(){
    
}

void parse_header(){
    consumir_token(TK_PROG);
    white_spaces();
    consumir_token(TK_ASPAS);
    consumir_token(TK_STR);
    consumir_token(TK_ASPAS);
    white_spaces();
    consumir_token(TK_DOISPONTOS);
    consumir_token(TK_NOVALINHA);
}

void parse_program(){
    parse_header();
    parse_inicio();
    consumir_token(TK_NOVALINHA);
    parse_res();
    consumir_token(TK_NOVALINHA);
    parse_fim();
}