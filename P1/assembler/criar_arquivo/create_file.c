#include "create_file.h"
#include "../extracao_dados/code.h"
#include "../extracao_dados/data.h"
#include "../estrutura_de_dados/lista.h"

const Instrucao tabela_instrucao[] = {
    {"NOP", 0x00}, {"STA", 0x10}, {"LDA", 0x20}, {"ADD", 0x30},
    {"OR",  0x40}, {"AND", 0x50}, {"NOT", 0x60}, {"JMP", 0x80},
    {"JN",  0x90}, {"JZ",  0xA0}, {"HLT", 0xF0}
};

void creating_file(LISTA* l_code, int start_index_write, int length_data){
    FILE *file = fopen("programa.mem", "wb");
    int size = 516;

    if(file == NULL){
        printf("Não foi possivel criar o arquivo!");
        return;
    }

    uint8_t buffer[516] = {0};
    manipulating_file(l_code, buffer, size, start_index_write, length_data);

    fwrite(buffer, 1, size, file);

    fclose(file);
}

uint16_t pegar_local_jump(int posicao_jump, LISTA *l_code){
    LISTA *l_aux = l_code;
    int jump_bytes = 0;
    int cont = 0;

    while(l_aux != NULL && cont < posicao_jump){
        CODE *code = (CODE *) l_aux->conteudo; 

        if (code->tem_dois_bytes){
            jump_bytes += 2;
        } else {
            jump_bytes++;
        }

        cont++;
        l_aux = l_aux->prox;
    }

    return jump_bytes;
}

bool index_variavel(uint8_t **array_data, uint8_t *variable, int length){
    for(int i = 0; i < length; i++){
        if(array_data[i] != NULL){
            if(strcmp(array_data[i], variable) == 0)
                return true;
        }
    }

    return false;
}

void manipulating_file(LISTA *l_code, uint8_t* buffer, int size, int start_index_write, int length_data){
    uint32_t magic = 0x034E4452;
    get_real_address(&magic, sizeof(uint32_t));
    memcpy(buffer, &magic, sizeof(magic));

    LISTA *l_aux = l_code;
    int i = 4 + (2 * start_index_write);
    LISTA *l_memory_variables = criar_lista(None);

    int instrucoes_lidas = 0;

    while(i < size && l_aux != NULL){
        CODE *code = (CODE*)l_aux->conteudo;
        
        if(code->data != NULL) {   
            uint32_t valor = pegar_valores_instrucao(code->instrucao);
            memcpy(&buffer[i], &valor, sizeof(valor));
            
            int *index_memory = (int*)malloc(sizeof(int));
            *index_memory = i + 2;

            adicionar_no(l_memory_variables, index_memory, None);
            
            i += sizeof(valor);
        } 
        else if(code->index_jump != -1){
            uint32_t valor = pegar_valores_instrucao(code->instrucao);
            memcpy(&buffer[i], &valor, sizeof(valor));  

            uint16_t jump = pegar_local_jump(code->index_jump, l_code);
            memcpy(&buffer[i + 2], &jump, sizeof(jump));
            
            i += sizeof(valor);
        } 
        else {
            uint16_t valor = pegar_valores_instrucao(code->instrucao);
            memcpy(&buffer[i], &valor, sizeof(valor));
            
            i += sizeof(valor);
        }

        instrucoes_lidas++;
        l_aux = l_aux->prox;
    }

    l_aux = l_code;

    LISTA *l_aux_memory = l_memory_variables;
    uint8_t **variaveis = (uint8_t **) malloc(sizeof(uint8_t *) * length_data); 
    int last_index_stored = 0;

    while(l_aux != NULL){
        CODE *code = (CODE*)l_aux->conteudo;
        
        if(code->data) {
            bool valor_criado = index_variavel(variaveis, code->data->nome, length_data);
            
            if(!valor_criado){
                uint16_t teste = (uint16_t)code->data->valor;   
                memcpy(&buffer[i], &teste, sizeof(teste));
                code->data->stored_index = i;
                
                int length_variable = strlen(code->data->nome);

                variaveis[last_index_stored] = (uint8_t *) malloc(sizeof(uint8_t) * length_variable + 1);
                strcpy((char *)variaveis[last_index_stored], (char *)code->data->nome);
                last_index_stored++;

                i += sizeof(teste);
            } 

            int index_memory = *(int*)l_aux_memory->conteudo;
            int conta = (code->data->stored_index - 4)/2;
            memcpy(&buffer[index_memory], &conta , sizeof(uint16_t));

            l_aux_memory = l_aux_memory->prox;
        }

        l_aux = l_aux->prox;
    }

    for(int i = 0; i < length_data; i++){
        free(variaveis[i]);
    }

    free(variaveis);

    deletar_lista(l_memory_variables);
}

uint16_t pegar_valores_instrucao(uint8_t* instrucao){
    size_t size = sizeof(tabela_instrucao) / sizeof(tabela_instrucao[0]);
    
    for (size_t i = 0; i < size; i++) {
        if (strcmp((const char*)instrucao, tabela_instrucao[i].instrucao) == 0)
            return tabela_instrucao[i].codigo;
    }

    return 0xFFFF;
}