debug: CFLAGS=-g -pedantic -Wall -Wextra -std=c18
debug: build compile

release: CFLAGS=-Os -Wall -std=c18
release: build compile

compile:
	ar rcs libfind_string.a -o find_string.o

build:
	gcc -c find_string.c $(CFLAGS)

clean:
	rm *.a *.o