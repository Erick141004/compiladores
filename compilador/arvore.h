#ifndef ARVORE_H
#define ARVORE_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {SEQ, VAR, NUM, OP, ATRIB} TypeNode;

typedef struct No{
    TypeNode tipo;
    uint8_t *valor;
    struct No *filho_esq;
    struct No *filho_dir;
    struct No *no_pai;
} NO;

NO* inserir_no_operacao(NO* dir, NO* esq, uint8_t operador);
NO* inserir_no_variavel(uint8_t *nome_var, TypeNode tipo);
NO* inserir_no_seq(NO* esq, NO* dir);
NO* encontrar_primeiro_atrib(NO *raiz);
void imprimir_arvore(NO *raiz, int nivel); 
void limpar_arvore(NO* raiz);
bool tem_filhos(NO* no);

#endif