#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "parser.h"
#include "tokens.h"

int main(int argc, char **argv){
    (void) argc;

    FILE *file = fopen(argv[1], "rb");

    if(file == NULL){
        printf("Não foi possivel ler o arquivo!");
        return 0;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    uint8_t *content = (uint8_t*) malloc(file_size);
    fread(content, 1, file_size, file);
    fclose(file);

    Token teste;
    int pos_atual = 0;

    return 0;
}