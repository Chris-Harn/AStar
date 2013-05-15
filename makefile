# Make file for SDL A* Implementation
#
# Compile using this: "make"
# Run using "./main"

all: main
		@echo Compiling the program...
		@echo Use "./main" to run.
main: main.o text.o
		g++ -o main main.o text.o -Wall -ansi -pedantic -O1 -lSDL -lSDL_ttf -std=c++0x
main.o: main.cpp
		g++ -c main.cpp defines.h -Wall -ansi -pedantic -O1 -lSDL -lSDL_ttf -std=c++0x
text.o: text.cpp
		g++ -c text.cpp text.h -Wall -ansi -pedantic -O1 -lSDL -lSDL_ttf -std=c++0x

clean:
		-rm -f *.o *.gch *.swn *.swo main *.out *.txt *.swp *.gch
