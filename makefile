# Make file for SDL A* Implementation
#
# Compile using this: "make"
# Run using "./main"

all: main
		@echo Compiling the program...
		@echo Use "./main" to run.
main: main.o graphics.o
		g++ -o main main.o graphics.o -Wall -ansi -pedantic -O1 -lSDL -lSDL_ttf
main.o: main.cpp
		g++ -c main.cpp defines.h -Wall -ansi -pedantic -O1 -lSDL -lSDL_ttf
graphics.o: graphics.cpp
		g++ -c graphics.cpp graphics.h -Wall -ansi -pedantic -O1 -lSDL -lSDL_ttf -std=c++0x

clean:
		-rm -f *.o *.gch *.swn *.swo main *.out *.txt *.swp *.gch
