#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "parser.h"
#include "tokens.h"
#include "lista.h"
#include "arvore.h"
#include "create_file.h"

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

    Token token;
    int pos_atual = 0;
    LISTA *variaveis = criar_lista();

    token = proximo_token(content, &pos_atual);
    NO* no = parse_program(content, &pos_atual, &token, variaveis);

    imprimir_arvore(no, 1);
    imprimir_lista(variaveis);
    criar_arquivo(variaveis, no);
    limpar_arvore(no);
    deletar_lista(variaveis);

    return 0;
}