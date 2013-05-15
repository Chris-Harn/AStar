#ifndef TEXT_H
#define TEXT_H

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include <string>

class Text { 
public:
							Text();
							~Text();
	void					drawText( SDL_Surface* surface, std::string text, int x, int y );
	void					drawFPS( SDL_Surface* surface, float fps );
private:
	TTF_Font* 				font;
	SDL_Color				foregroundColor;
	SDL_Color				backgroundColor;
	SDL_Surface*			textSurface;
	SDL_Rect 				textLocation;
};

#endif
