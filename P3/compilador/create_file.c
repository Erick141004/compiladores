#include "create_file.h"

void mover_para_celula(FILE *f, int alvo, int atual) {
    int delta = alvo - atual;
    for (int i = 0; i < abs(delta); i++) {
        fputc(delta > 0 ? '>' : '<', f);
    }
}

void gerar_soma_bf(FILE *f, int a, int b, int res, int *cel_atual) {
    // Zera resultado
    mover_para_celula(f, res, *cel_atual);
    fputs("[-]", f);
    *cel_atual = res;

    // Copia A para resultado
    mover_para_celula(f, a, *cel_atual);
    fputs("[-", f);
    mover_para_celula(f, res, a); fputc('+', f);
    mover_para_celula(f, a, res); fputs("]", f);  // <-- move de volta para A
    *cel_atual = a;

    // Copia B para resultado
    mover_para_celula(f, b, *cel_atual);
    fputs("[-", f);
    mover_para_celula(f, res, b); fputc('+', f);
    mover_para_celula(f, b, res); fputs("]>", f);  // <-- move de volta para B
    *cel_atual = b;
}

void gerar_sub_bf(FILE *f, int a, int b, int res, int *cel_atual) {
    // res = a - b
    mover_para_celula(f, res, *cel_atual); fputs("[-]", f); // zera resultado

    // copia A para res
    mover_para_celula(f, a, res);
    fputs("[-", f);
    mover_para_celula(f, res, a); fputc('+', f);
    mover_para_celula(f, a, res); fputs("]", f);

    // subtrai B de res
    mover_para_celula(f, b, a);
    fputs("[-", f);
    mover_para_celula(f, res, b); fputc('-', f);
    mover_para_celula(f, b, res); fputs("]", f);

    *cel_atual = b;
}

void gerar_mult_bf(FILE *f, int a, int b, int res, int tmp1, int tmp2, int *cel_atual) {
    // Zera células: resultado e temporários
    mover_para_celula(f, res, *cel_atual);  fputs("[-]", f);
    mover_para_celula(f, tmp1, res);        fputs("[-]", f);
    mover_para_celula(f, tmp2, tmp1);       fputs("[-]", f);

    // Copia A para tmp1
    mover_para_celula(f, a, tmp2);
    fputs("[", f);            // enquanto a > 0
    fputc('-', f);            // decrementa a
    mover_para_celula(f, tmp1, a);  
    fputc('+', f);            // incrementa tmp1
    mover_para_celula(f, a, tmp1);
    fputs("]", f);            // fim do loop

    // Loop do algoritmo principal: para cada unidade em tmp1, adiciona B ao resultado
    mover_para_celula(f, tmp1, a);
    fputs("[", f);            // enquanto tmp1 > 0
    fputc('-', f);            // decrementa tmp1

    // Copia B para tmp2 e para res
    mover_para_celula(f, b, tmp1);
    fputs("[", f);            // enquanto b > 0
    fputc('-', f);            // decrementa b
    mover_para_celula(f, tmp2, b); 
    fputc('+', f);            // incrementa tmp2
    mover_para_celula(f, res, tmp2);
    fputc('+', f);            // incrementa res
    mover_para_celula(f, b, res);
    fputs("]", f);            // fim do loop interno
    
    // Restaura B a partir de tmp2
    mover_para_celula(f, tmp2, b);
    fputs("[", f);            // enquanto tmp2 > 0
    fputc('-', f);            // decrementa tmp2
    mover_para_celula(f, b, tmp2);
    fputc('+', f);            // incrementa b
    mover_para_celula(f, tmp2, b);
    fputs("]", f);            // fim do loop de restauração
    
    // Volta para tmp1 para continuar o loop principal
    mover_para_celula(f, tmp1, tmp2);
    fputs("]<", f);            // fim do loop principal

    *cel_atual = tmp1 - 1;
}

void gerar_div_bf(FILE *f, int a, int b, int res, int valor, int *cel_atual) {
    // Zera as células de resultado e temporárias
    mover_para_celula(f, res, *cel_atual);  fputs("[-]", f);

    // Loop de divisão: enquanto tmp1 >= tmp2
    //mover_para_celula(f, tmp1, b);
    mover_para_celula(f, a, res);
    fputs("[", f); // Início do loop em tmp1
    // Subtrai tmp2 de tmp1
    gerar_valor_bf(f, 0, valor, cel_atual, true, '-');

    // Incrementa o resultado
    mover_para_celula(f, res, a);
    fputc('+', f);

    // Volta para tmp1 para continuar o loop
    mover_para_celula(f, a, res);
    fputs("]", f); // Fim do loop
    mover_para_celula(f, res, a);

    *cel_atual = res; // Atualiza a célula atual
}

void gerar_valor_bf(FILE *f, int cel, int valor, int *cel_atual, bool divisao, char sinal) {
    
    if (!divisao){
        mover_para_celula(f, cel, *cel_atual);
        fprintf(f, "[-]"); // zera a célula  
    }     

    for (int i = 0; i < valor; i++) {
        fputc(sinal, f);
    }
    *cel_atual = cel; // atualiza a célula atual
}


void gerar_char_utf8_bf(FILE *file, wchar_t wc, int *cel_atual) {
    char utf8[5] = {0};
    int len = wctomb(utf8, wc); // converte wchar_t para UTF-8

    for (int i = 0; i < len; i++) {
        int byte = (unsigned char)utf8[i];
        mover_para_celula(file, (*cel_atual) + 1, *cel_atual);
        fputs("[-]", file); // zera
        for (int j = 0; j < byte; j++) fputc('+', file);
        fputc('.', file); // imprime
        *cel_atual = (*cel_atual) + 1;
    }
}

