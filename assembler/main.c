#include <stdint.h>
#include <string.h>
#include "extracao_dados/data.h"
#include "extracao_dados/code.h"
#include "interface/interface.h"
#include "estrutura_de_dados/lista.h"
#include "criar_arquivo/create_file.h"

void executar_tarefa(char *palavra, LISTA* l_data, LISTA *l_code, int *index_inicial, uint8_t* content, long file_size){   
    if(strcmp(palavra, "DATA") == 0){
        ler_data(content, index_inicial, file_size, l_data);
    } else if(strcmp(palavra, "CODE") == 0) {
        ler_code(content, index_inicial, file_size,l_code, l_data);
    }

    return;
}

int main(int argc, char *argv[]){
    (void) argc;

    FILE *file = fopen(argv[1], "rb");

    if(file == NULL){
        printf("Não foi possivel ler o arquivo!");
        return 0;
    }
    
    //descobrir o tamanho do arquivo
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    uint8_t *content = (uint8_t*) malloc(file_size);
    fread(content, 1, file_size, file);
    fclose(file);

    LISTA* lista_data = criar_lista(Data);
    LISTA* lista_code = criar_lista(Code);

    for(int i = 0; i < file_size; i++){
        switch (content[i])
        {
            case '.':
                if(proximo_caracter_valido(content[i + 1])){
                    printf("Achei um ponto\n");
                    char* teste = pegar_palavra(content, file_size, i + 1);
                    printf("Palavra encontrada: %s - tamanho: %zu\n", teste, strlen(teste));
                    i += strlen(teste) + 1;
                    executar_tarefa(teste, lista_data, lista_code, &i, content, file_size);
                } else {
                    return 0;
                }
                break;
            case ';':
                i = pular_linha(content, file_size, i);
                break;
            case ' ':
                i = pular_espaco(content, file_size, i);
                printf("Achei um espaco\n");
                break;
            case '\n':
                printf("pulei linha\n");
                break;
            case '\0':
                return 0;    
            default:
                break;
        }
    }

    creating_file(lista_code);

    imprimir_lista(lista_data, Data);
    imprimir_lista(lista_code, Code);

    deletar_lista(lista_data);
    deletar_lista(lista_code);
    free(content);

    return 0;
}