# Compilador
CC = gcc

# Carpetas
SRC_DIR = .
OBJ_DIR = obj
BIN_DIR = bin

# Archivos fuente y objetos
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

# Nombre del ejecutable
TARGET = $(BIN_DIR)/programa.exe

# Flags de compilación
CFLAGS = -Wall

# Regla principal
all: $(BIN_DIR) $(OBJ_DIR) $(TARGET)

# Cómo construir el ejecutable
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@

# Cómo compilar los .c en .o dentro de obj
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Crear carpetas si no existen
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Ejecutar el programa
run: all
	./$(TARGET)

# Limpiar archivos compilados
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) Debug debug Build build

# Reiniciar el programa (limpia y recompila)
reset: clean all