void gerar_texto_utf8_bf(FILE *file, const wchar_t* texto, int *cel_atual) {
    for (int i = 0; texto[i] != L'\0'; i++) {
        gerar_char_utf8_bf(file, texto[i], cel_atual);
    }
}

void gerar_imprimir_numero_bf(FILE *f, int cel_num, int *cel_atual, int *prox_cel_livre) {
    int tmp_num = (*prox_cel_livre)++;  // Cópia do número
    int tmp_dezenas = (*prox_cel_livre)++;  // Dígito das dezenas
    int tmp_unidades = (*prox_cel_livre)++;  // Dígito das unidades

    // Zerar células temporárias
    mover_para_celula(f, tmp_dezenas, *cel_atual);
    fputs("[-]", f);
    mover_para_celula(f, tmp_unidades, tmp_dezenas);
    fputs("[-]", f);
    mover_para_celula(f, tmp_num, tmp_unidades);
    fputs("[-]", f);

    // Copiar o número para tmp_num
    mover_para_celula(f, cel_num, *cel_atual);
    fputs("[->+", f);
    mover_para_celula(f, tmp_num, cel_num);
    fputs("<]", f);

    // Calcular o dígito das dezenas
    mover_para_celula(f, tmp_num, *cel_atual);
    fputs("[", f);  // Enquanto tmp_num > 0
    fputs("----------", f);  // Subtrair 10
    mover_para_celula(f, tmp_dezenas, tmp_num);
    fputc('+', f);  // Incrementar dezenas
    mover_para_celula(f, tmp_num, tmp_dezenas);
    fputs("]", f);

    // O restante em tmp_num é o dígito das unidades
    mover_para_celula(f, tmp_num, *cel_atual);
    fputs("[->+", f);
    mover_para_celula(f, tmp_unidades, tmp_num);
    fputs("<]", f);

    // Imprimir dígito das dezenas (se > 0)
    mover_para_celula(f, tmp_dezenas, *cel_atual);
    fputs("[", f);
    for (int i = 0; i < 48; i++) fputc('+', f);  // Adicionar 48
    fputc('.', f);  // Imprimir
    fputs("[-]", f);  // Limpar
    fputs("]", f);

    // Imprimir dígito das unidades
    mover_para_celula(f, tmp_unidades, *cel_atual);
    for (int i = 0; i < 48; i++) fputc('+', f);  // Adicionar 48
    fputc('.', f);  // Imprimir
    fputs("[-]", f);  // Limpar

    *cel_atual = tmp_unidades;
}

void gerar_codigo_bf(NO *raiz, FILE *file_bf, int *cel_atual, int *prox_cel_livre) {
    if (!raiz) return;

    gerar_codigo_bf(raiz->filho_esq, file_bf, cel_atual, prox_cel_livre);
    gerar_codigo_bf(raiz->filho_dir, file_bf, cel_atual, prox_cel_livre);

    if (raiz->tipo == NUM) {
        int valor = (int)wcstol(raiz->valor, NULL, 10);
        raiz->celula = (*prox_cel_livre)++;
        gerar_valor_bf(file_bf, raiz->celula, valor, cel_atual, false, '+');
    }
    else if (raiz->tipo == OP) {
        int a = raiz->filho_esq->celula;
        int b = raiz->filho_dir->celula;
        
        raiz->celula = (*prox_cel_livre)++;

        if (wcscmp(raiz->valor, L"+") == 0) {
            gerar_soma_bf(file_bf, a, b, raiz->celula, cel_atual);
        }
        else if (wcscmp(raiz->valor, L"*") == 0) {
            int tmp1 = (*prox_cel_livre)++;
            int tmp2 = (*prox_cel_livre)++;
            gerar_mult_bf(file_bf, a, b, raiz->celula, tmp1, tmp2, cel_atual);
        } 
        else if (wcscmp(raiz->valor, L"-") == 0) {
            gerar_sub_bf(file_bf, a, b, raiz->celula, cel_atual);
        } 
        else if (wcscmp(raiz->valor, L"/") == 0) {
            if (raiz->filho_dir->tipo == NUM && wcstol(raiz->filho_dir->valor, NULL, 10) == 0) {
                printf("Erro: divisão por zero!\n");
                exit(EXIT_FAILURE);
            }
     
            gerar_div_bf(file_bf, a, b, raiz->celula, wcstol(raiz->filho_dir->valor, NULL, 10), cel_atual);
        }
    }
    else if (raiz->tipo == ATRIB) {
        int cel_result = *cel_atual;

        gerar_texto_utf8_bf(file_bf, raiz->valor, cel_atual);
        gerar_char_utf8_bf(file_bf, L'=', cel_atual);
        mover_para_celula(file_bf, cel_result, *cel_atual);
        fputc('.', file_bf);
    }
}


void criar_arquivo(NO *raiz){
    FILE* file_bf = stdout;

    if(file_bf == NULL){
        printf("Nao foi possivel criar o arquivo\n");
        exit(EXIT_FAILURE);
    }

    int cel_atual = 0;
    int prox_cel_livre = 1;
    gerar_codigo_bf(raiz, file_bf, &cel_atual, &prox_cel_livre);
}