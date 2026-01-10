### Equipe
#### Mateus Nascimento da Mota - 571044
#### Arthur Pereira dos Santos - 579364


## Simulador de Fila de Banco

 O projeto implementa um sistema de simulação de atendimento de Banco usando filas FIFO e uma árvore binária de busca

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
Para executar o código após o `make` você deve chamar `./simulador`, dessa forma:<br>
```bash
usuario@usuario:/Trabalho_Programa-o $ ./simulador x
```
Onde x é um sufixo do arquivo de entrada que você deseja executar

Considerando os 100 arquivos de teste existe um jeito mais dinâmico, usando um script bash que executa o simulador para todos os arquivos e gera um diff individual (se houver). Para usa-lo chame <code>./rodar.sh</code>, sem nenhum argumento, logo você verá algo como isso:
```bash
usuario@usuario:/Trabalho_Programa-o $ ./rodar.sh 
Executando simulador 0001...
Simulacao concluida. Tempo total: 11430 minutos.
OK: Sem diferenças para 0001
Executando simulador 0002...
Simulacao concluida. Tempo total: 8483 minutos.
OK: Sem diferenças para 0002
Executando simulador 0003...
Simulacao concluida. Tempo total: 26610 minutos.
OK: Sem diferenças para 0003
...
```

Observação: é esperado que os arquivos de entrada e saída que vão ser executados estejam em diretórios `/entradas` e `/saidas`, isso pode ser mudado alterando as variáveis nomeEntrada e nomeSaida em `main.c`.