CC      = gcc
INCLDIR = include/
BINDIR  = bin/
SRCDIR  = src/

_BIN    = main
BIN     = $(addprefix $(BINDIR), $(_BIN))

SRC     = $(wildcard src/*.c)
INCL    = $(wildcard include/*.h)
_OBJS   = $(patsubst src/%.c, %.o, $(SRC))
OBJS    = $(addprefix $(BINDIR), $(_OBJS))

all: $(BIN)

$(BIN): $(BINDIR) main print_file_list_recursively
	$(CC) $(OBJS) -o $(BIN)

$(BINDIR):
	mkdir -p $(BINDIR)

main : src/main.c
	$(CC) -c -o bin/main.o src/main.c

print_file_list_recursively : src/print_file_list_recursively.c
	$(CC) -c -o bin/print_file_list_recursively.o src/print_file_list_recursively.c
  
clean:
	rm -rf $(BINDIR)

