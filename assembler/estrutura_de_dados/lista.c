#include "lista.h"
#include "../extracao_dados/code.h"
#include "../extracao_dados/data.h"

LISTA* criar_lista(TIPO tipo){
    LISTA *l = (LISTA*)malloc(sizeof(LISTA));
    l->conteudo = NULL;
    l->tipo = tipo;
    l->prox = NULL;

    return l;
}

void adicionar_no(LISTA *l, void *conteudo, TIPO tipo){
    if(l->conteudo == NULL){
        l->conteudo = conteudo;
        l->tipo = tipo;
        l->prox = NULL;
        return;
    }

    if(l->prox != NULL)
        adicionar_no(l->prox, conteudo, tipo);
    else {
        LISTA *novo_no = (LISTA*)malloc(sizeof(LISTA));

        if(!novo_no){
            printf("Não foi possivel alocar a memoria para um novo nó");
            return;
        }

        novo_no->conteudo = conteudo;
        novo_no->tipo = tipo;
        novo_no->prox = NULL;
        l->prox = novo_no;
        return;
    }

}

void* buscar_no(LISTA *l, void *conteudo, TIPO tipo){
    LISTA *l_aux = l;
    
    while(l_aux != NULL){
        switch (tipo) {
            case Data:
                DATA *data = (DATA*)l_aux->conteudo;
                char* data_compare = (char*) conteudo;
                if(strcmp((const char*)data->nome, data_compare) == 0){
                    return data;
                }
            default:
                break;
        }

        l_aux = l_aux->prox;
    }

    return NULL;
}

void imprimir_lista(LISTA *l, TIPO tipo){
    LISTA *l_aux = l;

    if(tipo == Data)
        printf("Imprimindo DATA:\n\n");
    else 
        printf("Imprimindo CODE:\n\n");

    while(l_aux != NULL){
        switch (tipo) {
            case Data:
                DATA *data = (DATA*)l_aux->conteudo;
                printf("Nome variavel: %s - Tipo variavel: %s - Valor: %d\n", data->nome, data->tipo_variavel, data->valor);
                break;
            case Code:
                CODE *code = (CODE*)l_aux->conteudo;

                if(strcmp("HLT", (const char*)code->instrucao) == 0 || strcmp("NOT",(const char*) code->instrucao) == 0){
                    printf("Instrucao: %s\n", code->instrucao);
                } else{
                    printf("Instrucao: %s - Apontando para a variavel: %s\n", code->instrucao, code->data->nome);
                }
                break;
            default:
                break;
        }
        l_aux = l_aux->prox;
    }

    return;
}

void deletar_lista(LISTA *l){
    while(l != NULL){
        LISTA *l_aux = l;
        l = l->prox; 

        if(l_aux->conteudo != NULL){
            free(l_aux->conteudo);
        }

        free(l_aux);
    }

    return;
}