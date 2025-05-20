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
    fputs("]", f);            // fim do loop principal

    *cel_atual = tmp1;
}

void gerar_div_bf(FILE *f, int a, int b, int res, int tmp1, int tmp2, int tmp3, int *cel_atual) {
    // Zera res e temporários
    mover_para_celula(f, res, *cel_atual);   fputs("[-]", f);
    mover_para_celula(f, tmp1, res);         fputs("[-]", f);
    mover_para_celula(f, tmp2, tmp1);        fputs("[-]", f);
    mover_para_celula(f, tmp3, tmp2);        fputs("[-]", f);

    // Copia A para tmp1 (dividendo)
    mover_para_celula(f, a, tmp3);
    fputs("[->+<]", f);      // Copia A para tmp1, zerando A

    // Inicia a divisão - algoritmo simples:
    // Enquanto dividendo >= divisor:
    //   Subtraia o divisor do dividendo
    //   Incremente o resultado

    mover_para_celula(f, tmp1, a);
    fputs("[", f);           // Início do loop principal - enquanto tmp1 (dividendo) > 0

        // Copia tmp1 para tmp2 (cópia de trabalho do dividendo)
        mover_para_celula(f, tmp2, tmp1);
        fputs("[-]", f);     // Zera tmp2
        mover_para_celula(f, tmp1, tmp2);
        fputs("[->+<]", f);  // Copia tmp1 para tmp2
        
        // Copia B para tmp3 (cópia de trabalho do divisor)
        mover_para_celula(f, tmp3, tmp1);
        fputs("[-]", f);     // Zera tmp3
        mover_para_celula(f, b, tmp3);
        fputs("[->+<]", f);  // Copia B para tmp3
        
        // Tenta subtrair o divisor (tmp3) do tmp2
        // E verifica se a subtração é possível
        mover_para_celula(f, tmp2, b);
        
        // Loop de tentativa de subtração
        fputs(">", f);       // Move para tmp2
        
        // Marca para flag usar mais tarde
        fputs("+", f);       // Define uma flag (começamos assumindo sucesso)
        
        fputs("[", f);       // Enquanto tmp2 > 0
            fputs("-", f);   // Decrementa tmp2
            
            // Decrementa tmp3 se ainda tiver valor
            mover_para_celula(f, tmp3, tmp2);
            fputs(">>[", f);  // Move para tmp3, verifica se > 0
            fputs("-", f);    // Decrementa tmp3
            
            mover_para_celula(f, tmp2, tmp3);
            fputs("<<]", f);  // Volta para tmp2
            
            // Verifica se tmp3 ficou negativo (ou seja, tmp2 < tmp3)
            mover_para_celula(f, tmp3, tmp2);
            fputs(">>", f);   // Move para tmp3
            
            fputs("+[-<->]", f); // Se tmp3 for zero, a flag permanece positiva
                                  // Se tmp3 ainda tiver valor, zera a flag
            
            mover_para_celula(f, tmp2, tmp3);
            fputs("<<", f);   // Volta para tmp2
        fputs("]", f);       // Fim do loop de tentativa

        // Se a subtração foi bem-sucedida
        mover_para_celula(f, tmp2+1, tmp2); // Move para a flag
        fputs("[", f);       // Se a flag for positiva (subtração possível)
            fputs("-", f);   // Zera a flag

            // Incrementa o resultado
            mover_para_celula(f, res, tmp2+1);
            fputs("+", f);   // Incrementa o resultado
            
            // Copia o valor residual de tmp2 de volta para tmp1
            mover_para_celula(f, tmp1, res);
            fputs("[-]", f);  // Zera tmp1
            mover_para_celula(f, tmp2, tmp1);
            fputs("[<+>-]", f); // Move o valor de tmp2 para tmp1
            
            // Vai para tmp1 para continuar as tentativas
            mover_para_celula(f, tmp1, tmp2);
            fputs("<", f);    // Move para tmp1
        fputs("]", f);       // Fim do bloco condicional
        
        // Se não conseguiu subtrair (flag zerada), então o loop deve terminar
        // retornando à célula tmp1 e verificando se ela é zero
        mover_para_celula(f, tmp1, tmp2+1);
        
    fputs("]", f);           // Fim do loop principal

    *cel_atual = tmp1;
}

void gerar_valor_bf(FILE *f, int cel, int valor, int *cel_atual) {
    mover_para_celula(f, cel, *cel_atual);
    fprintf(f, "[-]"); // zera a célula
    for (int i = 0; i < valor; i++) {
        fputc('+', f);
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
        gerar_valor_bf(file_bf, raiz->celula, valor, cel_atual);
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
            int tmp1 = (*prox_cel_livre)++;
            int tmp2 = (*prox_cel_livre)++;
            int tmp3 = (*prox_cel_livre)++;
            gerar_div_bf(file_bf, a, b, raiz->celula, tmp1, tmp2, tmp3, cel_atual);
        }
    }
    else if (raiz->tipo == ATRIB) {
        gerar_texto_utf8_bf(file_bf, raiz->valor, cel_atual);
        gerar_char_utf8_bf(file_bf, L'=', cel_atual);

        if (raiz->filho_dir) {
            //gerar_imprimir_numero_bf(file_bf, raiz->filho_dir->celula, cel_atual, prox_cel_livre);

            mover_para_celula(file_bf, raiz->filho_dir->celula, *cel_atual);
            *cel_atual = raiz->filho_dir->celula;
        }
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