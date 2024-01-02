CC = gcc
CFLAGS = -g -std=c99 -Wall -Werror

all: test_mystring test
%.o : %.c
		$(CC) -c $(CFLAGS) $<

test_mystring: myString.o test_mystring.o
		$(CC) -o test_mystring myString.o test_mystring.o

test: test_mystring
		./test_mystring

clean:
		rm -f core *.o test_mystring
