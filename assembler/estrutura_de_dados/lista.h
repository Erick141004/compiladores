#ifndef LISTA_H
#define LISTA_H

#include <stdlib.h>
#include <stdio.h>

typedef enum{
    Data,
    Code
} TIPO;

typedef struct LISTA{
    void* conteudo;
    TIPO tipo;
    struct LISTA *prox;
} LISTA;

LISTA* criar_lista(TIPO);

void adicionar_no(LISTA*, void*, TIPO);
void* buscar_no(LISTA*, void*, TIPO);
void imprimir_lista(LISTA*, TIPO);
void deletar_lista(LISTA*);

#endif