# Executor de Compilador

Este repositório contém a implementação de um **executor para um compilador**, desenvolvido em **C**. O projeto inclui a interpretação e execução de instruções, manipulando arquivos de memória e utilizando um sistema de instruções pré-definido.

## Tecnologias Utilizadas
- Linguagem: **C**
- Build System: **Makefile**

## Estrutura do Repositório
```
executor/
├── Makefile                 # Script de compilação do projeto
├── executor.c                # Implementação do executor
├── executor.h                # Definição de funções do executor
├── instruction.c             # Implementação das instruções
├── instruction.h             # Definições de instruções
├── main.c                    # Arquivo principal do projeto
├── aula01.mem                # Arquivo de memória para teste
├── multiplicacao_entrega.mem  # Arquivo de memória com instruções
└── neander                   # Implementação de suporte ao projeto
```

## Como Compilar e Executar
1. Clone o repositório:
   ```sh
   git clone https://github.com/Erick141004/compiladores.git
   ```
2. Navegue até o diretório do projeto:
   ```sh
   cd compiladores/executor
   ```
3. Compile o projeto utilizando `make`:
   ```sh
   make
   ```
4. Execute o programa:
   ```sh
   make run
   ```
5. Para limpar os arquivos gerados:
   ```sh
   make clean
   ```

## Autor
Desenvolvido por **Erick141004**

