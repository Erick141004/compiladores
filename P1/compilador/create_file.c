#include "create_file.h"

void gerar_data(LISTA *lista_data, FILE *assembly){
    fprintf(assembly, ".DATA\n");
    LISTA *l_aux = lista_data;

    while(l_aux != NULL){
        DATA* d = (DATA *)l_aux->conteudo;
        
        if(d->expressao)
            fprintf(assembly, "%s %s ?\n", d->nome_variavel, d->tipo_variavel);
        else 
            fprintf(assembly, "%s %s %s\n", d->nome_variavel, d->tipo_variavel, d->valor);
        
        l_aux = l_aux->prox;
    }
}

bool proxima_operacao_soma(NO* no){
    if(no->tipo == OP)
        return strcmp(no->valor, "+") == 0;

    return true;
}

void escrever_valor(FILE *assembly, NO *raiz, int valor_temp, NO* filho, int *qtd_linhas, LISTA *lista){
    if(valor_temp >= 0){
        if (strcmp(raiz->valor, "+") == 0){
            fprintf(assembly, "ADD LIT_%d\n", valor_temp);
            (*qtd_linhas)++;
        }
        else if (strcmp(raiz->valor, "-") == 0){
            if(!proxima_operacao_soma(raiz->filho_esq) || !proxima_operacao_soma(raiz->filho_dir)){
                fprintf(assembly, "LDA %s\n", encontrar_primeiro_atrib(raiz)->valor);
                (*qtd_linhas)++;
            }

            uint8_t nome[20];
            snprintf(nome, sizeof(nome), "PULAR_%d", (*qtd_linhas) + 7);

            char buffer[12];
            snprintf(buffer, sizeof(buffer), "%d", (*qtd_linhas) + 7);

            DATA *d = criar_data(nome, "DB", (uint8_t *)buffer, false);
            adicionar_no(lista, d);

            fprintf(assembly, "STA TEMP_0\n");
            fprintf(assembly, "LDA LIT_%d\n", valor_temp);
            fprintf(assembly, "STA TEMP_1\n");
            fprintf(assembly, "LDA %s\n", nome);
            fprintf(assembly, "STA TEMP_2\n");
            fprintf(assembly, "JMP SUB\n");
            
            if(raiz->no_pai->tipo != ATRIB){
                fprintf(assembly, "STA %s\n", encontrar_primeiro_atrib(raiz)->valor);
                fprintf(assembly, "LDA ZERO\n");
                fprintf(assembly, "STA TEMP_0\n");
                fprintf(assembly, "STA TEMP_1\n");
                fprintf(assembly, "STA TEMP_2\n");
                
                (*qtd_linhas) += 5;
            }

            (*qtd_linhas) += 6;
        }
        else if (strcmp(raiz->valor, "*") == 0){
            if(!proxima_operacao_soma(raiz->filho_esq) || !proxima_operacao_soma(raiz->filho_dir)){
                fprintf(assembly, "LDA %s\n", encontrar_primeiro_atrib(raiz)->valor);
                (*qtd_linhas)++;
            }

            uint8_t nome[20];
            snprintf(nome, sizeof(nome), "PULAR_%d", (*qtd_linhas) + 7);

            char buffer[12];
            snprintf(buffer, sizeof(buffer), "%d", (*qtd_linhas) + 7);

            DATA *d = criar_data(nome, "DB", (uint8_t *)buffer, false);
            adicionar_no(lista, d);

            fprintf(assembly, "STA TEMP_0\n");
            fprintf(assembly, "LDA LIT_%d\n", valor_temp);
            fprintf(assembly, "STA TEMP_1\n");
            fprintf(assembly, "LDA %s\n", nome);
            fprintf(assembly, "STA TEMP_2\n");
            fprintf(assembly, "JMP MUL\n");
            
            if(raiz->no_pai->tipo != ATRIB){
                fprintf(assembly, "STA %s\n", encontrar_primeiro_atrib(raiz)->valor);
                fprintf(assembly, "LDA ZERO\n");
                fprintf(assembly, "STA TEMP_0\n");
                fprintf(assembly, "STA TEMP_1\n");
                fprintf(assembly, "STA TEMP_2\n");
                fprintf(assembly, "STA TEMP_3\n");

                (*qtd_linhas) += 6;
            }
            
            (*qtd_linhas) += 6;
        }
        else if (strcmp(raiz->valor, "/") == 0){
            fprintf(assembly, "DIV LIT_%d\n", valor_temp);
            (*qtd_linhas)++;
        }
    } else {
        if (strcmp(raiz->valor, "+") == 0){
            fprintf(assembly, "ADD %s\n", filho->valor);
            (*qtd_linhas)++;
        }
        else if (strcmp(raiz->valor, "-") == 0){
            if(!proxima_operacao_soma(raiz->filho_esq) || !proxima_operacao_soma(raiz->filho_dir)){
                fprintf(assembly, "LDA %s\n", encontrar_primeiro_atrib(raiz)->valor);
                (*qtd_linhas)++;
            }

            uint8_t nome[20];
            snprintf(nome, sizeof(nome), "PULAR_%d", (*qtd_linhas) + 7);

            char buffer[12];
            snprintf(buffer, sizeof(buffer), "%d", (*qtd_linhas) + 7);

            DATA *d = criar_data(nome, "DB", (uint8_t *)buffer, false);
            adicionar_no(lista, d);

            fprintf(assembly, "STA TEMP_0\n");
            fprintf(assembly, "LDA %s\n", filho->valor);
            fprintf(assembly, "STA TEMP_1\n");
            fprintf(assembly, "LDA %s\n", nome);
            fprintf(assembly, "STA TEMP_2\n");
            fprintf(assembly, "JMP SUB\n");
            
            if(raiz->no_pai->tipo != ATRIB){
                fprintf(assembly, "STA %s\n", encontrar_primeiro_atrib(raiz)->valor);
                fprintf(assembly, "LDA ZERO\n");
                fprintf(assembly, "STA TEMP_0\n");
                fprintf(assembly, "STA TEMP_1\n");
                fprintf(assembly, "STA TEMP_2\n");
                
                (*qtd_linhas) += 5;
            }

            (*qtd_linhas) += 6;
        }
        else if (strcmp(raiz->valor, "*") == 0){
            if(!proxima_operacao_soma(raiz->filho_esq) || !proxima_operacao_soma(raiz->filho_dir)){
                fprintf(assembly, "LDA %s\n", encontrar_primeiro_atrib(raiz)->valor);
                (*qtd_linhas)++;
            }

            uint8_t nome[20];
            snprintf(nome, sizeof(nome), "PULAR_%d", (*qtd_linhas) + 7);

            char buffer[12];
            snprintf(buffer, sizeof(buffer), "%d", (*qtd_linhas) + 7);

            DATA *d = criar_data(nome, "DB", (uint8_t *)buffer, false);
            adicionar_no(lista, d);

            fprintf(assembly, "STA TEMP_0\n");
            fprintf(assembly, "LDA %s\n", filho->valor);
            fprintf(assembly, "STA TEMP_1\n");
            fprintf(assembly, "LDA %s\n", nome);
            fprintf(assembly, "STA TEMP_2\n");
            fprintf(assembly, "JMP MUL\n");
            
            if(raiz->no_pai->tipo != ATRIB){
                fprintf(assembly, "STA %s\n", encontrar_primeiro_atrib(raiz)->valor);
                fprintf(assembly, "LDA ZERO\n");
                fprintf(assembly, "STA TEMP_0\n");
                fprintf(assembly, "STA TEMP_1\n");
                fprintf(assembly, "STA TEMP_2\n");
                fprintf(assembly, "STA TEMP_3\n");

                (*qtd_linhas) += 6;
            }
            
            (*qtd_linhas) += 6;
        }
        else if (strcmp(raiz->valor, "/") == 0){
            fprintf(assembly, "DIV %s\n", filho->valor);
            (*qtd_linhas)++;
        }
    }

}

