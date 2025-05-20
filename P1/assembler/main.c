#include <stdint.h>
#include <string.h>
#include "extracao_dados/data.h"
#include "extracao_dados/code.h"
#include "interface/interface.h"
#include "estrutura_de_dados/lista.h"
#include "criar_arquivo/create_file.h"

int executar_tarefa(char *palavra, LISTA* l_data, LISTA *l_code, int *index_inicial, uint8_t* content, long file_size){   
    if(strcmp(palavra, "DATA") == 0){
        return ler_data(content, index_inicial, file_size, l_data);
    } else if(strcmp(palavra, "CODE") == 0) {
        return ler_code(content, index_inicial, file_size,l_code, l_data);
    }

    return 0;
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

    int start_index_write = 0;
    bool leu_data = false;
    int length_data = 0;

    for(int i = 0; i < file_size; i++){
        switch (content[i])
        {
            case '.':
                if(proximo_caracter_valido(content[i + 1])){
                    char* teste = pegar_palavra(content, file_size, i + 1);
                    i += strlen(teste) + 1;

                    if(leu_data){
                        start_index_write = executar_tarefa(teste, lista_data, lista_code, &i, content, file_size);
                    } else {
                        length_data = executar_tarefa(teste, lista_data, lista_code, &i, content, file_size);
                        leu_data = true;
                    }

                } else {
                    printf("ERRO: sintaxe incorreta do arquivo\n");
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
                printf("Caracter não mapeado\n");
                break;
        }
    }

    creating_file(lista_code, start_index_write, length_data);

    imprimir_lista(lista_data, Data);
    imprimir_lista(lista_code, Code);

    deletar_lista(lista_data);
    deletar_lista(lista_code);
    free(content);

    return 0;
}