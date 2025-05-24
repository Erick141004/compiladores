# Analisador Léxico e Gramatical - Linguagem Customizada

Este projeto consiste na implementação de uma gramática no formato **BNF (Backus-Naur Form)** para uma linguagem fictícia mais completa, incluindo suporte a declarações de variáveis, estruturas condicionais, laços de repetição, funções e expressões aritméticas.

Além da gramática, o projeto inclui um **analisador léxico (lexer)** implementado em C, responsável por identificar os tokens da linguagem.

---

## 📁 Estrutura de Diretórios

```
P2/
├── gramatica_bnf.txt      # Definição formal da gramática da linguagem
├── tokens.c               # Implementação do lexer em C
└── tokens.h               # Header com definições dos tokens e funções auxiliares
```

---

## 🧠 Gramática

A gramática está definida no arquivo `gramatica_bnf.txt` e segue o formato BNF. Ela descreve os elementos básicos da linguagem, incluindo:

- Declaração de programas (`PROGRAMA`)
- Início e fim do programa (`INICIO`, `FIM`)
- Tipos primitivos (`int`, `float`, `char`)
- Variáveis e expressões
- Estruturas de decisão (`if`, `else if`, `else`)
- Estruturas de repetição (`while`, `do while`, `for`)
- Declaração e chamada de funções
- Operações aritméticas com precedência e parênteses

Exemplo de trecho suportado pela gramática:

```txt
PROGRAMA "exemplo":
INICIO
int x = 10
if (x > 5) {
    float y = x * 2.5
}
FIM
```

---

## 🧾 Funcionalidades do Lexer

O arquivo `tokens.c` contém a implementação do analisador léxico que:

- Reconhece palavras-chave, identificadores, números, operadores e símbolos
- Suporta espaços e tabulações como separadores
- Trabalha em conjunto com a gramática definida para análise sintática futura

---

## 🚧 Status do Projeto

- ✅ Gramática definida em BNF
- ✅ Lexer implementado
- ⬜ Parser sintático (futuro)
- ⬜ Analisador semântico (futuro)
- ⬜ Interpretador/compilador final (futuro)

---

## 📌 Observações

- A linguagem foi projetada para fins acadêmicos.
- A gramática pode evoluir conforme novos recursos sejam adicionados.
- A implementação foca em uma linguagem parecida com C, com sintaxe simples e clara.

---