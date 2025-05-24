# Diretórios
COMPILADOR_DIR = compilador
EXECUTOR_DIR = executor

# Arquivos fonte
COMPILADOR_SRCS = $(wildcard $(COMPILADOR_DIR)/*.c)
EXECUTOR_SRCS = $(wildcard $(EXECUTOR_DIR)/*.c)

# Binários
COMPILADOR_BIN = $(COMPILADOR_DIR)/bfc
EXECUTOR_BIN = $(EXECUTOR_DIR)/bfe

# Compilador e flags
CC = gcc
CFLAGS = -Wall -O2

# Alvo padrão
all: $(COMPILADOR_BIN) $(EXECUTOR_BIN)

# Compilar o compilador
$(COMPILADOR_BIN): $(COMPILADOR_SRCS)
	$(CC) $(CFLAGS) -o $@ $^

# Compilar o executor
$(EXECUTOR_BIN): $(EXECUTOR_SRCS)
	$(CC) $(CFLAGS) -o $@ $^

# Limpar arquivos binários
clean:
	rm -f $(COMPILADOR_BIN) $(EXECUTOR_BIN)

.PHONY: all clean