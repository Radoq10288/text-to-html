debug: CFLAGS=-g -pedantic -Wall -Wextra -std=c18
debug: build compile

release: CFLAGS=-O2 -Wall -std=c18
release: build compile

compile:
	ar rcs libcopy_sub_string.a -o copy_sub_string.o

build:
	gcc -c copy_sub_string.c $(CFLAGS)

clean:
	rm *.a *.o