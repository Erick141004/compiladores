# Projeto Assembler

## Descrição
Este projeto implementa um montador (assembler) para processar arquivos de entrada contendo seções `DATA` e `CODE`. Ele analisa e extrai informações dessas seções, armazena os dados em listas e gera um arquivo de saída correspondente.

## Estrutura do Projeto

```
.
├── Makefile
├── main.c
├── estrutura_de_dados/
│   ├── lista.c
│   ├── lista.h
├── extracao_dados/
│   ├── data.c
│   ├── data.h
│   ├── code.c
│   ├── code.h
├── criar_arquivo/
│   ├── create_file.c
│   ├── create_file.h
├── interface/
│   ├── interface.c
│   ├── interface.h
```

## Compilação e Execução

### Requisitos
- GCC instalado
- Make instalado

### Compilar o projeto

Execute o seguinte comando no terminal:
```sh
make
```

### Executar o programa

Para rodar o montador, use:
```sh
./assembler <arquivo_de_entrada>
```
Exemplo:
```sh
./assembler teste.txt
```

### Limpar arquivos compilados

Para remover arquivos objeto e binários gerados:
```sh
make clean
```

## Funcionamento
O programa:
1. Abre e lê o arquivo de entrada em formato binário.
2. Processa o conteúdo, identificando comandos `DATA` e `CODE`.
3. Armazena os dados em listas encadeadas.
4. Gera um arquivo de saída a partir dos dados extraídos.
5. Imprime os dados processados na tela.

## Principais Arquivos
- `main.c`: Ponto de entrada do programa.
- `data.h` e `data.c`: Manipulação de seções `DATA`.
- `code.h` e `code.c`: Manipulação de seções `CODE`.
- `lista.h` e `lista.c`: Implementação da estrutura de lista encadeada.
- `create_file.h` e `create_file.c`: Responsável pela criação do arquivo de saída.
- `interface.h` e `interface.c`: Funções de interface para interação com o usuário.

## Autor
Desenvolvido por Erick Costa.

