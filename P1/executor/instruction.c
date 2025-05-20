#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "executor.h"

bool flagZero(uint8_t AC) {
    return AC == 0x00;
}

bool flagNeg(uint8_t AC) {
    return AC >= 0x80;
}

void instructionSTA(CPU *executor){
    executor->PC += 2;
    executor->position = executor->memory[executor->PC] ;
    printf("STA ----- POSICAO: %x ---- MEMORIA: %x\n\n", executor->position, executor->memory[executor->position * 2 + 4]);
    executor->memory[executor->position * 2 + 4] = executor->AC;
    executor->PC += 2;
    return;
}

void instructionLDA(CPU *executor){
    executor->PC += 2;
    executor->position = executor->memory[executor->PC] ;
    printf("LDA ----- POSICAO: %x ---- MEMORIA: %x\n\n", executor->position, executor->memory[executor->position * 2 + 4]);
    executor->AC = executor->memory[executor->position * 2 + 4];
    executor->PC += 2;
    return;
}

void instructionADD(CPU *executor){
    executor->PC += 2;
    executor->position = executor->memory[executor->PC] ;
    printf("ADD ----- POSICAO: %x ---- MEMORIA: %x\n\n", executor->position * 2 + 4, executor->memory[executor->position * 2 + 4]);
    executor->AC += executor->memory[executor->position * 2 + 4];
    executor->PC += 2;
    return;
}

void instructionAND(CPU *executor){
    executor->PC += 2;
    executor->position = executor->memory[executor->PC];
    printf("AND ----- POSICAO: %x ---- MEMORIA: %x\n\n", executor->position, executor->memory[executor->position * 2 + 4]);
    executor->AC = executor->AC & executor->memory[executor->position * 2 + 4];
    executor->PC += 2;
    return;
}

void instructionOR(CPU *executor){
    executor->PC += 2;
    executor->position = executor->memory[executor->PC];
    printf("OR ----- POSICAO: %x ---- MEMORIA: %x\n\n", executor->position, executor->memory[executor->position * 2 + 4]);
    executor->AC = executor->AC | executor->memory[executor->position * 2 + 4];
    executor->PC += 2;
    return;
}

void instructionNOT(CPU *executor){
    executor->AC = ~executor->AC;
    executor->PC += 2;
    return;
}

void instructionJMP(CPU *executor){
    executor->PC += 2;
    executor->position = executor->memory[executor->PC];
    printf("JMP ----- POSICAO: %x ---- MEMORIA: %x ------ MEMORY[PC] %x\n\n", executor->position, 
    executor->memory[executor->position * 2 + 4], 
    executor->memory[executor->PC]);
    executor->PC = executor->position * 2 + 4;
    return;
}

void instructionJN(CPU *executor){
    executor->PC += 2;
    if (flagNeg(executor->AC)) {
        executor->position = executor->memory[executor->PC];
        executor->PC = executor->position * 2 + 4;
    } else {
        executor->PC += 2;
    }
    return;
}

void instructionJZ(CPU *executor){
    executor->PC += 2;
    if (flagZero(executor->AC)) {
        executor->position = executor->memory[executor->PC];
        executor->PC = executor->position * 2 + 4;
    } else {
        executor->PC += 2;
    }
    return;
}