
### Mateus Nascimento da Mota - 571044


## Simulador de Fila de Banco

## O projeto implementa um sistema de simulação de atendimento de Banco usando filas FIFO e uma árvore binária de busca

## Compilação e Execução

```makefile
CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = simulador

## lista de arquivos objeto 
OBJS = main.o fila_fifo.o logtree.o escalonador.o

## verificando SO
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

## regras de compilação individual .c -> .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) *.o $(EXEC) saida-*.txt

run: all
	./$(EXEC) $(X)

```