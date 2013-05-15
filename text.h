#ifndef TEXT_H
#define TEXT_H

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include <string>
#include <sstream>
#include <iostream>

class Text { 
public:
							Text();
							~Text();
	void					drawText( SDL_Surface* surface, char* text, const short int x, const short int y );
	void					drawFPS( SDL_Surface* surface, float fps );
private:
	TTF_Font* 				font;
	SDL_Color				foregroundColor;
	SDL_Color				backgroundColor;
	SDL_Surface*			textSurface;
	SDL_Rect 				textLocation;
};

#endif
