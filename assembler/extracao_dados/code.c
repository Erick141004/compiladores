#include "code.h"
#include "../estrutura_de_dados/lista.h"
#include "data.h"

CODE* criar_code(uint8_t *content, int *start_index, long file_size, LISTA *l_data){
    CODE* code = (CODE *)malloc(sizeof(CODE));

    if(code == NULL){
        printf("ERRO: Nao foi possivel armazenar code\n");
        return NULL;
    }

    code->instrucao = (uint8_t*)pegar_palavra(content, file_size, *start_index);
    //printf("Nome variavel: %s\n", code->instrucao);
    
    *start_index += strlen((const char*)code->instrucao) + 1;

    if(strcmp("HLT", (const char*)code->instrucao) == 0 || strcmp("NOT",(const char*) code->instrucao) == 0){
        code->data = NULL;
        code->index_jump = -1;
        code->tem_dois_bytes = false;
    } else {
        char* variable_name = (char*)pegar_palavra(content, file_size, *start_index);
        DATA* data = (DATA*)buscar_no(l_data, variable_name, Data);

        if(data){
            code->data = data;
            code->index_jump = -1;
            code->tem_dois_bytes = true;
            *start_index += strlen((const char*)variable_name) + 1;
        } else if(strcmp("JMP", (const char*)code->instrucao) == 0 || strcmp("JZ", (const char*)code->instrucao) == 0 || strcmp("JN", (const char*)code->instrucao) == 0){
            code->data = NULL;
            code->index_jump = atoi(variable_name);
            code->tem_dois_bytes = true;
            *start_index += strlen((const char*)variable_name) + 1;
        } else {
            printf("\nERRO: Váriavel não definida em uso\n");
            return NULL;
        }
    }

    return code;
}

//TODO: fazer essa funcao retornar um valor para tratar erros
int ler_code(uint8_t *content, int *start_index, long file_size, LISTA *l_code, LISTA *l_data){
    int index_org = 0;

    while (*start_index < file_size) {
        char c = content[*start_index];

        switch (c) {
            case '.':
            //logica para pegar em qual indice de memoria vamos comecar a armazenar os nossos dados
                char *org = pegar_palavra(content, file_size, *start_index + 1); 
                
                *start_index += strlen((const char*)org);
                *start_index = pular_espaco(content, file_size, *start_index + 1);
                char *value_org = pegar_palavra(content, file_size, *start_index);
                index_org = atoi(value_org);

                *start_index = pular_linha(content, file_size, *start_index);
                break;
            case '\n':
                (*start_index)++;
                break;
            case ';':
                *start_index = pular_linha(content, file_size, *start_index);
                break;
            case ' ':
                *start_index = pular_espaco(content, file_size, *start_index);
                break;
            case '\0':
                return index_org;
            default:
                CODE* code = criar_code(content, start_index, file_size, l_data);
                if (code) {
                    adicionar_no(l_code, code, Code);
                }
                break;
        }
    }

    return index_org;
}