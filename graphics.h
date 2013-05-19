#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include <sstream>

class Graphics {	
public:
							Graphics();
							~Graphics();
	void					Init( int windowWidth, int windowHeight, const char* caption );
	void					SetBackgroundColor( int red, int green, int blue );
	void					ClearScene();
	void					DrawScene();
	void					ShowFPS( int fps );
	bool					Running;
	void					DrawSprite( SDL_Surface* spriteSurface, int srcX, int srcY, int dstX, int dstY, int width, int height );
private:
	SDL_Surface* 			Window;
	TTF_Font*				font;
	SDL_Color				textColor;

	// Background - Clear Screen Color
	int  					bgR;
	int						bgG;
	int						bgB;
};

#endif
