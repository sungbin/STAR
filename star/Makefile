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

$(BIN): $(BINDIR) main star
	$(CC) $(OBJS) -g -o $(BIN)

$(BINDIR):
	mkdir -p $(BINDIR)

main : src/main.c
	$(CC) -c -g -o bin/main.o src/main.c

star : src/star.c
	$(CC) -c -g -o bin/star.o src/star.c
  
clean:
	rm -rf $(BINDIR)

