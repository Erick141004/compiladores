#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "executor.h"
#include "instruction.h"

void get_real_address(void* value, size_t size){
    __uint8_t* bytes = (__uint8_t *) value;
    for(int i = 0; i < size / 2; i++){
        __uint8_t aux = bytes[i];
        bytes[i] =  bytes[size - i - 1];
        bytes[size - i - 1] = aux;
    }
}

int main(int argc, char** argv)
{
    FILE *file = fopen(argv[1], "rb");

    if(file == NULL){
        printf("Não foi possivel ler o arquivo!");
        return 0;
    }

    CPU* executor = createMemory();
    fread(executor->memory, 1, TOTAL_SIZE, file);
    fclose(file);

    uint32_t file_validation = *((__uint32_t*)(executor->memory));
    get_real_address(&file_validation, sizeof(uint32_t));

    if(file_validation != SIGNATURE_FILE){
        printf("Arquivo não compativel, tente novamente com outro arquivo\nExtensão aceita: .mem!");
        return 0;
    }

    printf("SIGNATURE: 0x%x\n\n", file_validation);

    do {
        printf("\nAC: %x PC: %x FZ: %i FN: %i INSTRUCAO: %x CONTEUDO: %x\n", executor->AC, executor->PC,
             flagZero(executor->AC), flagNeg(executor->AC), executor->memory[executor->PC], executor->memory[executor->PC+2]);

        switch (executor->memory[executor->PC]) {
            case STA:
                instructionSTA(executor);               
                break;
            case LDA:
                instructionLDA(executor);
                break;
            case ADD:
                instructionADD(executor);
                break;
            case OR:
                instructionOR(executor);
                break;
            case AND:
                instructionAND(executor);
                break;
            case NOT:
                instructionNOT(executor);
                break;
            case JMP:
                instructionJMP(executor);
                break;
            case JN:
                instructionJN(executor);
                break;
            case JZ:
                instructionJZ(executor);
                break;
            default:
                executor->PC += 2;
                break;
        }

        printMemory(executor->memory);
        printf("\n");

    } while (executor->memory[executor->PC] != HLT && executor->PC <= 0xFF);

    freeMemory(executor);

    return 0;
}