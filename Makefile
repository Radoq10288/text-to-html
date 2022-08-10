BINDIR=bin
OBJDIR=obj
SRCDIR=src
TESTDIR=tests

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


test: $(TESTDIR)/bin/test
$(TESTDIR)/bin/test: $(TESTDIR)/*.o
	$(CC) -o $(TESTDIR)/bin/test $(TESTDIR)/*.o

$(TESTDIR)/*.o: $(TESTDIR)/src/*.c $(SRCDIR)/strrep.c $(SRCDIR)/strrep.h
	$(CC) -c $(TESTDIR)/src/*.c $(SRCDIR)/strrep.c -g -pedantic -Wall

	@mv *.o $(TESTDIR)/
	

clean:
	rm $(OBJ) $(BINDIR)/*

distclean: clean
	rmdir $(OBJDIR) $(BINDIR)
	rm make-t2h-mingw32-source.tar
	rm make-t2h-mingw32-release.tar
	rm make-t2h-mingw32-debug.tar

clean-test:
	rm $(TESTDIR)/*.o $(TESTDIR)/bin/* new-testfile.txt new-a-testfile.txt

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


