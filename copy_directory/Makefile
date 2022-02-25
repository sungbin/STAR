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

$(BIN): $(BINDIR) main copy_directory
	$(CC) $(OBJS) -o $(BIN)

$(BINDIR):
	mkdir -p $(BINDIR)

main : src/main.c
	$(CC) -c -o bin/main.o src/main.c

copy_directory : src/copy_directory.c
	$(CC) -c -o bin/copy_directory.o src/copy_directory.c
  
clean:
	rm -rf $(BINDIR)

