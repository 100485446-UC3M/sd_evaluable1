# Variables de compilación
CC = gcc
CFLAGS = -Wall -fPIC -g
LDFLAGS = -lrt -lpthread
LIBRARY_NAME = libclaves.so
SERVER_EXEC = servidor-mq
CLIENT_EXEC1 = app-cliente1
CLIENT_EXEC2 = app-cliente2
CLIENT_EXEC3 = app-cliente3

# Directorios
SRC_DIR = .
OBJ_DIR = obj
BIN_DIR = bin

# Archivos fuente
SERVER_SRC = $(SRC_DIR)/servidor-mq.c
CLIENT_SRC1 = $(SRC_DIR)/app-cliente1.c
CLIENT_SRC2 = $(SRC_DIR)/app-cliente2.c
CLIENT_SRC3 = $(SRC_DIR)/app-cliente3.c
PROXY_SRC = $(SRC_DIR)/proxy-mq.c
HEADER_SRC = $(SRC_DIR)/claves.h

# Archivos objeto
SERVER_OBJ = $(OBJ_DIR)/servidor-mq.o
CLIENT_OBJ1 = $(OBJ_DIR)/app-cliente1.o
CLIENT_OBJ2 = $(OBJ_DIR)/app-cliente2.o
CLIENT_OBJ3 = $(OBJ_DIR)/app-cliente3.o
PROXY_OBJ = $(OBJ_DIR)/proxy-mq.o

# Regla principal
all: $(LIBRARY_NAME) $(SERVER_EXEC) $(CLIENT_EXEC1) $(CLIENT_EXEC2) $(CLIENT_EXEC3)

# Crear la biblioteca dinámica
$(LIBRARY_NAME): $(PROXY_OBJ)
	@echo "Creando la biblioteca dinámica $(LIBRARY_NAME)"
	$(CC) -shared -o $(LIBRARY_NAME) $(PROXY_OBJ) $(LDFLAGS)

# Compilar el servidor
$(SERVER_EXEC): $(SERVER_OBJ) $(LIBRARY_NAME)
	@echo "Compilando el servidor $(SERVER_EXEC)"
	$(CC) -o $(BIN_DIR)/$(SERVER_EXEC) $(SERVER_OBJ) $(LDFLAGS)

# Compilar los clientes
$(CLIENT_EXEC): $(CLIENT_OBJ1) $(LIBRARY_NAME)
	@echo "Compilando el cliente $(CLIENT_EXEC)"
	$(CC) -o $(BIN_DIR)/$(CLIENT_EXEC) $(CLIENT_OBJ1) $(LDFLAGS)

$(CLIENT_EXEC2): $(CLIENT_OBJ2) $(LIBRARY_NAME)
	@echo "Compilando el cliente $(CLIENT_EXEC2)"
	$(CC) -o $(BIN_DIR)/$(CLIENT_EXEC2) $(CLIENT_OBJ2) $(LDFLAGS)

$(CLIENT_EXEC3): $(CLIENT_OBJ3) $(LIBRARY_NAME)
	@echo "Compilando el cliente $(CLIENT_EXEC3)"
	$(CC) -o $(BIN_DIR)/$(CLIENT_EXEC3) $(CLIENT_OBJ3) $(LDFLAGS)

# Compilación de los archivos .c a .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER_SRC)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Limpiar los archivos generados
clean:
	@echo "Limpiando los archivos generados"
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(LIBRARY_NAME)

# Eliminar todo, incluyendo los archivos generados
distclean: clean
	@echo "Limpiando todo"
	rm -f $(BIN_DIR)/$(SERVER_EXEC) $(BIN_DIR)/$(CLIENT1_EXEC) $(BIN_DIR)/$(CLIENT_EXEC2) $(BIN_DIR)/$(CLIENT_EXEC3)

.PHONY: all clean distclean
