# Makefile for curses-based 8BitConverter
# author - Thomas Cushman

# Macros ========================================

#CC=clang++
CFLAGS=-std=c++11 -O2 -g -Wconversion -Wall -Wextra -Wconversion -Werror -pedantic-errors

INC=-Iinc -Iproject_inc
LIBS=-Llib -lncurses -lmidifile -lportaudio -lrt -lm -lasound -ljack -lpthread -L/usr/lib64 -lstdc++ 

SDIR=./project_src/
HDIR=./project_inc/
ERASE=rm
OBJECTS=main.o \
	oscillator.o \
	note.o \
	midiparser.o \
	timer.o \
	channel.o \
	debug.o \
	adsr.o
EXE=Pangolin.exe

# Targets ========================================

$(EXE) : $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBS) -o $(EXE) && make clean_objs

main.o : $(SDIR)main.cpp
	$(CC) $(CFLAGS) $(INC) -c $(SDIR)main.cpp -o main.o
	
oscillator.o : $(SDIR)Oscillator.cpp $(HDIR)Oscillator.hpp
	$(CC) $(CFLAGS) $(INC) -c $(SDIR)Oscillator.cpp -o oscillator.o
	
note.o : $(SDIR)Note.cpp $(HDIR)Note.hpp
	$(CC) $(CFLAGS) $(INC) -c $(SDIR)Note.cpp -o note.o
	
midiparser.o : $(SDIR)MidiParser.cpp $(HDIR)MidiParser.hpp
	$(CC) $(CFLAGS) $(INC) -c $(SDIR)MidiParser.cpp -o midiparser.o
	
timer.o : $(SDIR)Timer.cpp $(HDIR)Timer.hpp
	$(CC) $(CFLAGS) $(INC) -c $(SDIR)Timer.cpp -o timer.o
	
channel.o : $(SDIR)Channel.cpp $(HDIR)Channel.hpp
	$(CC) $(CFLAGS) $(INC) -c $(SDIR)Channel.cpp -o channel.o
	
debug.o : $(SDIR)Debug.cpp $(HDIR)Debug.hpp
	$(CC) $(CFLAGS) $(INC) -c $(SDIR)Debug.cpp -o debug.o
	
adsr.o : $(SDIR)ADSR.cpp $(HDIR)ADSR.hpp
	$(CC) $(CFLAGS) $(INC) -c $(SDIR)ADSR.cpp -o adsr.o
	
clean :
	$(ERASE) $(EXE) $(OBJECTS)

clean_objs :
	$(ERASE) $(OBJECTS)
	
rebuild :
	make -B

debug :
	CC=clang++ make $(EXE) && CC=g++ make $(EXE)
