
#variáveis de Compilação
CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = simulador


OBJS = main.o fila_fifo.o logtree.o escalonador.o


ifeq ($(OS),Windows_NT)
    # Comandos para Windows
    RM = del /Q
    EXEC = $(TARGET).exe
else
    # Comandos para Linux/Unix
    RM = rm -f
    EXEC = $(TARGET)
endif

#regra principal (Compilar)
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

# regras de compilação individual (.c -> .o)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

#para limpar arquivos temporários make clean
clean:
	$(RM) *.o $(EXEC) saida-*.txt

# atalho para rodar ex: make run X=0001
run: all
	./$(EXEC) $(X)