BINDIR=bin
OBJDIR=obj
SRCDIR=src

OS=$(shell uname -o)
ifeq ($(OS), Msys)
BINFILE=txt2html.exe
endif
ifeq ($(OS), GNU/Linux)
BINFILE=txt2html
endif

BIN=$(BINDIR)/$(BINFILE)
OBJ=$(OBJDIR)/*.o
CFILES=$(SRCDIR)/*.c

CC=gcc
LDFLAGS=-L./lib -lfstring_replace -lstring_replace

debug: CFLAGS=-g -pedantic -Wall
debug: build-lib build compile

release: CFLAGS=-Os -Wall
release: build-lib-rel build compile

compile: $(BIN)
$(BIN) : $(OBJ)
	$(CC) -o $(BIN) $(OBJ) $(LDFLAGS)

build: $(OBJ)
$(OBJ) : $(CFILES)
	$(CC) -c $(CFILES) $(CFLAGS) -I./include

	@mkdir -p $(OBJDIR)
	@mkdir -p $(BINDIR)
	@mv *.o $(OBJDIR)/


clean: build-lib-clean
	rm $(OBJ) $(BINDIR)/* ./lib/*.a

distclean: clean
	rmdir $(OBJDIR)
	ifeq *.html { rm *.html }
	ifeq *.tar {
		rm txt2html-source.tar
		rm txt2html-release.tar
		rm txt2html-debug.tar
	}


# To unit test
build-test: build-lib
	cd tests && $(MAKE)

run-test:
	cd tests/bin && ./test

clean-test: build-lib-clean
	cd tests && $(MAKE) clean

distclean-test:
	cd tests && $(MAKE) distclean


# Building the static library and putting the '*.a' file in the 'lib' folder.
build-lib:
	cd src/find-string && $(MAKE)
	cd src/copy-sub-string && $(MAKE)

	cp src/find-string/libfind_string.a ./lib
	cp src/copy-sub-string/libcopy_sub_string.a ./lib


	cd src/string-replace && $(MAKE)
	cp src/string-replace/libstring_replace.a ./lib


	cp src/find-string/*.o src/file-string-replace/
	cp src/copy-sub-string/*.o src/file-string-replace/
	cp src/string-replace/*.o src/file-string-replace/


	cd src/file-string-replace && $(MAKE)
	cp src/file-string-replace/libfstring_replace.a ./lib

build-lib-rel:
	cd src/find-string && $(MAKE) release
	cd src/copy-sub-string && $(MAKE) release

	cp src/find-string/libfind_string.a ./lib
	cp src/copy-sub-string/libcopy_sub_string.a ./lib


	cd src/string-replace && $(MAKE) release
	cp src/string-replace/libstring_replace.a ./lib


	cp src/find-string/*.o src/file-string-replace/
	cp src/copy-sub-string/*.o src/file-string-replace/
	cp src/string-replace/*.o src/file-string-replace/


	cd src/file-string-replace && $(MAKE) release
	cp src/file-string-replace/libfstring_replace.a ./lib

build-lib-clean:
	cd src/find-string && $(MAKE) clean
	cd src/copy-sub-string && $(MAKE) clean
	cd src/string-replace && $(MAKE) clean
	cd src/file-string-replace && $(MAKE) clean


# Archive all the files
tar-source:
	tar -cvf txt2html-mingw32-source.tar include/sput-1.4.0/* src/* tests/* .gitignore COPYING Makefile README.md run-test.sh

tar-release:
	tar -cvf txt2html-mingw32-release.tar bin/* COPYING README.md

tar-debug:
	tar -cvf txt2html-mingw32-debug.tar bin/* COPYING README.md


# Install the program
install:
	install -d ~/local/bin
	install -d ~/local/share/txt2html
	install bin/$(BINFILE) ~/local/bin/$(BINFILE)
	install COPYING ~/local/share/txt2html/
	install README.md ~/local/share/txt2html/

uninstall:
	rm ~/local/bin/$(BINFILE)
	rm ~/local/share/txt2html/*
	rmdir ~/local/share/txt2html


