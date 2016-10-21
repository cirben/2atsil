CC=g++ -g -std=c++11
BAKEFLAGS=-lcryptopp
CFLAGS=-c -Wall -I ./headers
OBJDIR=obj/
SRCDIR=src/
HDIR=headers/
NAME=k2

$(OBJDIR)main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp -pthread -o $(OBJDIR)main.o $(BAKEFLAGS)

$(OBJDIR)converter.o: $(SRCDIR)converter.cpp $(HDIR)converter.h
	$(CC) $(CFLAGS) $(SRCDIR)converter.cpp -pthread -o $(OBJDIR)converter.o $(BAKEFLAGS)

$(OBJDIR)Decryptor.o: $(SRCDIR)Decryptor.cpp $(HDIR)Decryptor.h
	$(CC) $(CFLAGS) $(SRCDIR)Decryptor.cpp -pthread -o $(OBJDIR)Decryptor.o $(BAKEFLAGS)

$(OBJDIR)data.o: $(SRCDIR)data.cpp $(HDIR)data.h
	$(CC) $(CFLAGS) $(SRCDIR)data.cpp -pthread -o $(OBJDIR)data.o $(BAKEFLAGS)

$(OBJDIR)fload.o: $(SRCDIR)fload.cpp $(HDIR)fload.h
	$(CC) $(CFLAGS) $(SRCDIR)fload.cpp -pthread -o $(OBJDIR)fload.o $(BAKEFLAGS)

$(OBJDIR)block128.o: $(SRCDIR)block128.cpp $(HDIR)block128.h
	$(CC) $(CFLAGS) $(SRCDIR)block128.cpp -pthread -o $(OBJDIR)block128.o $(BAKEFLAGS)

all: $(OBJDIR)converter.o $(OBJDIR)Decryptor.o $(OBJDIR)data.o $(OBJDIR)fload.o $(OBJDIR)block128.o $(OBJDIR)main.o
const:
	make all --no-print-directory
	$(CC) obj/*.o -o $(NAME) -pthread $(BAKEFLAGS)
	ctags -R --languages=C,C++ --c++-kinds=+p --fields=+iaS --extra=+q ./
clean:
	rm -d -r $(OBJDIR)* *.o $(NAME)
