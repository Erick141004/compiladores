#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "executor.h"

bool flagZero(uint8_t AC) {
    return AC == 0x00;
}

bool flagNeg(uint8_t AC) {
    return AC >= 0x80;
}

void printMemory(uint8_t* content){
    for(int i = 0; i < TOTAL_SIZE; i++){
        if (i % 16 == 0){
            printf("\n");
        }else if(i % 1 == 0){
            printf(" ");
        }

        printf("%02x", content[i]);
    }
}

void freeMemory(CPU *content){
    if(content == NULL)
        return;

    free(content->memory);
    content->memory = NULL;

    free(content);
    content = NULL;
    return;
}


CPU* createMemory(){
    CPU *content = malloc(sizeof(CPU));
    content->memory = (uint8_t*)malloc(sizeof(uint8_t) * TOTAL_SIZE);
    content->AC = 0x00;
    content->PC = 0x04;
    content->position = 0;

    return content;
}