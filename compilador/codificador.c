#include "codificador.h"
#include <stdlib.h>
#include <string.h>

DATA *criar_data(uint8_t *nome, uint8_t *tipo_variavel, uint8_t* valor, bool expressao){
    DATA *data = (DATA*) malloc(sizeof(DATA));
    data->nome_variavel = (uint8_t *)malloc(sizeof(uint8_t) * (strlen(nome) + 1));
    strcpy(data->nome_variavel, nome);
    data->tipo_variavel = (uint8_t *)malloc(sizeof(uint8_t) * (strlen(tipo_variavel) + 1));
    strcpy(data->tipo_variavel, tipo_variavel);
    if(valor){
        data->valor = (uint8_t *)malloc(sizeof(uint8_t) * (strlen(valor) + 1));
        strcpy(data->valor, valor);
    } else {
        data->valor = NULL;
    }
    
    data->expressao = expressao;

    return data;
}

void limpar_data(DATA* data){
    free(data->valor);
    free(data->nome_variavel);
    free(data->tipo_variavel);
    
    return;
}