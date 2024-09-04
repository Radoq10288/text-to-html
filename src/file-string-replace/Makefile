LDFLAGS=-L./lib -lfind_string -lcopy_sub_string

debug: CFLAGS=-g -pedantic -Wall -Wextra -std=c18
debug: build compile

release: CFLAGS=-Os -Wall -std=c18
release: build compile

compile:
	ar rcs libfstring_replace.a -o *.o

build:
	gcc -c file_string_replace.c $(CFLAGS) -I ../../include

clean:
	rm *.a *.o