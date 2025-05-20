#include <stdlib.h>
#include <stdio.h>
#include "lista.h"
#include "tokens.h"
#include "arvore.h"
#include "parser.h"
#include <wctype.h>
#include <locale.h>
#include <wchar.h>
#include "create_file.h"

int main(){
    char buffer[100];
    setlocale(LC_ALL, "");

    if(fgets(buffer, sizeof(buffer), stdin) != NULL){
        printf("Expressão lida: %s\n", buffer);
    } else {
        printf("Não foi possivel ler a expressão\n");
        return 1;
    }

    wchar_t wbuffer[100];
    size_t teste = mbstowcs(wbuffer, buffer, 100);
 
    if (teste == (size_t)-1) {
        fprintf(stderr, "Erro na conversão de string multibyte para wide-char\n");
        return 1;
    }

    wprintf(L"Teste: %ls\n", wbuffer);

    Token token;
    int pos_atual = 0;
    LISTA *variaveis = criar_lista();

    token = proximo_token(wbuffer, &pos_atual);
    NO* no = parse_atribuicao(wbuffer, &pos_atual, &token, variaveis);

    imprimir_arvore(no, 1);
    imprimir_lista(variaveis);
    criar_arquivo(no);
    limpar_arvore(no);
    deletar_lista(variaveis);

    return 0;
}