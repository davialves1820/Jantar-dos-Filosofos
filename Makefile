# Compilador
CC = gcc

# Diretórios
INCLUDE_DIR = include
SRC_DIR = src
BUILD_DIR = build

# Flags de compilação
CFLAGS = -Wall -I$(INCLUDE_DIR) -g

# Lista de arquivos-fonte
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Gera os arquivos .o correspondentes em build/
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# Nome do executável final
TARGET = app

# Regra padrão
all: $(TARGET)

# Como criar o executável
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Como compilar os .c em .o (no diretório build)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Instalação
install:
	cp $(TARGET) /usr/local/bin/

# Desinstalação
uninstall:
	rm -f /usr/local/bin/$(TARGET)

.PHONY: all clean install uninstall
