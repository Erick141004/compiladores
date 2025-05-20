# Compilador de Expressões Matemáticas

Este projeto é um compilador desenvolvido em C para a linguagem Neander, focado em traduzir **expressões matemáticas simples** para um código Assembly executável. O compilador gera um código `.asm` e permite a execução do mesmo por meio de um interpretador (executor). Por limitação de tempo, a **operação de divisão ainda não foi implementada**.

## 🧠 Funcionalidades

- Análise sintática de expressões aritméticas.
- Geração de código em Assembly Neander.
- Suporte a operações com literais e variáveis.
- Implementação das operações:
  - Soma
  - Subtração
  - Multiplicação
- Execução do binário gerado (via executor externo).

---

## 📁 Estrutura do Projeto

```
.
├── assembler/                  # Responsável por gerar o arquivo Assembly final
│   ├── criar_arquivo/         # Criação e escrita no arquivo .asm
│   ├── estrutura_de_dados/    # Lista ligada para armazenar variáveis e literais
│   ├── extracao_dados/        # Análise e extração de dados e código
│   ├── interface/             # Interface entre parser e geração de código
│   ├── main.c                 # Entrada principal do assembler
├── compilador/                # Parte principal do compilador
│   ├── arvore.c/h             # Estrutura da árvore sintática
│   ├── parser.c/h             # Parser descendente recursivo
│   ├── tokens.c/h             # Analisador léxico
│   ├── lista.c/h              # Manipulação de lista de tokens
│   ├── codificador.c/h        # Geração do código intermediário
│   ├── create_file.c/h        # Criação de arquivos temporários
│   ├── main.c                 # Entrada principal do compilador
├── executor/                  # Executor de código Assembly (não exibido nas imagens)
│   └── [arquivos necessários para executar o .bin gerado]
├── programa.asm               # Arquivo final gerado em Assembly
├── programa_temp.asm         # Código temporário intermediário
├── programa.mem              # Memória utilizada no Neander
├── Makefile                  # Compilação automatizada do projeto
```

---

## ⚙️ Como Compilar

Você pode compilar o projeto utilizando o `make` a partir das pastas `assembler`, `compilador` e `executor`:

```bash
# Dentro da pasta compilador/
make

# Dentro da pasta assembler/
make

# Dentro da pasta executor/
make
```

> Certifique-se de estar na pasta correta ao executar o `make`, pois existem dois arquivos `Makefile`, um para o compilador e outro para o assembler.

Caso queira rodar o programa de uma vez, também pode se usar o comando `make run` na raiz do projeto.

---

## ▶️ Como Executar

1. Compile o código fonte com o `make`.
2. Rode o compilador passando uma expressão ou script.
3. O arquivo `programa.asm` será gerado.
4. O arquivo `.asm` será passado para o assembler, que irá gerar um binário.
5. O binário pode ser executado pelo interpretador Neander (presente na pasta `executor`).

---

## Exemplos utilizados para rodar o compilador

### exemplo1.txt
``` txt
PROGRAMA "programa":
INICIO
A = 4
B = 5
RES = A + B
FIM
```

### exemplo2.txt
``` txt
PROGRAMA "programa":
INICIO
A = 2 + 3
B = 4
RES = (A + B) * A * B
FIM
```

## 🚫 Observações

- A operação de **divisão (`/`) ainda não foi implementada**, mas o sistema está preparado para facilitar sua futura inclusão.
- O projeto está estruturado de forma modular, facilitando a manutenção e expansão.
- Ambos os exemplos utilizados funcionaram tanto para o compilador quanto para o assembly, porém no caso do exemplo2, quando foi rodado no executor, ele entrou em loop infinito e não foi possível alterar antes da data de entrega. Também rodei ambos os exemplos gerados pelo meu assembler no `Neander` e por la, funcionou como o esperado.
- Para váriaveis literais, não é possivel realizar outras operações além da adição, pois não houve tempo hábil para a implementação, porém também será fácil incluir esse fator.
---

## 👨‍💼 Autoria

Projeto acadêmico desenvolvido como parte do curso de Ciência da Computação.  
Autor: Erick Costa Reimberg de Lima
