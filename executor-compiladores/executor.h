#ifndef ADDRESS_H
#define ADDRESS_H

#include <stdint.h>
#include <stdbool.h>

//
#define TOTAL_SIZE 516
#define SIGNATURE_FILE 0x034e4452

//Instrucoes
#define NOP 0x00 //sem operacao
#define STA 0x10 //armazena na memoria
#define LDA 0x20 //le da memoria
#define ADD 0x30 //adiciona
#define OR 0x40 //operador or
#define AND 0x50 //operador and
#define NOT 0x60 //operador not
#define JMP 0x80 //jump para a linha
#define JN 0x90 //jump se for negativo
#define JZ 0xA0 //jump se for igual a 0
#define HLT 0xF0 //finalizar programa

typedef struct {
    uint8_t AC;
    uint8_t PC;
    uint8_t position;
    uint8_t* memory;
} CPU;

bool flagZero(uint8_t);
bool flagNeg(uint8_t);
void printMemory(uint8_t *);
void freeMemory(CPU *);
CPU* createMemory();

#endif