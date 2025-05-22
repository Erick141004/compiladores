#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

#define TAPE_SIZE 30000

void executar_brainfuck(const char *codigo) {
    unsigned char tape[TAPE_SIZE] = {0};
    int ptr = 0;

    const char *pc = codigo;
    const char *loop_stack[512];
    int loop_top = -1;
    bool eh_resultado = false;

    while (*pc) {
        switch (*pc) {
            case '>': ptr++; break;
            case '<': ptr--; break;
            case '+': tape[ptr]++; break;
            case '-': tape[ptr]--; break;
            case '.': 
                if(!eh_resultado)
                    putchar(tape[ptr]);
                else
                    printf(" %d", tape[ptr]);
            
                if(tape[ptr] == '='){
                    eh_resultado = true;
                }
                break;
            case '[':
                if (tape[ptr] == 0) {
                    int loop = 1;
                    while (loop > 0) {
                        pc++;
                        if (*pc == '[') loop++;
                        if (*pc == ']') loop--;
                    }
                } else {
                    loop_stack[++loop_top] = pc;
                }
                break;
            case ']':
                if (tape[ptr] != 0) {
                    pc = loop_stack[loop_top];
                } else {
                    loop_top--;
                }
                break;
        }
        pc++;
    }

    printf("\n");
}

char* ler_stdin_completo() {
    size_t tamanho = 0;
    size_t capacidade = 1024;
    char *buffer = malloc(capacidade);

    if (!buffer) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    int c;
    while ((c = fgetc(stdin)) != EOF) {
        buffer[tamanho++] = (char)c;

        if (tamanho >= capacidade) {
            capacidade *= 2;
            buffer = realloc(buffer, capacidade);
            if (!buffer) {
                perror("realloc");
                exit(EXIT_FAILURE);
            }
        }
    }

    buffer[tamanho] = '\0';
    return buffer;
}

char* ler_arquivo(const char *nome) {
    FILE *f = fopen(nome, "r");
    if (!f) {
        fprintf(stderr, "Erro ao abrir '%s': %s\n", nome, strerror(errno));
        exit(1);
    }
    fseek(f, 0, SEEK_END);
    long t = ftell(f);
    rewind(f);
    char *buf = malloc(t+1);
    if (!buf) { perror("malloc"); exit(1); }
    fread(buf, 1, t, f);
    buf[t] = '\0';
    fclose(f);
    return buf;
}

int main(int argc, char **argv) {
    char *codigo_bf;

    if (argc > 1) {
        codigo_bf = ler_arquivo("../compilador/main.bf");
    } else {
        codigo_bf = ler_stdin_completo();
    }

    executar_brainfuck(codigo_bf);
    free(codigo_bf);
    return 0;
}