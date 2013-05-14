#ifndef TEXT_H
#define TEXT_H

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

class Text { 
public:
							Text();
							~Text();
	// void					drawText();
private:
	TTF_Font* 				font;
	SDL_Color				foregroundColor;
	SDL_Color				backgroundColor;
	// SDL_Surface*			textSurface;
	// SDL_Rect 				textLocation;
};

#endif
