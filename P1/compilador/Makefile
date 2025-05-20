CC = gcc
CFLAGS = -Wall -Wextra

SOURCES = main.c parser.c tokens.c codificador.c arvore.c lista.c create_file.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = compilador

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJECTS) $(TARGET)