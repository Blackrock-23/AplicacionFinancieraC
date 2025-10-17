# Nombre del compilador
CC = gcc

# Flags de compilación (puedes agregar -Wall para ver advertencias)
CFLAGS = -Wall

# Nombre del ejecutable final
TARGET = programa

# Busca todos los archivos .c del directorio actual
SRC = $(wildcard *.c)

# Crea una lista de archivos objeto .o a partir de los .c
OBJ = $(SRC:.c=.o)

# ===============================
# Regla principal (compila todo)
# ===============================
all: $(TARGET)

# Cómo generar el ejecutable a partir de los objetos
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Cómo generar los .o a partir de los .c
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# ===============================
# Ejecutar el programa
# ===============================
run: all
	./$(TARGET)

# ===============================
# Limpiar archivos intermedios
# ===============================
clean:
	rm -f $(OBJ) $(TARGET)

# ===============================
# Resetear el proyecto
# (limpia y recompila todo)
# ===============================
reset: clean all
