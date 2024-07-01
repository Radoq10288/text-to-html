debug: CFLAGS=-g -pedantic -Wall -Wextra -std=c18
debug: build compile

release: CFLAGS=-O2 -Wall -std=c18
release: build compile

compile:
	ar rcs libfile_string_replace.a -o file_string_replace.o

build:
	gcc -c file_string_replace.c $(CFLAGS) -I ../../include

clean:
	rm *.a *.o