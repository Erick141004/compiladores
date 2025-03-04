#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <ctype.h>

bool proximo_caracter_valido(char value);
int pular_linha(uint8_t *content, long file_size, int index);
char* pegar_palavra(uint8_t *content, long file_size, int index_inicial);
int pular_espaco(uint8_t *content, long file_size, int index);
void get_real_address(void* value, size_t size);

#endif