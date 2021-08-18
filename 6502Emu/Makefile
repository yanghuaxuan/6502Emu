CC := g++
CXXFLAGS := -std=c++17 -Wall -pedantic -pedantic-errors
LDFLAGS := -lncurses
VPATH = src:${srcPath}

objects := RAM.o CPU.o emuUI.o main.o

RAM.o: RAM.cpp
CPU.o: CPU.cpp
emuUI.o: emuUI.cpp
main.o: main.cpp

all: $(objects)
	$(CC) $(CXXFLAGS) $(LDFLAGS) $^ -o emu6502
clean:
	rm -f *.o all

