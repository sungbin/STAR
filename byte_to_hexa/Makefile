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

$(BIN): $(BINDIR) main byte_to_hexa
	$(CC) $(OBJS) -o $(BIN)

$(BINDIR):
	mkdir -p $(BINDIR)

main : src/main.c
	$(CC) -c -o bin/main.o src/main.c

byte_to_hexa : src/byte_to_hexa.c
	$(CC) -c -o bin/byte_to_hexa.o src/byte_to_hexa.c
  
clean:
	rm -rf $(BINDIR)

test: $(BIN)
	gcc test/atoi.c -o bin/test_atoi
	gcc test/timeout.c -o bin/test_timeout
