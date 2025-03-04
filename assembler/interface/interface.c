#include "interface.h"

int pular_linha(uint8_t *content, long file_size, int index){
    int index_jump = 0;
    for(int i = index; i < file_size; i++){
        if(content[i] == '\n' || content[i] == '\0'){
            index_jump = i;
            break;
        }
    }

    return index_jump;
}

bool proximo_caracter_valido(char value){
    return isupper(value);
}

char* pegar_palavra(uint8_t *content, long file_size, int index_inicial){
    int quantidade_letras = 0;
    
    for(int i = index_inicial; i < file_size; i++){
        if(content[i] == ' ' || content[i] == '\0' || content[i] == '\n') break;
        quantidade_letras++;
    }
    
    char* palavra = (char *)malloc(sizeof(char) * (quantidade_letras + 1));
    for(int i = 0; i < quantidade_letras; i++){
        palavra[i] = content[index_inicial + i];
    }
    
    palavra[quantidade_letras] = '\0';
    printf("PALAVRA PEGA: %s -------\n", palavra);

    return palavra;
}

int pular_espaco(uint8_t *content, long file_size, int index){
    int index_jump = 0;
    for(int i = index; i < file_size; i++){
        if(content[i] != ' '){
            index_jump = i;
            break;
        }
    }

    return index_jump;
}

void get_real_address(void* value, size_t size){
    __uint8_t* bytes = (__uint8_t *) value;
    for(size_t i = 0; i < size / 2; i++){
        __uint8_t aux = bytes[i];
        bytes[i] =  bytes[size - i - 1];
        bytes[size - i - 1] = aux;
    }
}