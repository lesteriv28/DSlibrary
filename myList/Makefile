CC = gcc
CFLAGS = -g -std=c99 -Wall -Werror

all: test_list test
%.o : %.c
		$(CC) -c $(CFLAGS) $<

test_list: myList.o test_list.o
		$(CC) -o test_list myList.o test_list.o

test: test_list
		./test_list

clean:
		rm -f core *.o test_list