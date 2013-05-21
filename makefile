# Make file for SDL A* Implementation
#
# Compile using this: "make"
# Run using "./main"

all: main
		@echo Compiling the program...
		@echo Use "./main" to run.
main: main.o graphics.o timer.o
		g++ -o main main.o graphics.o timer.o -Wall -ansi -pedantic -O1 -lSDL -lSDL_ttf -pg -std=c++0x
main.o: main.cpp
		g++ -c main.cpp defines.h -Wall -ansi -pedantic -O1 -lSDL -lSDL_ttf -pg -std=c++0x
graphics.o: graphics.cpp
		g++ -c graphics.cpp graphics.h -Wall -ansi -pedantic -O1 -lSDL -lSDL_ttf -pg -std=c++0x
timer.o: timer.cpp
		g++ -c timer.cpp timer.h -Wall -ansi -pedantic -O1 -lSDL -lSDL_ttf -pg -std=c++0x


clean:
		-rm -f *.o *.gch *.swn *.swo main *.out *.txt *.swp *.gch
