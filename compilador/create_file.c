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

void gerar_codigo(NO *raiz, FILE* assembly, LISTA*data, int *valor_temp){
    if(raiz == NULL) return;
    
    if(raiz->tipo == OP || raiz->tipo == ATRIB || raiz->tipo == SEQ){
        gerar_codigo(raiz->filho_esq, assembly, data, valor_temp);
        gerar_codigo(raiz->filho_dir, assembly, data, valor_temp);

        if(raiz->filho_esq->tipo == NUM && raiz->tipo != ATRIB){
            fprintf(assembly, "LDA TEMP_%d\n", *valor_temp);

            //X = 7 + 8
            if(raiz->filho_dir->tipo == NUM){
                if(*valor_temp == 0)
                    *valor_temp = 1;
                else
                    *valor_temp = 0;

                if (strcmp(raiz->valor, "+") == 0)
                    fprintf(assembly, "ADD TEMP_%d\n", *valor_temp);
                else if (strcmp(raiz->valor, "-") == 0)
                    fprintf(assembly, "SUB TEMP_%d\n", *valor_temp);
                else if (strcmp(raiz->valor, "*") == 0)
                    fprintf(assembly, "MUL TEMP_%d\n", *valor_temp);
                else if (strcmp(raiz->valor, "/") == 0)
                    fprintf(assembly, "DIV TEMP_%d\n", *valor_temp);
            } 
            //X = 7 + A
            else{
                if (strcmp(raiz->valor, "+") == 0)
                    fprintf(assembly, "ADD %s\n", raiz->filho_dir->valor);
                else if (strcmp(raiz->valor, "-") == 0)
                    fprintf(assembly, "SUB %s\n", raiz->filho_dir->valor);
                else if (strcmp(raiz->valor, "*") == 0)
                    fprintf(assembly, "MUL %s\n", raiz->filho_dir->valor);
                else if (strcmp(raiz->valor, "/") == 0)
                    fprintf(assembly, "DIV %s\n", raiz->filho_dir->valor);
            }
        }
        else if(raiz->tipo == OP){
            if(raiz->filho_esq->tipo != OP && raiz->filho_dir->tipo != OP)
                fprintf(assembly, "LDA %s\n", raiz->filho_esq->valor);
            else {
                if(raiz->filho_esq->tipo != OP){
                    if(raiz->filho_esq->tipo == NUM){
                        if (strcmp(raiz->valor, "+") == 0)
                            fprintf(assembly, "ADD TEMP_%d\n", *valor_temp);
                        else if (strcmp(raiz->valor, "-") == 0)
                            fprintf(assembly, "SUB TEMP_%d\n", *valor_temp);
                        else if (strcmp(raiz->valor, "*") == 0)
                            fprintf(assembly, "MUL TEMP_%d\n", *valor_temp);
                        else if (strcmp(raiz->valor, "/") == 0)
                            fprintf(assembly, "DIV TEMP_%d\n", *valor_temp);
                    
                        if(*valor_temp == 0)
                            *valor_temp = 1;
                        else
                            *valor_temp = 0;
                    } 
                    //X = A + B
                    else{
                        if (strcmp(raiz->valor, "+") == 0)
                            fprintf(assembly, "ADD %s\n", raiz->filho_esq->valor);
                        else if (strcmp(raiz->valor, "-") == 0)
                            fprintf(assembly, "SUB %s\n", raiz->filho_esq->valor);
                        else if (strcmp(raiz->valor, "*") == 0)
                            fprintf(assembly, "MUL %s\n", raiz->filho_esq->valor);
                        else if (strcmp(raiz->valor, "/") == 0)
                            fprintf(assembly, "DIV %s\n", raiz->filho_esq->valor);
                    }
                }
            }

            if(raiz->filho_dir->tipo != OP){
                //X = A + 8
                if(raiz->filho_dir->tipo == NUM){
                    if (strcmp(raiz->valor, "+") == 0)
                        fprintf(assembly, "ADD TEMP_%d\n", *valor_temp);
                    else if (strcmp(raiz->valor, "-") == 0)
                        fprintf(assembly, "SUB TEMP_%d\n", *valor_temp);
                    else if (strcmp(raiz->valor, "*") == 0)
                        fprintf(assembly, "MUL TEMP_%d\n", *valor_temp);
                    else if (strcmp(raiz->valor, "/") == 0)
                        fprintf(assembly, "DIV TEMP_%d\n", *valor_temp);
                
                    if(*valor_temp == 0)
                        *valor_temp = 1;
                    else
                        *valor_temp = 0;
                } 
                //X = A + B
                else{
                    if (strcmp(raiz->valor, "+") == 0)
                        fprintf(assembly, "ADD %s\n", raiz->filho_dir->valor);
                    else if (strcmp(raiz->valor, "-") == 0)
                        fprintf(assembly, "SUB %s\n", raiz->filho_dir->valor);
                    else if (strcmp(raiz->valor, "*") == 0)
                        fprintf(assembly, "MUL %s\n", raiz->filho_dir->valor);
                    else if (strcmp(raiz->valor, "/") == 0)
                        fprintf(assembly, "DIV %s\n", raiz->filho_dir->valor);
                }
            }
          
        }

        if(raiz->tipo == ATRIB){
            DATA *d = (DATA *) buscar_no(data, raiz->valor);

            if(d->expressao)
                fprintf(assembly, "STA %s\n", raiz->valor);
            
            return;
        }

    } else {
        if(raiz->tipo == NUM){
            if(raiz->no_pai->tipo == OP){
                fprintf(assembly, "LDA TEMP_%d\nADD %s\nSTA TEMP_%d\n", *valor_temp, raiz->valor, *valor_temp);
                if(*valor_temp == 0)
                    *valor_temp = 1;
                else
                    *valor_temp = 0;
            }
        }
    } 
}

void criar_arquivo(LISTA *lista_data, NO *raiz){
    FILE *assembly = fopen("programa.asm", "w");

    if(assembly == NULL){
        printf("Nao foi possivel criar o arquivo\n");
        exit(EXIT_FAILURE);
    }

    //adicionando variaveis temporarias para expressoes com literais
    adicionar_no(lista_data, criar_data("TEMP_0", "DB", "?", false));
    adicionar_no(lista_data, criar_data("TEMP_1", "DB", "?", false));

    fprintf(assembly, "; Assembly gerado do programa \"%s\"\n\n", raiz->valor);
    gerar_data(lista_data, assembly);
    fprintf(assembly, "\n.CODE\n.ORG 0\n");
    int i = 0;
    gerar_codigo(raiz, assembly, lista_data, &i);
    fprintf(assembly, "HLT");
}

