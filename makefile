# Makefile for curses-based 8BitConverter
# author - Thomas Cushman

# Macros ========================================

CC=clang++
CFLAGS=-std=c++11 -O2 -g -Wconversion -Wall -Wextra -Wconversion -Werror -pedantic-errors

INC=-Iinc
LIBS=-lncurses -Llib -lmidifile -lportaudio -lrt -lm -lasound -ljack -pthread

OUTDIR=./clang/
ERASE=rm
OBJECTS=$(OUTDIR)main.o $(OUTDIR)menu.o $(OUTDIR)note.o $(OUTDIR)system.o
EXE=8BC

# Targets ========================================

$(EXE) : $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBS) -o $(EXE)

$(OUTDIR)main.o : main.cpp
	$(CC) $(CFLAGS) $(INC) -c main.cpp -o $(OUTDIR)main.o
	
$(OUTDIR)menu.o : Menu.cpp Menu.hpp
	$(CC) $(CFLAGS) $(INC) -c Menu.cpp -o $(OUTDIR)menu.o
	
$(OUTDIR)note.o : Note.cpp Note.hpp
	$(CC) $(CFLAGS) $(INC) -c Note.cpp -o $(OUTDIR)note.o
	
$(OUTDIR)system.o : System.cpp System.hpp
	$(CC) $(CFLAGS) $(INC) -c System.cpp -o $(OUTDIR)system.o
	
clean :
	$(ERASE) $(EXE) $(OBJECTS)