void gerar_codigo(NO *raiz, FILE* assembly, LISTA*data, int *valor_temp, int *qtd_linhas, bool *ja_computou){
    if(raiz == NULL) return;
    
    if(raiz->tipo == OP || raiz->tipo == ATRIB || raiz->tipo == SEQ){
        gerar_codigo(raiz->filho_esq, assembly, data, valor_temp, qtd_linhas, ja_computou);
        gerar_codigo(raiz->filho_dir, assembly, data, valor_temp, qtd_linhas, ja_computou);

        if(raiz->filho_esq->tipo == NUM && raiz->tipo != ATRIB){
            
        }
        else if(raiz->tipo == OP){
            if(raiz->filho_esq->tipo != OP && raiz->filho_dir->tipo != OP){
                fprintf(assembly, "LDA %s\n", raiz->filho_esq->valor);
                (*qtd_linhas)++;
            }
            else {
                if(raiz->filho_esq->tipo != OP){
                    if(raiz->filho_esq->tipo == NUM){
                        escrever_valor(assembly, raiz, *valor_temp, NULL, qtd_linhas, data);
                        *valor_temp = *valor_temp == 0 ? 1 : 0;
                    } 
                    //X = A + B
                    else{
                        escrever_valor(assembly, raiz, -1, raiz->filho_esq, qtd_linhas, data);
                    }
                }
            }

            if(raiz->filho_dir->tipo != OP){
                //X = A + 8
                if(raiz->filho_dir->tipo == NUM){
                    escrever_valor(assembly, raiz, *valor_temp, NULL, qtd_linhas, data);

                    *valor_temp = *valor_temp == 0 ? 1 : 0;
                } 
                //X = A + B
                else{
                    escrever_valor(assembly, raiz, -1, raiz->filho_dir, qtd_linhas, data);
                }
            }
          
        }

        if(raiz->tipo == ATRIB){
            DATA *d = (DATA *) buscar_no(data, raiz->valor);

            if(d->expressao){
                fprintf(assembly, "STA %s\n", raiz->valor);
                (*qtd_linhas)++;
            }
            
            return;
        }

    } else {
        if(raiz->tipo == NUM){
            if(raiz->no_pai->tipo == OP && !(*ja_computou)){
                fprintf(assembly, "LDA LIT_%s\n", raiz->valor);
                (*qtd_linhas)++;

                (*ja_computou) = true;
                *valor_temp = *valor_temp == 0 ? 1 : 0;
            } else {
                escrever_valor(assembly, raiz->no_pai, atoi(raiz->valor), NULL, qtd_linhas, data);
            }
        }
    } 
}

