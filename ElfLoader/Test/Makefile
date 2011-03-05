CC=gcc
CFLAGS=-c -g -W -Wall -ansi -pedantic
LDFLAGS=
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
EXEC_NAME=main
RM=rm -f

all: $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(EXEC_NAME)
	$(RM) *.o *~ \#*\#

%.o: %.c
	$(CC) $(CFLAGS) $<

clean:
	rm *.o

