#include <stdio.h>
#include <stdlib.h>

#define TAPE_SIZE 30000

void executar_brainfuck(const char *codigo) {
    unsigned char tape[TAPE_SIZE] = {0};
    int ptr = 0;

    const char *pc = codigo;
    const char *loop_stack[512];
    int loop_top = -1;

    while (*pc) {
        switch (*pc) {
            case '>': ptr++; break;
            case '<': ptr--; break;
            case '+': tape[ptr]++; break;
            case '-': tape[ptr]--; break;
            case '.': putchar(tape[ptr]); break;
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
    printf("Resultado final: %d\n", tape[ptr]);
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

int main(int argc, char **argv) {
    char *codigo_bf = ler_stdin_completo();
    executar_brainfuck(codigo_bf);

    free(codigo_bf);
    return 0;
}