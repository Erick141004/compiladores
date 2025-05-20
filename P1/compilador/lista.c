#include "lista.h"
#include "codificador.h"

LISTA* criar_lista(){
    LISTA *l = (LISTA*)malloc(sizeof(LISTA));
    l->conteudo = NULL;
    l->prox = NULL;

    return l;
}

void adicionar_no(LISTA *l, void *conteudo){
    if(l->conteudo == NULL){
        l->conteudo = conteudo;
        l->prox = NULL;

        return;
    }

    if(l->prox != NULL)
        adicionar_no(l->prox, conteudo);
    else {
        LISTA *novo_no = (LISTA*)malloc(sizeof(LISTA));

        if(!novo_no){
            printf("Não foi possivel alocar a memoria para um novo nó");
            return;
        }

        novo_no->conteudo = conteudo;
        novo_no->prox = NULL;
        l->prox = novo_no;

        return;
    }
}

void* buscar_no(LISTA *l, void *conteudo){
    LISTA *l_aux = l;
    
    while(l_aux != NULL){
        DATA *data = (DATA*)l_aux->conteudo;
        char* data_compare = (char*) conteudo;
        //printf("Data atual: %s ---- Data comparado: %s\n", data->nome, data_compare);
        if(strcmp((const char*)data->nome_variavel, data_compare) == 0){
            return data;
        }
        
        l_aux = l_aux->prox;
    }

    return NULL;
}

void imprimir_lista(LISTA *l){
    LISTA *l_aux = l;

    while(l_aux != NULL){
        DATA *data = (DATA*)l_aux->conteudo;
        printf("Nome variavel: %s - Tipo variavel: %s - Valor: %s\n", data->nome_variavel, data->tipo_variavel, data->valor);
 
        l_aux = l_aux->prox;
    }

    return;
}

void deletar_lista(LISTA *l){
    while(l != NULL){
        LISTA *l_aux = l;
        l = l->prox; 

        if(l_aux->conteudo != NULL){
            DATA *d = (DATA *) l_aux->conteudo;
            limpar_data(d);
        }

        free(l_aux);
    }

    return;
}