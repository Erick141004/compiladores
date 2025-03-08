#include "create_file.h"
#include "../extracao_dados/code.h"
#include "../extracao_dados/data.h"
#include "../estrutura_de_dados/lista.h"

const Instrucao tabela_instrucao[] = {
    {"NOP", 0x00}, {"STA", 0x10}, {"LDA", 0x20}, {"ADD", 0x30},
    {"OR",  0x40}, {"AND", 0x50}, {"NOT", 0x60}, {"JMP", 0x80},
    {"JN",  0x90}, {"JZ",  0xA0}, {"HLT", 0xF0}
};

void creating_file(LISTA* l_code, int start_index_write){
    FILE *file = fopen("teste.mem", "wb");
    int size = 516;

    if(file == NULL){
        printf("Não foi possivel criar o arquivo!");
        return;
    }

    uint8_t buffer[516] = {0};
    manipulating_file(l_code, buffer, size, start_index_write);

    fwrite(buffer, 1, size, file);

    fclose(file);
}

void manipulating_file(LISTA *l_code, uint8_t* buffer, int size, int start_index_write){
    uint32_t magic = 0x034E4452;
    get_real_address(&magic, sizeof(uint32_t));
    memcpy(buffer, &magic, sizeof(magic));

    LISTA *l_aux = l_code;
    int i = 4 + (2 * start_index_write);
    LISTA *l_memory = criar_lista(None);

    while(i < size && l_aux != NULL){
        CODE *code = (CODE*)l_aux->conteudo;
        
        if(code->data != NULL)
        {   
            uint32_t valor = pegar_valores_instrucao(code->instrucao);
            memcpy(&buffer[i], &valor, sizeof(valor));
            
            int *index_memory = (int*)malloc(sizeof(int));
            *index_memory = i + 2;

            adicionar_no(l_memory, index_memory, None);
            
            i += sizeof(valor);
        } else {
            printf("ENTROU AQUI------------\n");
            uint16_t valor = pegar_valores_instrucao(code->instrucao);
            memcpy(&buffer[i], &valor, sizeof(valor));
            
            i += sizeof(valor);
        }

        l_aux = l_aux->prox;
    }

    l_aux = l_code;

    LISTA *l_aux_memory = l_memory;

    while(l_aux != NULL){
        CODE *code = (CODE*)l_aux->conteudo;
        
        if(code->data){
            uint16_t teste = (uint16_t)code->data->valor;   
            memcpy(&buffer[i], &teste, sizeof(teste));

            int index_memory = *(int*)l_aux_memory->conteudo;
            int conta = (i - 4)/2;
            memcpy(&buffer[index_memory], &conta , sizeof(uint16_t));

            l_aux_memory = l_aux_memory->prox;
            i += sizeof(teste);
        }

        l_aux = l_aux->prox;
    }

    deletar_lista(l_memory);
}

uint16_t pegar_valores_instrucao(uint8_t* instrucao){
    size_t size = sizeof(tabela_instrucao) / sizeof(tabela_instrucao[0]);
    
    for (size_t i = 0; i < size; i++) {
        if (strcmp((const char*)instrucao, tabela_instrucao[i].instrucao) == 0)
            return tabela_instrucao[i].codigo;
    }

    return 0xFFFF;
}