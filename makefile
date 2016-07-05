# Makefile for curses-based 8BitConverter
# author - Thomas Cushman

# Macros ========================================

CC=clang++
CFLAGS=-std=c++11 -O2 -g -Wconversion -Wall -Wextra -Wconversion -Werror -pedantic-errors

INC=-Iinc
LIBS=-lncurses -Llib -lmidifile -lportaudio -lrt -lm -lasound -ljack -pthread

OUTDIR=./clang/
ERASE=rm
OBJECTS=$(OUTDIR)main.o $(OUTDIR)menu.o $(OUTDIR)oscillator.o $(OUTDIR)note.o $(OUTDIR)midiparser.o $(OUTDIR)timer.o $(OUTDIR)channel.o $(OUTDIR)debug.o $(OUTDIR)adsr.o
EXE=Pangolin.exe

# Targets ========================================

$(EXE) : $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBS) -o $(EXE)

$(OUTDIR)main.o : main.cpp
	$(CC) $(CFLAGS) $(INC) -c main.cpp -o $(OUTDIR)main.o
	
$(OUTDIR)menu.o : Menu.cpp Menu.hpp
	$(CC) $(CFLAGS) $(INC) -c Menu.cpp -o $(OUTDIR)menu.o
	
$(OUTDIR)oscillator.o : Oscillator.cpp Oscillator.hpp
	$(CC) $(CFLAGS) $(INC) -c Oscillator.cpp -o $(OUTDIR)oscillator.o
	
$(OUTDIR)note.o : Note.cpp Note.hpp
	$(CC) $(CFLAGS) $(INC) -c Note.cpp -o $(OUTDIR)note.o
	
$(OUTDIR)midiparser.o : MidiParser.cpp MidiParser.hpp
	$(CC) $(CFLAGS) $(INC) -c MidiParser.cpp -o $(OUTDIR)midiparser.o
	
$(OUTDIR)timer.o : Timer.cpp Timer.hpp
	$(CC) $(CFLAGS) $(INC) -c Timer.cpp -o $(OUTDIR)timer.o
	
$(OUTDIR)channel.o : Channel.cpp Channel.hpp
	$(CC) $(CFLAGS) $(INC) -c Channel.cpp -o $(OUTDIR)channel.o
	
$(OUTDIR)debug.o : Debug.hpp
	$(CC) $(CFLAGS) $(INC) -c Debug.cpp -o $(OUTDIR)debug.o
	
$(OUTDIR)adsr.o : ADSR.cpp ADSR.hpp
	$(CC) $(CFLAGS) $(INC) -c ADSR.cpp -o $(OUTDIR)adsr.o
	
clean :
	$(ERASE) $(EXE) $(OBJECTS)
	
rebuild :
	make -B