int gerar_subtracao(FILE *assembly, int *qtd_linhas){
    int valor_offset = *qtd_linhas;

    fprintf(assembly, "LDA TEMP_0\n");
    fprintf(assembly, "NOT\n");
    fprintf(assembly, "ADD Y\n");
    fprintf(assembly, "ADD TEMP_1\n");
    fprintf(assembly, "STA TEMP_0\n");
    fprintf(assembly, "JMP TEMP_2\n");

    (*qtd_linhas) += 6;    
    return valor_offset;
}

int gerar_multiplicacao(FILE *assembly, int *qtd_linhas){
    int valor_offset = *qtd_linhas;

    fprintf(assembly, "LDA TEMP_0\n");
    fprintf(assembly, "JN %d\n", valor_offset + 4);
    fprintf(assembly, "JZ %d\n", valor_offset + 18);
    fprintf(assembly, "JMP %d\n", valor_offset + 12);
    fprintf(assembly, "NOT\n");
    fprintf(assembly, "ADD Y\n");
    fprintf(assembly, "STA TEMP_0\n");
    fprintf(assembly, "LDA TEMP_1\n");
    fprintf(assembly, "NOT\n");
    fprintf(assembly, "ADD Y\n");
    fprintf(assembly, "STA TEMP_1\n");
    fprintf(assembly, "JMP %d\n", valor_offset);
    fprintf(assembly, "ADD Z\n");
    fprintf(assembly, "STA TEMP_0\n");
    fprintf(assembly, "LDA TEMP_3\n");
    fprintf(assembly, "ADD TEMP_1\n");
    fprintf(assembly, "STA TEMP_3\n");
    fprintf(assembly, "JMP %d\n", valor_offset);
    fprintf(assembly, "LDA TEMP_3\n");
    fprintf(assembly, "JMP TEMP_2\n");
    (*qtd_linhas) += 20;

    return valor_offset;
}

