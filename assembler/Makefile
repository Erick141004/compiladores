# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -I./estrutura_de_dados -I./extracao_dados -I./criar_arquivo -I./interface
TARGET = assembler
SOURCES = main.c \
          interface/interface.c \
          extracao_dados/data.c \
          extracao_dados/code.c \
          estrutura_de_dados/lista.c \
          criar_arquivo/create_file.c

OBJECTS = $(SOURCES:.c=.o)

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	clear
	./$(TARGET) teste.txt

clean:
	rm -f $(TARGET) $(OBJECTS)