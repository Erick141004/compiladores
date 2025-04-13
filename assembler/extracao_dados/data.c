#include "data.h"
#include "../interface/interface.h"
#include "../estrutura_de_dados/lista.h"

DATA* criar_data(uint8_t* content, int* index_inicial, long file_size){
    DATA *data = (DATA *)malloc(sizeof(DATA));
    
    data->nome = (uint8_t*)pegar_palavra(content, file_size, *index_inicial);
    
    *index_inicial += strlen((const char*)data->nome) + 1;
    data->tipo_variavel = (uint8_t*)pegar_palavra(content, file_size, *index_inicial);

    *index_inicial += strlen((const char*)data->tipo_variavel) + 1;
    char* valor_str = pegar_palavra(content, file_size, *index_inicial);

    if(strcmp(valor_str, "?") == 0){
        data->valor = 0;
    } else {
        data->valor = (uint8_t)atoi(valor_str);
    }

    data->stored_index = -1;

    *index_inicial += strlen((const char*)valor_str) + 1;

    return data;
}

//TODO: fazer essa funcao retornar um valor para tratar erros
int ler_data(uint8_t* content, int* index_inicial, long file_size, LISTA* l) {
    int size_data = 0;
    
    while (*index_inicial < file_size) {
        char c = content[*index_inicial];

        switch (c) {
            case '.':
                (*index_inicial)--;
                return size_data;
            case '\n':
                (*index_inicial)++;
                break;
            case ';':
                *index_inicial = pular_linha(content, file_size, *index_inicial);
                break;
            case ' ':
                *index_inicial = pular_espaco(content, file_size, *index_inicial);
                break;
            case '\0':
                return 0;
            default:
                DATA* data = criar_data(content, index_inicial, file_size);
                if (data) {
                    adicionar_no(l, data, Data);
                    size_data++;
                }
                break;
        }
    }

    return size_data;
}