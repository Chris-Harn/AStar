# Make file for SDL A* Implementation
#
# Compile using this: "make"
# Run using "./main"

all: main
		@echo Compiling the program...
		@echo Use "./main" to run.
main: main.o graphics.o timer.o square.o location.o path.o
		g++ -o main main.o graphics.o timer.o square.o location.o path.o -Wall -ansi -pedantic -O1 -lSDL -lSDL_ttf -lSDL_gfx -std=c++0x
main.o: main.cpp
		g++ -c main.cpp defines.h -Wall -ansi -pedantic -O1 -lSDL -lSDL_ttf -lSDL_gfx -std=c++0x
graphics.o: graphics.cpp
		g++ -c graphics.cpp graphics.h -Wall -ansi -pedantic -O1 -lSDL -lSDL_ttf -lSDL_gfx -std=c++0x
timer.o: timer.cpp
		g++ -c timer.cpp timer.h -Wall -ansi -pedantic -O1 -lSDL -lSDL_ttf -lSDL_gfx -std=c++0x
square.o: square.cpp
		g++ -c square.cpp square.h -Wall -ansi -pedantic -O1 -lSDL -lSDL_ttf -lSDL_gfx -std=c++0x
location.o: location.cpp
		g++ -c location.cpp location.h -Wall -ansi -pedantic -O1 -lSDL -lSDL_ttf -lSDL_gfx -std=c++0x
path.o: path.cpp
		g++ -c path.cpp path.h -Wall -ansi -pedantic -O1 -lSDL -lSDL_ttf -lSDL_gfx -std=c++0x


clean:
		-rm -f *.o *.gch .*.swn *.swo main *.out *.txt *.swp
