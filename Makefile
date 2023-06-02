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

debug: CFLAGS=-g -pedantic -Wall
debug: build compile

release: CFLAGS=-O2 -Wall
release: build compile

compile: $(BIN)
$(BIN) : $(OBJ)
	$(CC) -o $(BIN) $(OBJ)

build: $(OBJ)
$(OBJ) : $(CFILES)
	$(CC) -c $(CFILES) $(CFLAGS)

	@mkdir -p $(OBJDIR)
	@mkdir -p $(BINDIR)
	@mv *.o $(OBJDIR)/


clean:
	rm $(OBJ) $(BINDIR)/*

distclean: clean
	rmdir $(OBJDIR)
	rm txt2html-source.tar
	rm txt2html-release.tar
	rm txt2html-debug.tar


build-test:
	cd tests && $(MAKE)

run-test:
	cd tests/bin && ./test

clean-test:
	cd tests && $(MAKE) clean

distclean-test:
	cd tests && $(MAKE) distclean


tar-source:
	tar -cvf txt2html-mingw32-source.tar include/sput-1.4.0/* src/* tests/* .gitignore COPYING Makefile README.md run-test.sh

tar-release:
	tar -cvf txt2html-mingw32-release.tar bin/* COPYING README.md

tar-debug:
	tar -cvf txt2html-mingw32-debug.tar bin/* COPYING README.md


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


