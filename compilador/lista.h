#ifndef LISTA_COMPILER_H
#define LISTA_COMPILER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct LISTA{
    void* conteudo;
    struct LISTA *prox;
} LISTA;

LISTA* criar_lista();

void adicionar_no(LISTA*, void*);
void* buscar_no(LISTA*, void*);
void imprimir_lista(LISTA*);
void deletar_lista(LISTA*);

#endif