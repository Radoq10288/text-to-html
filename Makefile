BINDIR=bin
OBJDIR=obj
SRCDIR=src

OS=$(shell uname -o)
ifeq ($(OS), Msys)
BINFILE=make-t2h.exe
endif
ifeq ($(OS), GNU/Linux)
BINFILE=make-t2h
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
	rmdir $(OBJDIR) $(BINDIR)
	rm make-t2h-mingw32-source.tar
	rm make-t2h-mingw32-release.tar
	rm make-t2h-mingw32-debug.tar


build-test:
	cd tests && $(MAKE)

run-test:
	cd tests/bin && ./test

clean-test:
	cd tests && $(MAKE) clean

distclean-test:
	cd tests && $(MAKE) distclean


tar-source:
	tar -cvf make-t2h-mingw32-source.tar include/sput-1.4.0/* src/* tests/* .gitignore COPYING Makefile README.md run-test.sh

tar-release:
	tar -cvf make-t2h-mingw32-release.tar bin/* COPYING README.md

tar-debug:
	tar -cvf make-t2h-mingw32-debug.tar bin/* COPYING README.md


install:
	install -d ~/local/bin
	install -d ~/local/share/make-t2h
	install bin/$(BINFILE) ~/local/bin/$(BINFILE)
	install COPYING ~/local/share/make-t2h/
	install README.md ~/local/share/make-t2h/

uninstall:
	rm ~/local/bin/$(BINFILE)
	rm ~/local/share/make-t2h/*
	rmdir ~/local/share/make-t2h


