A* Implementation
=====

![Screenshot](/screenshot.png?raw=true)

A* Implementation written in C++, SDL, g++, VIM and Screen GNU.  Compiled in g++ on Xbuntu.  Original started with Manhattan Heuristic, but changed it to give a better path.

Started May 14th, 2013. Completed May 28th, 2013 by Chris Harn.

## Dependencies

These needed to installed:
- SDL 1.2      From here www.libsdl.org/download-1.2.php
- SDL_ttf 2.0  From here www.libsdl.org/projects/SDL_ttf/
- SDL_gfx      From here www.ferzkopp.net/joomla/software-mainmenu-14/4-ferzkopps-linux-software/19-sdlgfx

These files need to be put in the directory:
- arial.tff    Do a google search for and download
- SDL.dll      Get from SDL 1.2 download
- SDL_ttf.dll  Get from SDL_ttf download
- sdlgfx.dll   Get from SDL_gfx download

## Building

To build this project, you need to make sure all the needed files are included in the AStar directory: arial.tff, SDL.dll, sdlgfx.dll, and SDL_ttf.dll.

To compile and run:

    make
    ./main

After you have successfully built and started the applet, you can start path finding by left clicking on the grid.  It will label the movement and heuristic cost for every node it touches along with the Start and End nodes.  The program also displays a frame rate counter in the top left corner.  Right clicking will reset the simulation to its original state. 
