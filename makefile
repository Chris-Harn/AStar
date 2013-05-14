# Make file for SDL A* Implementation
#
# Compile using this: "make"
# Run using "./main"

all: main
		@echo Compiling the program...
		@echo Use "./main" to run.
main: main.o
		g++ -o main main.o -Wall -ansi -pedantic -O1 -lSDL -lSDL_ttf
main.o: main.cpp
		g++ -c main.cpp defines.h -Wall -ansi -pedantic -O1 -lSDL -lSDL_ttf
text.o: text.cpp
		g++ -c text.cpp text.h -Wall -ansi -pedantic -O1 -lSDL -lSDL_ttf

clean:
		-rm -f *.o *.gch *.swn *.swo main *.out *.txt
