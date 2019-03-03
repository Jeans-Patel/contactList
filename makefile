CC = gcc
CFLAGS = -ansi -Wall -I$(IDIR)

IDIR = ./includes/
SRCDIR = ./src/
BINDIR = ./bin/

SOURCES = $(SRCDIR)*.c

all: $(BINDIR)contactList

$(BINDIR)contactList: $(BINDIR)main.o $(BINDIR)functions.o
	$(CC) $(BINDIR)main.o $(BINDIR)functions.o -o $@

$(BINDIR)main.o: $(SRCDIR)main.c
	$(CC) $(CFLAGS) -c $(SRCDIR)main.c -o $@

$(BINDIR)functions.o: $(SRCDIR)functions.c
	$(CC) $(CFLAGS) -c $(SRCDIR)functions.c -o $@

clean:
	rm ./bin/*o ./contactList