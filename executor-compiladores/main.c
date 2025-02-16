#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "executor.h"

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
    uint8_t AC = 0;
    uint8_t PC = 0x04;

    FILE *file = fopen("aula01.mem", "rb");

    if(file == NULL){
        printf("Não foi possivel ler o arquivo!");
        return 0;
    }

    uint8_t *memory = (uint8_t *)malloc(sizeof(uint8_t)* TOTAL_SIZE);
    fread(memory, 1, TOTAL_SIZE, file);
    fclose(file);

    uint8_t posicao = 0;

    uint32_t file_validation = *((__uint32_t*)(memory));
    get_real_address(&file_validation, sizeof(uint32_t));

    if(file_validation != SIGNATURE_FILE){
        printf("Arquivo não compativel, tente novamente com outro arquivo\nExtensão aceita: .mem!");
        return 0;
    }

    printf("SIGNATURE: 0x%x\n\n", file_validation);

    do {
        printf("\nAC: %x PC: %x FZ: %i FN: %i INSTRUCAO: %x CONTEUDO: %x\n", AC, PC, flagZero(AC), flagNeg(AC), memory[PC], memory[PC+2]);

        switch (memory[PC]) {
            case STA:
                PC += 2;
                posicao = memory[PC] ;
                printf("STA ----- POSICAO: %x ---- MEMORIA: %x\n\n", posicao, memory[posicao * 2 + 4]);
                memory[posicao * 2 + 4] = AC;
                PC += 2;
                break;
            case LDA:
                PC += 2;
                posicao = memory[PC] ;
                printf("LDA ----- POSICAO: %x ---- MEMORIA: %x\n\n", posicao, memory[posicao * 2 + 4]);
                AC = memory[posicao * 2 + 4];
                PC += 2;
                break;
            case ADD:
                PC += 2;
                posicao = memory[PC] ;
                printf("ADD ----- POSICAO: %x ---- MEMORIA: %x\n\n", posicao * 2 + 4, memory[posicao * 2 + 4]);
                AC += memory[posicao * 2 + 4];
                PC += 2;
                break;
            case OR:
                PC += 2;
                posicao = memory[PC];
                printf("OR ----- POSICAO: %x ---- MEMORIA: %x\n\n", posicao, memory[posicao * 2 + 4]);
                AC = AC | memory[posicao * 2 + 4];
                PC += 2;
                break;
            case AND:
                PC += 2;
                posicao = memory[PC];
                printf("AND ----- POSICAO: %x ---- MEMORIA: %x\n\n", posicao, memory[posicao * 2 + 4]);
                AC = AC & memory[posicao * 2 + 4];
                PC += 2;
                break;
            case NOT:
                AC = ~AC;
                PC += 2;
                break;
            case JMP:
                PC += 2;
                posicao = memory[PC];
                printf("JMP ----- POSICAO: %x ---- MEMORIA: %x ------ MEMORY[PC] %x\n\n", posicao, memory[posicao * 2 + 4], memory[PC]);
                PC = posicao * 2 + 4;
                break;
            case JN:
                PC += 2;
                if (flagNeg(AC)) {
                    posicao = memory[PC];
                    PC = posicao * 2 + 4;
                } else {
                    PC += 2;
                }
                break;
            case JZ:
                PC += 2;
                if (flagZero(AC)) {
                    posicao = memory[PC];
                    PC = posicao * 2 + 4;
                } else {
                    PC += 2;
                }
                break;
            default:
                PC += 2;
                break;
        }

        printMemory(memory);
        printf("\n");

    } while (memory[PC] != HLT && PC <= 0xFF);

    free(memory);

    return 0;
}