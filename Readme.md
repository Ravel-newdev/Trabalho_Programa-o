
# Variáveis de Compilação
CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = simulador

# Lista de arquivos objeto (Membro 3 coordena isso)
OBJS = main.o fila_fifo.o logtree.o escalonador.o

# Detecção do Sistema Operacional
ifeq ($(OS),Windows_NT)
    # Comandos para Windows
    RM = del /Q
    EXEC = $(TARGET).exe
else
    # Comandos para Linux/Unix
    RM = rm -f
    EXEC = $(TARGET)
endif

# Regra principal (Compilar)
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

# Regras de compilação individual (.c -> .o)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Comando para limpar arquivos temporários (make clean)
clean:
	$(RM) *.o $(EXEC) saida-*.txt

# Atalho para rodar (ex: make run X=0001)
run: all
	./$(EXEC) $(X)