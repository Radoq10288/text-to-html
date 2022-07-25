BINDIR=bin
OBJDIR=obj
SRCDIR=src
TESTDIR=tests

BIN=$(BINDIR)/make-t2h
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
	rm $(TESTDIR)/*.o $(TESTDIR)/bin/*

tar-source:
	tar -cvf make-t2h-mingw32-source.tar include/sput-1.4.0/* src/* tests/* .gitignore COPYING Makefile README.md run-test.sh

tar-release:
	tar -cvf make-t2h-mingw32-release.tar bin/* COPYING README.md

tar-debug:
	tar -cvf make-t2h-mingw32-debug.tar bin/* COPYING README.md

install:
	install -d ~/local/bin
	install -d ~/local/share/make-t2h
	install bin/make-t2h ~/local/bin/make-t2h
	install COPYING ~/local/share/make-t2h/
	install README.md ~/local/share/make-t2h/

uninstall:
	rm -fr ~/local/bin/make-t2h
	rm ~/local/share/make-t2h/*
	rmdir ~/local/share/make-t2h


