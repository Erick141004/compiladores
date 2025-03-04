#include "create_file.h"
#include "../extracao_dados/code.h"
#include "../extracao_dados/data.h"
#include "../estrutura_de_dados/lista.h"

const Instrucao tabela_instrucao[] = {
    {"NOP", 0x00}, {"STA", 0x10}, {"LDA", 0x20}, {"ADD", 0x30},
    {"OR",  0x40}, {"AND", 0x50}, {"NOT", 0x60}, {"JMP", 0x80},
    {"JN",  0x90}, {"JZ",  0xA0}, {"HLT", 0xF0}
};

void creating_file(LISTA* l_code){
    FILE *file = fopen("teste.mem", "wb");
    int size = 516;

    if(file == NULL){
        printf("Não foi possivel criar o arquivo!");
        return;
    }

    uint8_t buffer[516] = {0};
    manipulating_file(l_code, buffer, size);

    fwrite(buffer, 1, size, file);

    fclose(file);
}

void manipulating_file(LISTA *l_code, uint8_t* buffer, int size){
    uint32_t magic = 0x034E4452;
    get_real_address(&magic, sizeof(uint32_t));
    memcpy(buffer, &magic, sizeof(magic));

    LISTA *l_aux = l_code;
    int i = 4;
    int data = 260;

    while(i < size/2 && l_aux->prox != NULL){
        CODE *code = (CODE*)l_aux->conteudo;
        uint16_t valor = pegar_valores_instrucao(code->instrucao);
        
        memcpy(&buffer[i], &valor, sizeof(valor));

        if(code->data)
        {
            uint16_t teste = (uint16_t)code->data->valor;   
            memcpy(&buffer[data], &teste, sizeof(teste));

            data += sizeof(teste);
        }

        i += sizeof(valor);
        l_aux = l_aux->prox;
    }
}

uint16_t pegar_valores_instrucao(uint8_t* instrucao){
    size_t size = sizeof(tabela_instrucao) / sizeof(tabela_instrucao[0]);
    
    for (size_t i = 0; i < size; i++) {
        if (strcmp((const char*)instrucao, tabela_instrucao[i].instrucao) == 0)
            return tabela_instrucao[i].codigo;
    }

    return 0xFFFF;
}