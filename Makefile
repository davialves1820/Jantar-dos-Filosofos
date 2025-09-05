# Compilador
CC = gcc

# Diretórios
INCLUDE_DIR = include
SRC_DIR = src
BUILD_DIR = build

# Flags de compilação
CFLAGS = -Wall -I$(INCLUDE_DIR) -g

# Flags de linkagem (para bibliotecas como a de threads)
LDFLAGS = -lpthread

# Lista de arquivos-fonte (encontra todos os .c em src/ automaticamente)
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Gera a lista de arquivos objeto (.o) correspondentes em build/
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# Nome do executável final
TARGET = app

# Regra padrão: compila tudo
all: $(TARGET)

# Regra para linkar os objetos e criar o executável final
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Regra para compilar cada .c em seu respectivo .o no diretório build/
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para limpar os arquivos gerados
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Instalação do programa no sistema
install:
	cp $(TARGET) /usr/local/bin/

# Desinstalação do programa do sistema
uninstall:
	rm -f /usr/local/bin/$(TARGET)

# Declara as regras que não geram arquivos
.PHONY: all clean install uninstall