void detectar_literais(NO *no, LISTA *lista_data, bool *operacoes) {
    if (no == NULL) return;

    if (no->tipo == NUM && no->no_pai->tipo != ATRIB) {
        uint8_t nome[20];
        snprintf(nome, sizeof(nome), "LIT_%s", no->valor);

        if (buscar_no(lista_data, nome) == NULL) {
            adicionar_no(lista_data, criar_data(nome, "DB", no->valor, false));
        }
    }

    if(no->tipo == OP){
        if(strcmp(no->valor, "-") == 0)
            operacoes[0] = true;
        else if(strcmp(no->valor, "*") == 0)
            operacoes[1] = true;
        else if(strcmp(no->valor, "/") == 0)
            operacoes[2] = true;    
    }

    detectar_literais(no->filho_esq, lista_data, operacoes);
    detectar_literais(no->filho_dir, lista_data, operacoes);
}

void copiar_e_substituir(const char* origem_nome, const char* destino_nome, int offset_mul, int offset_sub) {
    FILE *origem = fopen(origem_nome, "r");
    FILE *destino = fopen(destino_nome, "a");

    if (!origem || !destino) {
        perror("Erro ao abrir os arquivos");
        return;
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), origem)) {
        if (strstr(linha, "MUL")) {
            fprintf(destino, "JMP %d\n", offset_mul);
        } else if (strstr(linha, "SUB")) {
            fprintf(destino, "JMP %d\n", offset_sub);
        } else {
            fputs(linha, destino); 
        }
    }

    fclose(origem);
    fclose(destino);
}

void criar_arquivo(LISTA *lista_data, NO *raiz){
    FILE *assembly = fopen("programa.asm", "w");
    FILE *assembly_temp = fopen("programa_temp.asm", "w");

    if(assembly == NULL || assembly_temp == NULL ){
        printf("Nao foi possivel criar o arquivo\n");
        exit(EXIT_FAILURE);
    }
    
    bool operacoes[3] = {false};
    detectar_literais(raiz, lista_data, operacoes);

    //adicionando variaveis temporarias para expressoes com literais
    if(operacoes[0] || operacoes[1] || operacoes[2]){
        adicionar_no(lista_data, criar_data("TEMP_0", "DB", "?", false));
        adicionar_no(lista_data, criar_data("TEMP_1", "DB", "?", false));
        adicionar_no(lista_data, criar_data("TEMP_2", "DB", "?", false));
        adicionar_no(lista_data, criar_data("TEMP_3", "DB", "?", false));
        adicionar_no(lista_data, criar_data("Y", "DB", "1", false));
        adicionar_no(lista_data, criar_data("Z", "DB", "-1", false));
        adicionar_no(lista_data, criar_data("ZERO", "DB", "0", false));
    }
    
    int i = 0;
    int qtd_linhas = 0;
    bool ja_computou = false;
    int offset_mul = 0;
    int offset_sub = 0;
    gerar_codigo(raiz, assembly_temp, lista_data, &i, &qtd_linhas, &ja_computou);
    
    fprintf(assembly, "; Assembly gerado do programa \"%s\"\n\n", raiz->valor);
    gerar_data(lista_data, assembly);
    fprintf(assembly, "\n.CODE\n.ORG 0\n");

    fprintf(assembly_temp, "HLT\n");
    qtd_linhas += 2;

    if(operacoes[0]){
        offset_sub = gerar_subtracao(assembly_temp, &qtd_linhas);
        printf("OFFSET LINHAS: %d\n", offset_sub);
    }

    if(operacoes[1]){
        offset_mul = gerar_multiplicacao(assembly_temp, &qtd_linhas);
        printf("OFFSET LINHAS: %d\n", offset_mul);
    }

    fclose(assembly_temp);
    fclose(assembly);
    copiar_e_substituir("programa_temp.asm", "programa.asm", offset_mul, offset_sub);
}

