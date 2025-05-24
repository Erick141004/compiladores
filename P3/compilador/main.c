#include <stdlib.h>
#include <stdio.h>
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

    if(fgets(buffer, sizeof(buffer), stdin) == NULL){
        printf("Não foi possivel ler a expressão\n");
        return 1;
    }

    wchar_t wbuffer[100];
    size_t teste = mbstowcs(wbuffer, buffer, 100);
 
    if (teste == (size_t)-1) {
        fprintf(stderr, "Erro na conversão de string multibyte para wide-char\n");
        return 1;
    }

    Token token;
    int pos_atual = 0;

    token = proximo_token(wbuffer, &pos_atual);
    NO* no = parse_atribuicao(wbuffer, &pos_atual, &token);

    criar_arquivo(no);
    limpar_arvore(no);

    return 0;
}