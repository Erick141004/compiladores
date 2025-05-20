.PHONY: all clean run compilador assembler executor

COMPILADOR_DIR = compilador
ASSEMBLER_DIR = assembler
EXECUTOR_DIR = executor

COMPILADOR_BIN = $(COMPILADOR_DIR)/compilador
ASSEMBLER_BIN = $(ASSEMBLER_DIR)/assembler
EXECUTOR_BIN = $(EXECUTOR_DIR)/neander

all: compilador assembler executor

compilador:
	$(MAKE) -C $(COMPILADOR_DIR)

assembler:
	$(MAKE) -C $(ASSEMBLER_DIR)

executor:
	$(MAKE) -C $(EXECUTOR_DIR)

clean:
	$(MAKE) -C $(COMPILADOR_DIR) clean
	$(MAKE) -C $(ASSEMBLER_DIR) clean
	$(MAKE) -C $(EXECUTOR_DIR) clean

run: all
	@echo "===> Compilando .lpn para .asm"
	./$(COMPILADOR_BIN) $(COMPILADOR_DIR)/programa.lpn

	@echo "===> Compilando .asm para .mem"
	cp $(COMPILADOR_DIR)/programa.asm $(ASSEMBLER_DIR)/programa.asm
	./$(ASSEMBLER_BIN) $(ASSEMBLER_DIR)/programa.asm

	@echo "===> Executando .mem"
	cp $(ASSEMBLER_DIR)/programa.mem $(EXECUTOR_DIR)/programa.mem
	./$(EXECUTOR_BIN) $(EXECUTOR_DIR)/programa.mem
