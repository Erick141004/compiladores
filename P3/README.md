
# Brainfuck Expression Compiler & Executor

Este projeto consiste em um **compilador e executor de expressões matemáticas** escritas em linguagem natural no formato:

```
CRÉDITO = 5 + 3 * 7
```

O compilador traduz expressões com operações aritméticas para código **Brainfuck**, respeitando a **precedência de operadores** e o uso de **parênteses**.

---

## 📁 Estrutura do Projeto

- `compilador/`: Responsável por:
  - Análise léxica e sintática da expressão.
  - Conversão para código Brainfuck.
  - Escrita do código gerado em um arquivo.

- `executor/`: Responsável por:
  - Execução do código Brainfuck gerado.

---

## 🚀 Como Executar

Você pode executar uma expressão diretamente com:

```bash
echo "CRÉDITO = 5 + 3 * 7" | ./compilador/bfc | ./executor/bfe
```

> ⚠️ **Importante**: o comando deve ser executado a partir da **pasta raiz** do projeto.

---

## 💡 Exemplo de Saída

Entrada:
```
CRÉDITO = 5 + 3 * 7
```

Saída:
```
CRÉDITO= 26
```

> A saída sempre será exibida no formato:  
> **NOME_VARIÁVEL= RESULTADO**

---

## ✅ Funcionalidades

- Suporte às quatro operações básicas: `+`, `-`, `*`, `/`.
- Suporte ao uso de **parênteses**.
- Compilação da expressão para **Brainfuck**.
- Execução do código Brainfuck.
- **Suporte a UTF-8**: nomes de variáveis com acentuação, emojis e outros caracteres especiais são aceitos e corretamente tratados.

---

## ⚠️ Limitações Conhecidas

- Apenas **divisões inteiras** são suportadas.
  - Expressões como `7 / 2` podem causar **loop infinito**.
- **Números negativos não são suportados**.

---

## 🛠️ Como Compilar

### 📦 Usando `make` (Recomendado)

Na pasta raiz do projeto:

```bash
make         # Compila os dois executáveis
make clean   # Remove os arquivos binários gerados
```

Isso criará:

- `compilador/bfc`: o compilador Brainfuck
- `executor/bfe`: o interpretador Brainfuck

### 🔧 Compilação Manual (sem make)

```bash
# Compilar o compilador
gcc -o compilador/bfc compilador/*.c

# Compilar o executor
gcc -o executor/bfe executor/*.c
```

### 📌 Requisitos

Certifique-se de ter o `gcc` e o `make` instalados. 

---

## 👨‍💼 Autoria

Projeto acadêmico desenvolvido como parte do curso de Ciência da Computação.  
Autor: Erick Costa Reimberg de Lima
