# Variables de compilación
CC = gcc
CFLAGS = -Wall -fPIC -g
LDFLAGS = -lrt -lpthread
LIBRARY_NAME = libclaves.so
SERVER_EXEC = servidor-mq
CLIENT_EXEC = app-cliente

# Directorios
SRC_DIR = .
OBJ_DIR = obj
BIN_DIR = bin

# Archivos fuente
CLAVES_SRC = $(SRC_DIR)/claves.c
SERVER_SRC = $(SRC_DIR)/servidor-mq.c
CLIENT_SRC = $(SRC_DIR)/app-cliente.c
PROXY_SRC = $(SRC_DIR)/proxy-mq.c
HEADER_SRC = $(SRC_DIR)/claves.h

# Archivos objeto
CLAVES_OBJ = $(OBJ_DIR)/claves.o
SERVER_OBJ = $(OBJ_DIR)/servidor-mq.o
CLIENT_OBJ = $(OBJ_DIR)/app-cliente.o
PROXY_OBJ = $(OBJ_DIR)/proxy-mq.o

# Regla principal
all: $(LIBRARY_NAME) $(SERVER_EXEC) $(CLIENT_EXEC)

# Crear la biblioteca dinámica (solo proxy)
$(LIBRARY_NAME): $(PROXY_OBJ)
	@mkdir -p $(BIN_DIR)
	@echo "Creando la biblioteca dinámica $(LIBRARY_NAME)"
	$(CC) -shared -o $(LIBRARY_NAME) $(PROXY_OBJ) $(LDFLAGS)

# Compilar el servidor con claves.c
$(SERVER_EXEC): $(SERVER_OBJ) $(CLAVES_OBJ)
	@mkdir -p $(BIN_DIR)
	@echo "Compilando el servidor $(SERVER_EXEC)"
	$(CC) -o $(BIN_DIR)/$(SERVER_EXEC) $(SERVER_OBJ) $(CLAVES_OBJ) $(LDFLAGS)

# Compilar el cliente
$(CLIENT_EXEC): $(CLIENT_OBJ) $(LIBRARY_NAME)
	@mkdir -p $(BIN_DIR)
	@echo "Compilando el cliente $(CLIENT_EXEC)"
	$(CC) -o $(BIN_DIR)/$(CLIENT_EXEC) $(CLIENT_OBJ) -L. -lclaves $(LDFLAGS) -Wl,-rpath,.

# Compilación de los archivos .c a .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER_SRC)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Limpiar los archivos generados
clean:
	@echo "Limpiando los archivos generados"
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(LIBRARY_NAME)

# Eliminar todo, incluyendo los archivos generados
# filepath: /home/zakku/Desktop/sd_evaluable1-main/MakeFile
distclean: clean
	@echo "Limpiando todo"
	rm -f $(BIN_DIR)/$(SERVER_EXEC) $(BIN_DIR)/$(CLIENT_EXEC) $(LIBRARY_NAME)

.PHONY: all clean distclean
