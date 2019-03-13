CC = gcc
CFLAGS = -ansi -Wall -g -I$(IDIR)

IDIR = ./includes/
SRCDIR = ./src/
BINDIR = ./bin/

SOURCES = $(SRCDIR)*.c

all: $(BINDIR)contactList

$(BINDIR)contactList: $(BINDIR)main.o $(BINDIR)functions.o
	$(CC) -o $@ $^

$(BINDIR)%.o: $(SRCDIR)%.c $(IDIR)header.h
	$(CC) $(CFLAGS) -c -o $@ $<

run:
	./bin/contactList

clean:
	rm ./bin/*o ./contactList