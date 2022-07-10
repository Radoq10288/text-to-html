BINDIR=bin
OBJDIR=obj
SRCDIR=src
TESTDIR=tests

BIN=$(BINDIR)/make-th
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
	rm maketh-win-source.tar

clean-test:
	rm $(TESTDIR)/*.o $(TESTDIR)/bin/*

tar-source:
	tar -cvf maketh-win-source.tar include/sput-1.4.0/* src/* tests/* .gitignore COPYING Makefile README.md run-test.sh

tar-release: tar-debug

tar-debug:
	tar -cvf maketh-win-debug.tar bin/* COPYING README.md

install:
	install -d ~/local/share/make-th
	install bin/make-th ~/local/bin/make-th
	install COPYING ~/local/share/make-th/
	install README.md ~/local/share/make-th/

uninstall:
	rm -fr ~/local/bin/make-th
	rm ~/local/share/make-th/*
	rmdir ~/local/share/make-th


