
#variáveis de Compilação
CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = simulador


OBJS = main.o fila_fifo.o logtree.o escalonador.o


ifeq ($(OS),Windows_NT)
    RM = del /Q
    EXEC = $(TARGET).exe
else
    RM = rm -f
    EXEC = $(TARGET)
endif


all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

# regras de compilação individual (.c -> .o)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

#para limpar arquivos temporários make clean
clean:
	$(RM) *.o $(EXEC) saida-*.txt


run: all
	./$(EXEC) $(X)