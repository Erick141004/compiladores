#include "arvore.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

NO* inserir_no_operacao(NO* esq, NO* dir, uint8_t operador){
    NO *novo = (NO *) malloc(sizeof(NO));
    novo->filho_esq = esq;
    novo->filho_dir = dir;
    novo->valor = (uint8_t *)malloc(sizeof(uint8_t) * 2);
    novo->valor[0] = operador;
    novo->valor[1] = '\0';
    novo->tipo = OP;

    if(esq) esq->no_pai = novo;
    if(dir) dir->no_pai = novo;

    return novo;
}

NO* encontrar_primeiro_atrib(NO *raiz){
    if(raiz == NULL)
        return NULL;
    else{
        if(raiz->tipo == ATRIB)
            return raiz;
        
        encontrar_primeiro_atrib(raiz->no_pai);
    }
}

NO* inserir_no_variavel(uint8_t *nome_var, TypeNode tipo){
    NO *novo = (NO *) malloc(sizeof(NO));
    novo->filho_esq = NULL;
    novo->filho_dir = NULL;
    novo->valor = (uint8_t *)malloc(sizeof(uint8_t) * (strlen(nome_var) + 1));
    strcpy(novo->valor, nome_var);
    novo->tipo = tipo;
    novo->no_pai = NULL;

    return novo;
}

NO* inserir_no_seq(NO* esq, NO* dir){
    NO *novo = (NO *) malloc(sizeof(NO));
    novo->filho_esq = esq;
    novo->filho_dir = dir;
    novo->tipo = SEQ;
    novo->valor = NULL;
    novo->no_pai = NULL;

    if (esq) esq->no_pai = novo;
    if (dir) dir->no_pai = novo;

    return novo;
}

void imprimir_arvore(NO* raiz, int nivel) {
    if (raiz == NULL) return;

    imprimir_arvore(raiz->filho_dir, nivel + 1);

    for (int i = 0; i < nivel; i++) printf("    ");
    
    if (raiz->tipo == VAR || raiz->tipo == NUM)
        printf("[VAL] %s\n", raiz->valor);
    else if (raiz->tipo == SEQ)
        printf("[SEQ ] %s\n", raiz->valor);
    else if (raiz->tipo == ATRIB)
        printf("[ATRIB ] %s\n", raiz->valor);
    else
        printf("[OP ] %s\n", raiz->valor);

    imprimir_arvore(raiz->filho_esq, nivel + 1);
}

void limpar_arvore(NO* raiz){
    if(raiz == NULL) return;

    limpar_arvore(raiz->filho_esq);
    limpar_arvore(raiz->filho_dir);
    
    if(raiz->valor != NULL)
        free(raiz->valor);
    
    free(raiz);
}

bool tem_filhos(NO* no){
    return (no->filho_esq == NULL && no->filho_dir == NULL &&
        (no->tipo == NUM || no->tipo == VAR));
}