# Makefile for curses-based 8BitConverter
# author - Thomas Cushman

# Macros ========================================

CC=clang++
CFLAGS=-std=c++11 -O2 -g -Wconversion -Wall -Wextra -Wconversion -Werror -pedantic-errors

INC=-Iinc -Iproject_inc
LIBS=-lncurses -Llib -lmidifile -lportaudio -lrt -lm -lasound -ljack -pthread

SDIR=./project_src/
HDIR=./project_inc/
OUTDIR=./clang/
ERASE=rm
OBJECTS=$(OUTDIR)main.o \
	$(OUTDIR)menu.o \
	$(OUTDIR)oscillator.o \
	$(OUTDIR)note.o \
	$(OUTDIR)midiparser.o \
	$(OUTDIR)timer.o \
	$(OUTDIR)channel.o \
	$(OUTDIR)debug.o \
	$(OUTDIR)adsr.o
EXE=Pangolin.exe

# Targets ========================================

$(EXE) : $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBS) -o $(EXE)

$(OUTDIR)main.o : $(SDIR)main.cpp
	$(CC) $(CFLAGS) $(INC) -c $(SDIR)main.cpp -o $(OUTDIR)main.o
	
$(OUTDIR)menu.o : $(SDIR)Menu.cpp $(HDIR)Menu.hpp
	$(CC) $(CFLAGS) $(INC) -c $(SDIR)Menu.cpp -o $(OUTDIR)menu.o
	
$(OUTDIR)oscillator.o : $(SDIR)Oscillator.cpp $(HDIR)Oscillator.hpp
	$(CC) $(CFLAGS) $(INC) -c $(SDIR)Oscillator.cpp -o $(OUTDIR)oscillator.o
	
$(OUTDIR)note.o : $(SDIR)Note.cpp $(HDIR)Note.hpp
	$(CC) $(CFLAGS) $(INC) -c $(SDIR)Note.cpp -o $(OUTDIR)note.o
	
$(OUTDIR)midiparser.o : $(SDIR)MidiParser.cpp $(HDIR)MidiParser.hpp
	$(CC) $(CFLAGS) $(INC) -c $(SDIR)MidiParser.cpp -o $(OUTDIR)midiparser.o
	
$(OUTDIR)timer.o : $(SDIR)Timer.cpp $(HDIR)Timer.hpp
	$(CC) $(CFLAGS) $(INC) -c $(SDIR)Timer.cpp -o $(OUTDIR)timer.o
	
$(OUTDIR)channel.o : $(SDIR)Channel.cpp $(HDIR)Channel.hpp
	$(CC) $(CFLAGS) $(INC) -c $(SDIR)Channel.cpp -o $(OUTDIR)channel.o
	
$(OUTDIR)debug.o : $(SDIR)Debug.cpp $(HDIR)Debug.hpp
	$(CC) $(CFLAGS) $(INC) -c $(SDIR)Debug.cpp -o $(OUTDIR)debug.o
	
$(OUTDIR)adsr.o : $(SDIR)ADSR.cpp $(HDIR)ADSR.hpp
	$(CC) $(CFLAGS) $(INC) -c $(SDIR)ADSR.cpp -o $(OUTDIR)adsr.o
	
clean :
	$(ERASE) $(EXE) $(OBJECTS)
	
rebuild :
	make -B
